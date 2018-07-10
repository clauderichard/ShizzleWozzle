#include "sw_game_state_master.h"

#include <allegro5\allegro_primitives.h>
#include "sw_game_state_menu.h"
#include "sw_game_state.h"

sw_game_state_master::sw_game_state_master() {
	_game_state_sub = NULL;
}

sw_game_state_master::~sw_game_state_master() {
	al_destroy_font(_font);
	delete _game_state_sub;
}

void sw_game_state_master::draw_on_screen() {
	if (_inmenu) {
		int ty = _select_skate ? 260 : 200;
		al_draw_filled_triangle(200, ty, 200, ty+40, 240, ty+20, al_map_rgb(0, 255, 255));
		al_draw_text(_font, al_map_rgb(255, 255, 255), 250, 260, 0, "Skateboard");
		al_draw_text(_font, al_map_rgb(255, 255, 255), 250, 200, 0, "Main game (currently a mess)");
	} else {
		_game_state_sub->draw_on_screen();
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
}

void sw_game_state_master::compute_timestep() {
	if (_game_state_sub!=NULL) _game_state_sub->compute_timestep();
}

//void sw_game_state_master::set_game_state_sub(sw_game_state* gs) {
//	game_state_sub = gs;
//}