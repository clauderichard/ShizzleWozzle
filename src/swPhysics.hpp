
/* This is the 2D physical model.

A "box" of some mass lies on a flat horizontal surface.
There is no friction between the "box" and the surface.
The "box" is attached to a massless rigid rod, but the angle of the rod is free to move.
The other end of the rod is attached to a particle of some mass.
You can apply a force to the "box" going left of right.
A differential equation derived from Lagrangian equations determine the movement of the "box" and of the top particle.

The "head" is massless but of some positive radius around the top particle.
When the "head" touches the ground, the velocities of the "box",
  rod and top particle become combined into one velocity, using conservation of momentum.
The object continues to drag, with the head on the floor.
The head becomes smaller as you drag. It looks as if the head is digging into the ground except you don't see the underground part.
The ratio of the mass of the part of the head that's above the ground to the total head mass equals (distance dragged):(death-distance).
The object drags along with the head on the floor until either the head is completely gone or the object stops.

If the head completely disappears before stopping, then the rod keeps dangling according to dtheta at time of death. No friction.

*/ 

class swPhysics {

public:
	enum PhysicsState {
		PHYS_BALANCING, // The head is not on the floor yet
		PHYS_DRAGGING, // The head is on the floor
		PHYS_DEAD, // The head is completely gone, but the rod is still swinging back and forth
		PHYS_STOPPED // The head is on the floor, not completely gone, and dx/dt = 0
	};

	swPhysics(double gravityaccel, double headfriction, double boardforce,
		double bottommass, double rodmass, double headmass,
		double rodlength, double headradius,
		double deathdistance);
	~swPhysics();
	
	void set_position_x(double posx); // sets the bottom position if you don't want to use 0
	void set_position_angle(double angle); // sets the starting angle if you don't want to use 0
	void set_velocity_x(double posx); // sets the bottom velocity if you don't want to use 0
	void set_velocity_angle(double angle); // sets the starting angle velocity if you don't want to use 0
	
	// Change the forces applied to the bottom. True = pushing in that direction
	void set_force_right(bool pushing);
	void set_force_left(bool pushing);

	// get methods
	double get_position_x();
	double get_position_angle();
	double get_velocity_x();
	double get_velocity_angle(); // d(angle)/dt
	PhysicsState get_state(); // balancing, dragging, etc
	double get_startdrag_bottom(); // position of box when you started dragging
	double get_startdrag_top(); // position of head when you started dragging
	double get_enddrag_bottom(); // position of box when you died or stopped
	double get_enddrag_top(); // position of head when you died or stopped
	
	// calculates one timestep. 1/60 second usually.
	// Returns true if the state has changed.
	bool timestep(double seconds);

private:

	// These are the parameters of the physical model.
	double m_accel_gravity; // acceleration due to gravity
	double m_accel_top; // negative acceleration when scraping your head
	double m_force_bottom; // force that the arrows would apply to the bottom part when not scraping
	double m_mass_bottom; // mass of the bottom part
	double m_mass_rod; // mass of the rod between bottom and top
	double m_mass_top; // mass of the top (head)
	double m_length_rod; // length of the rod from bottom joint to head. equal to height of joint.
	double m_radius_top; // radius of the head
	double m_distance_death; // distance you have to scrape your head on the floor to scrape entire head off

	// These are calculated from parameters in the constructor, for computational convenience.
	double m_alpha; // sum of three masses
	double m_beta; // mh + mr/2
	double m_lambda; // mh + mr/3
	double m_phi; // alpha*(lambda*length^2 + 2/3*headmass*radius^2)
	double m_cosangle_startdrag; // cos of the angle at which you need to be to hit the floor
	// These are for dead mode
	double m_alpha2; // sum of three masses
	double m_beta2; // mh + mr/2
	double m_lambda2; // mh + mr/3
	double m_phi2; // alpha*(lambda*length^2 + 2/3*headmass*radius^2)
	
	// Current state
	PhysicsState m_state; // are you balancing, dragging, dead or stopped?

	// These represent the current state of the physical model while balancing.
	double m_position_x; // x position of the bottom part. default=0
	double m_position_angle; // angle of rod relative to vertical. positive = counterclockwise.
	double m_velocity_x; // d(posx)/dt
	double m_velocity_angle; // d(angle)/dt
	bool m_pushing_right; // are you applying force to the right?
	bool m_pushing_left; // are you applying force to the left?
	double m_start_drag; // x position of box where you started dragging.
	double m_end_drag; // x position of box either when you either died or stopped.

};