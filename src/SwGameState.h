#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <cgGameState.h>
#include "sw_pde_plane.h"
#include "sw_camera.h"

class SwGameState : public cgGameState {

	// pde
	sw_pde_plane _pde;
	// camera
	sw_camera _camera;

	// for graphics
	ALLEGRO_FONT* font;
	int radius;
	int legs_y;
	int legs_height;
	int enemy_height;
	int enemy_width;
	int enemy_dx;
	int ground_y;
	double wheelradius;
	double wheelseparation_2;
	double angle_arms;
	double arm_length;

	// physics constants
	double grav;
	double legs_mass;
	double head_mass;
	double stick_length;
	double jetpackforce;

	// physics variables
	double legs_x;
	double theta;
	double legs_dx;
	double dtheta;
	double enemy_x;
	bool enemy_dir; // true if right

	// 3d physics variables
	double _x;
	double _y;
	double _phi;
	double _theta;
	double _dx;
	double _dy;
	double _dphi;
	double _dtheta;

	double cur_score;
	double high_score;
	int cur_enemy_score;
	int high_enemy_score;

	bool resting;
	int resting_count;

	bool game_over();
	void reset();
public:
	SwGameState(cgGame*);
	~SwGameState();
	void draw_on_screen();
	void compute_timestep();
};
