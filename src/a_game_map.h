//#ifndef __SW_GAME_MAP_H__
//#define __SW_GAME_MAP_H__
//
//#include <allegro5\allegro.h>
//#include <allegro5\allegro_primitives.h>
//#include <allegro5\allegro_image.h>
//
//class sw_game_map {
//
//	ALLEGRO_BITMAP* bitmap;
//
//	int** blocks;
//	float block_width;
//	float block_height;
//	int num_block_rows;
//	int num_block_cols;
//
//public:
//	static enum blocks {START, WALL, NOTHING, ENEMY};
//	sw_game_map();
//	~sw_game_map();
//	bool load_map(const char *filename);
//	int get_block(int x, int y);
//	float get_block_height();
//	float get_block_width();
//	int get_block_rows();
//	int get_block_cols();
//	ALLEGRO_COLOR get_color(int x, int y);
//	ALLEGRO_BITMAP* get_bitmap();
//};
//
//#endif