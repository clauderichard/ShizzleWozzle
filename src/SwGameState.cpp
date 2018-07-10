#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <math.h>
#include "SwGameState.h"
#include "globals.h"
#include "sw_camera.h"
#include <string>
//#include <cgAudiomanager.h>
#include <cgInputmanager.h>
#include <cgGame.h>

SwGameState::SwGameState(cgGame* g) : cgGameState(g), _pde(), _camera() {

	//std::string* files = new std::string[4];
	//files[0] = "coin0.png";
	//files[1] = "coin1.png";
	//files[2] = "coin2.png";
	//files[3] = "coin3.png";
	//_sprite = new cgSprite(__game, "images", files, 4, 8);
	//std::string* files2 = new std::string[4];
	//files2[0] = "5coins.png";
	//files2[1] = "5coins2.png";
	//files2[2] = "5coins3.png";
	//files2[3] = "5coins2.png";
	//_sprite2 = new cgSprite(__game, "images", files2, 4, 8);
	//__game->getAudioManager().play(0, false);

	resting_count = 0;
	resting = false;

	font = al_load_font("fonts/arial.ttf", 24, 0);

	radius = 30;
	legs_height = 80;
	enemy_height = 35;
	enemy_dx = 2;
	enemy_width = 40;
	ground_y = __game->screenHeight() - 50;
	legs_y = ground_y-legs_height;
	grav = 0.4;
	wheelradius = 5;
	wheelseparation_2 = 20;
	angle_arms = asin(0.3);
	arm_length = 50;

	legs_mass = 5;
	head_mass = 1;
	stick_length = 200;

	high_score = 0;
	high_enemy_score = 0;

	jetpackforce = 15;

	reset();
}

SwGameState::~SwGameState() {
	al_destroy_font(font);
}

