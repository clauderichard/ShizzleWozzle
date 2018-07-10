#include "swPhysics.hpp"

#define M_PI 3.141592653538

swPhysics::swPhysics(double gravityaccel, double headfriction, double boardforce,
					double bottommass, double rodmass, double headmass,
					double rodlength, double headradius,
					double deathdistance) {
	m_accel_gravity = gravityaccel;
	m_accel_top = headfriction;
	m_force_bottom = boardforce;
	m_mass_bottom = bottommass;
	m_mass_rod = rodmass;
	m_mass_top = headmass;
	m_length_rod = rodlength;
	m_radius_top = headradius;
	m_distance_death = deathdistance;

	m_alpha = m_mass_bottom + m_mass_rod + m_mass_top;
	m_beta = m_mass_top + m_mass_rod/2;
	m_lambda = m_mass_top + m_mass_rod/3;
	m_phi = m_alpha*(m_lambda*(m_length_rod+m_radius_top)*(m_length_rod+m_radius_top) + m_mass_top*m_radius_top*m_radius_top*2/3);
	m_cosangle_startdrag = - (m_length_rod - m_radius_top) / (m_length_rod + m_radius_top);
	m_alpha2 = m_mass_bottom + m_mass_rod;
	m_beta2 = m_mass_rod/2;
	m_lambda2 = m_mass_rod/3;
	m_phi2 = m_alpha2*m_lambda2*m_length_rod*m_length_rod;

	m_state = PHYS_BALANCING;

	m_position_x = 0;
	m_position_angle = 0;
	m_velocity_x = 0;
	m_velocity_angle = 0;
	m_pushing_right = false;
	m_pushing_left = false;
	m_start_drag = 0; // who cares at this point?
	m_end_drag = 0; // who cares at this point?
}

swPhysics::~swPhysics() {

}

void swPhysics::set_position_x(double posx) {
	m_position_x = posx;
}
void swPhysics::set_position_angle(double angle) {
	m_position_angle = angle;
}
void swPhysics::set_velocity_x(double velx) {
	m_velocity_x = velx;
}
void swPhysics::set_velocity_angle(double d_angle) {
	m_velocity_angle = d_angle;
}

void swPhysics::set_force_left(bool pushing) {
	m_pushing_left = pushing;
}
void swPhysics::set_force_right(bool pushing) {
	m_pushing_right = pushing;
}

// get methods
double swPhysics::get_position_x() {
	return m_position_x;
}
double swPhysics::get_position_angle() {
	return m_position_angle;
}
double swPhysics::get_velocity_x() {
	return m_velocity_x;
}
double swPhysics::get_velocity_angle() {
	return m_velocity_angle;
}
swPhysics::PhysicsState swPhysics::get_state() {
	return m_state;
}
double swPhysics::get_startdrag_bottom() {
	return m_start_drag;
}
double swPhysics::get_startdrag_top() {
	double y = m_length_rod - m_radius_top;
	double xplus = sqrt(m_length_rod*m_length_rod - y*y);
	return xplus + m_start_drag;
}
double swPhysics::get_enddrag_bottom() {
	return m_end_drag;
}
double swPhysics::get_enddrag_top() {
	double y = m_length_rod - m_radius_top;
	double xplus = sqrt(m_length_rod*m_length_rod - y*y);
	return xplus + m_end_drag;
}

bool swPhysics::timestep(double seconds) {
	// intermediate variables for computation
	double ddangle;
	double ddx;
	double extra1;
	double extra2;
	double force;
	bool retval = false;

	switch( m_state ) {
	case PHYS_BALANCING:
		extra1 = m_beta*m_length_rod*cos(m_position_angle);
		extra2 = m_beta*m_length_rod*sin(m_position_angle);
		force = (m_pushing_right?m_force_bottom:0) - (m_pushing_left?m_force_bottom:0);
		ddangle = (m_alpha*m_accel_gravity*extra2 - force*extra1 - extra1*extra2*m_velocity_angle*m_velocity_angle) / (m_phi - extra1*extra1);
		ddx = (force + extra2*m_velocity_angle*m_velocity_angle - extra1*ddangle) / m_alpha;

		m_velocity_x += ddx*seconds;
		m_velocity_angle += ddangle*seconds;
		// if the head is gonna hit the floor then set the drag start position and start dragging
		if ( sin(m_position_angle+m_velocity_angle*seconds) < m_sinangle_startdrag ) {
			retval = true;
			// extra1 means seconds now, from timestep-start to hitting point
			extra1 = seconds * (m_sinangle_startdrag-m_position_angle) / (m_velocity_angle*seconds);
			m_start_drag = m_position_x+m_velocity_x*extra1;
			m_position_x = m_start_drag;
			m_position_angle = m_sinangle_startdrag;
			m_state = PHYS_DRAGGING;
			// new velocities by combining current velocities for conservation of momentum in x-dir
			m_velocity_x += m_length_rod*m_velocity_angle*m_beta*cos(m_position_angle)/m_alpha;
			m_velocity_angle = 0; // not used during dragging
			// The control flow will go to PHYS_DRAGGING from here to do a little bit of dragging.
			seconds -= extra1;
		} else {
			m_position_x += m_velocity_x*seconds;
			m_position_angle += m_velocity_angle*seconds;
			return retval;
		}
	case PHYS_DRAGGING:
		// if no seconds left because you just came from PHYS_BALANCING, then do nothing.
		if (seconds <= 0) {
			break;
		}
		m_velocity_x -= m_accel_top*seconds;
		if (m_velocity_x <= 0) {
			m_velocity_x = 0;
		} else {
			// if you're going to die, then die and dangle a little bit.
			if (m_position_x+m_velocity_x*seconds-m_start_drag >= m_distance_death) {
				retval = true;
				// extra1 = seconds from start of timestep to death
				extra1 = seconds * (m_distance_death-m_position_x) / (m_velocity_x*seconds);
				m_position_x = m_distance_death + m_start_drag;
				m_position_angle = M_PI;
				m_end_drag = m_position_x;
				m_state = PHYS_DEAD;
				m_velocity_x -= m_accel_top*extra1; // speed at death
				// set the angular velocity according to speed at death (speed of rod-bottom = - box-speed)
				m_velocity_angle = m_velocity_x / m_length_rod;
				seconds -= extra1;
				// go to PHYS_DEAD
			} else {
				// update x position and angle
				m_position_x += m_velocity_x*seconds;
				m_position_angle = ;
				return retval;
			}
		}
	case PHYS_DEAD:
		// Headless thing dangling along
		extra1 = m_beta2*m_length_rod*cos(m_position_angle);
		extra2 = m_beta2*m_length_rod*sin(m_position_angle);
		ddangle = (m_alpha2*m_accel_gravity*extra2 - extra1*extra2*m_velocity_angle*m_velocity_angle) / (m_phi2 - extra1*extra1);
		ddx = (extra2*m_velocity_angle*m_velocity_angle - extra1*ddangle) / m_alpha2;
		
		m_velocity_x += ddx*seconds;
		m_velocity_angle += ddangle*seconds;
		m_position_x += m_velocity_x*seconds;
		m_position_angle += m_velocity_angle*seconds;

		return retval; // don't go from dead to stopped
	case PHYS_STOPPED:
		// don't do anything here
		return retval;
	}
}