void SwGameState::draw_on_screen() {
	//if (_background==NULL) _background = new Background("images", "bkgd.png", gc);
	int width = __game->screenWidth();
	int height = __game->screenHeight();
	double head_cx = legs_x + stick_length*cos(theta);
	double head_cy = legs_y - stick_length*sin(theta);

	//_camera.phi = 1.8;
	//_camera.theta = 1.6;
	//_camera.spread = 1.0;
	//_camera.x = _pde.x + 0.3;
	//_camera.y = _pde.y - 5.0;
	//_camera.z = 1.7;

	//sw_vector basevec(_pde.x, _pde.y, 0);
	//sw_vector headvec(_pde.x+_pde.a, _pde.y+_pde.b, _pde.c);
	//sw_vector c1(-1,-1,0);
	//sw_vector c2(-1,1,0);
	//sw_vector c3(1, 0, 0);
	//sw_vector shadow(_pde.x + _pde.a, _pde.y + _pde.b, 0);

	//sw_vector basecam = _camera.project(basevec);
	//sw_vector headcam = _camera.project(headvec);
	//sw_vector c1cam = _camera.project(c1);
	//sw_vector c2cam = _camera.project(c2);
	//sw_vector c3cam = _camera.project(c3);
	//sw_vector shadowcam = _camera.project(shadow);
	//
	//int bx = width/2 + basecam.x*width;
	//int by = height/2 - basecam.y*height;
	//int hx = width/2 + headcam.x*width;
	//int hy = height/2 - headcam.y*height;

	//// random triangle carpet
	//al_draw_filled_triangle(width/2 + c1cam.x*width, height/2 - c1cam.y*height,
	//	width/2 + c2cam.x*width, height/2 - c2cam.y*height,
	//	width/2 + c3cam.x*width, height/2 - c3cam.y*height, al_map_rgb(128, 0, 0));

	//// main
	//// shadow
	//if (headcam.z > 0) {
	//	int hr = 40.0/headcam.z;
	//	al_draw_filled_circle(hx, hy, hr, al_map_rgb(0, 255, 0));
	//	al_draw_filled_circle(width/2 + shadowcam.x*width, height/2 - shadowcam.y*height, hr, al_map_rgb(128, 128, 128));
	//}
	//if (basecam.z > 0) {
	//	int br = 80.0/basecam.z;
	//	al_draw_filled_circle(bx, by, br, al_map_rgb(0, 0, 255));
	//}
	//if (headcam.z > 0 && basecam.z > 0) {
	//	al_draw_line(bx, by, hx, hy, al_map_rgb(0, 128, 128), 2);
	//}
	//
	//// small representation
	//al_draw_filled_circle(100, 100, 10, al_map_rgb(0, 0, 255));
	//al_draw_filled_circle(100+_pde.a*30, 100-_pde.b*30, 5, al_map_rgb(0, 255, 0));
	//
	////al_draw_line(100, 100, 100+_pde.a*20, 100-sqrt(_pde.l*_pde.l-_pde.a*_pde.a)*20, al_map_rgb(255, 0, 0), 1);
	////al_draw_line(200, 100, 200+sqrt(_pde.l*_pde.l-_pde.b*_pde.b)*20, 100-_pde.b*20, al_map_rgb(255, 0, 0), 1);

	//if (resting) {
	//	al_draw_textf(font, al_map_rgb(255, 255, 255), 100, 100, ALLEGRO_ALIGN_LEFT, "You are dead.");
	//}

	al_draw_textf(font, al_map_rgb(255, 255, 255), 10, ground_y+10, ALLEGRO_ALIGN_LEFT,
		  "Score: %d", cur_enemy_score);
	al_draw_textf(font, al_map_rgb(255, 255, 255), width/2+10, ground_y+10, ALLEGRO_ALIGN_LEFT,
		  "High Score: %d", high_enemy_score);
	al_draw_line(0, ground_y+2, width, ground_y+2, al_map_rgb(255, 255, 0), 1);

	double eyeradius = radius/5;
	double righteye_cx = head_cx + radius*sin(theta)/2;
	double lefteye_cx = head_cx - radius*sin(theta)/2;
	double righteye_cy = head_cy + radius*cos(theta)/2;
	double lefteye_cy = head_cy - radius*cos(theta)/2;
	double rightsmile_x = lefteye_cx - radius/2*cos(theta);
	double leftsmile_x = righteye_cx - radius/2*cos(theta);
	double rightsmile_y = lefteye_cy + radius/2*sin(theta);
	double leftsmile_y = righteye_cy + radius/2*sin(theta);
	double neck_x = head_cx - radius*cos(theta);
	double neck_y = head_cy + radius*sin(theta);
	double rightarm_x = neck_x - cos(theta-angle_arms)*arm_length;
	double leftarm_x = neck_x - cos(theta+angle_arms)*arm_length;
	double rightarm_y = neck_y + sin(theta-angle_arms)*arm_length;
	double leftarm_y = neck_y + sin(theta+angle_arms)*arm_length;

	// legs
	al_draw_line(legs_x, legs_y,
		legs_x+wheelseparation_2, legs_y+legs_height-2*wheelradius,
		al_map_rgb(0, 0, 255), 2);
	al_draw_line(legs_x, legs_y,
		legs_x-wheelseparation_2, legs_y+legs_height-2*wheelradius,
		al_map_rgb(0, 0, 255), 2);

	// board
	al_draw_line(legs_x-wheelseparation_2-wheelradius, ground_y-2*wheelradius,
		legs_x+wheelseparation_2+wheelradius, ground_y-2*wheelradius,
		al_map_rgb(0, 255, 0), 2);
	al_draw_circle(legs_x-wheelseparation_2, ground_y-wheelradius, 5, al_map_rgb(0, 255, 0), 1);
	al_draw_circle(legs_x+wheelseparation_2, ground_y-wheelradius, 5, al_map_rgb(0, 255, 0), 1);

	// stick
	al_draw_line(legs_x, legs_y, head_cx, head_cy, al_map_rgb(0, 0, 255), 3);

	// arms
	al_draw_line(neck_x, neck_y, rightarm_x, rightarm_y, al_map_rgb(0, 0, 255), 3);
	al_draw_line(neck_x, neck_y, leftarm_x, leftarm_y, al_map_rgb(0, 0, 255), 3);

	// head
	al_draw_filled_circle(head_cx, head_cy, radius, al_map_rgb(0, 0, 255));
	al_draw_line(leftsmile_x, leftsmile_y, rightsmile_x, rightsmile_y, al_map_rgb(255, 255, 255), 2);
	al_draw_filled_circle(lefteye_cx, lefteye_cy, eyeradius, al_map_rgb(255, 255, 255));
	al_draw_filled_circle(righteye_cx, righteye_cy, eyeradius, al_map_rgb(255, 255, 255));

	// enemy
	al_draw_filled_rectangle(enemy_x-enemy_width/2, ground_y-enemy_height, enemy_x+enemy_width/2, ground_y, al_map_rgb(255, 0, 0));

	// random sprite
	//_sprite->step();

	//_sprite->draw(10, 10);
	//_sprite2->step();
	//_sprite2->draw(20, 30);

}

void SwGameState::compute_timestep() {
	if (resting) {
		resting_count ++;
		if (resting_count > __game->framesPerSecond() / 2) {
			resting = false;
			resting_count = 0;
			reset();
		}
		return;
	}

	////jetpack force
	//double fx = 0;
	//double fy = 0;
	//if (gc.inputManager().pressed(ALLEGRO_KEY_RIGHT) || gc.inputManager().times_pressed(ALLEGRO_KEY_RIGHT)>0) fx += jetpackforce;
	//if (gc.inputManager().pressed(ALLEGRO_KEY_LEFT) || gc.inputManager().times_pressed(ALLEGRO_KEY_LEFT)>0) fx -= jetpackforce;
	//if (gc.inputManager().pressed(ALLEGRO_KEY_UP) || gc.inputManager().times_pressed(ALLEGRO_KEY_UP)>0) fy += jetpackforce;
	//if (gc.inputManager().pressed(ALLEGRO_KEY_DOWN) || gc.inputManager().times_pressed(ALLEGRO_KEY_DOWN)>0) fy -= jetpackforce;
	//_pde.fx = fx;
	//_pde.fy = fy;

	jetpackforce = 0;
	jetpackforce += __game->getInputManager()->pressed(ALLEGRO_KEY_RIGHT)*3;
	jetpackforce -= __game->getInputManager()->pressed(ALLEGRO_KEY_LEFT)*3;

	double ddx = jetpackforce + head_mass*cos(theta)*(stick_length*dtheta*dtheta - grav*sin(theta));
	ddx /= (legs_mass + head_mass*cos(theta)*cos(theta));
	//double ddtheta = grav*cos(theta)*(legs_mass*head_mass) - head_mass*stick_length*dtheta*dtheta*sin(theta)*cos(theta) - jetpackforce*sin(theta);
	//ddtheta /= stick_length*(head_mass*sin(theta)*sin(theta) - legs_mass - head_mass);
	double ddtheta = ddx*sin(theta) - grav*cos(theta);
	ddtheta /= stick_length;

	legs_dx += ddx;
	dtheta += ddtheta;
	legs_x += legs_dx;
	theta += dtheta;

	// enemy
	enemy_x += (enemy_dir ? enemy_dx : -enemy_dx);
	double dist = enemy_x - legs_x;
	dist = dist<0 ? -dist : dist;
	double contactdist = enemy_width/2 + wheelradius + wheelseparation_2;
	if (dist < contactdist) {
		//__game->getAudioManager().play(1, false);
		cur_enemy_score ++;
		if (cur_enemy_score > high_enemy_score) {
			high_enemy_score = cur_enemy_score;
		}
		enemy_dir = !enemy_dir;
		if (enemy_dir) {
			enemy_x = -enemy_width;
		} else {
			enemy_x = __game->screenWidth() + enemy_width;
		}
	}
	if (game_over()) {
		//__game->getAudioManager().play(2, false);
		resting = true;
		resting_count = 0;
	}

	//_pde.step(1.0/60);
	//if (_pde.onfloor) {
	//	resting = true;
	//	resting_count = 0;
	//}
}

bool SwGameState::game_over() {
	int width = __game->screenWidth();
	double head_cx = legs_x + stick_length*cos(theta);
	double head_cy = legs_y - stick_length*sin(theta);
	return (head_cx<=radius || head_cx>=width-radius || head_cy>=ground_y-radius);
}

void SwGameState::reset() {
	int width = __game->screenWidth();

	legs_x = width/2;
	enemy_x = -enemy_width;
	enemy_dir = true;
	theta = asin(1.0)+0.01;
	legs_dx = 0;
	dtheta = 0;

	cur_score = 0;
	cur_enemy_score = 0;

	_pde.reset();
}
