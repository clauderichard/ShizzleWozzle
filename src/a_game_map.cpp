//#include "sw_game_map.h"
//#include "globals.h"
//
//#include <allegro5\allegro.h>
//#include <fstream>
//using namespace std;
//
//sw_game_map::sw_game_map() {
//
//	block_width = 20;
//	block_height = 20;
//	num_block_rows = 20;
//	num_block_cols = 20;
//	blocks = new int*[num_block_cols];
//
//	for (int i=0; i<20; i++) {
//		blocks[i] = new int[num_block_rows];
//		for (int j=0; j<20; j++) {
//			blocks[i][j] = (j==18 ? WALL : NOTHING);
//		}
//	}
//}
//
//bool sw_game_map::load_map(const char *filename) {
//	int r = 0;
//	int c = 0;
//	ifstream openfile(filename);
//	if (openfile.is_open()) {
//		// delete blocks
//		for (int i=0; i<num_block_cols; i++) {
//			delete[] blocks[i];
//		}
//		delete[] blocks;
//
//		openfile >> num_block_cols >> num_block_rows >> block_width >> block_height;
//
//		// initialize blocks again
//		blocks = new int*[num_block_cols];
//		for (int i=0; i<num_block_cols; i++) {
//			blocks[i] = new int[num_block_rows];
//		}
//
//		while(!openfile.eof())
//		{
//			openfile >> blocks[r][c];
//			r ++;
//			if (r >= num_block_cols) {
//				r = 0;
//				c ++;
//			}
//		}
//	
//		// draw bitmap
//		bitmap = al_create_bitmap(block_width / global_pixel_width * num_block_cols, block_height / global_pixel_height * num_block_rows);
//		al_set_target_bitmap(bitmap);
//		for (int x=0; x<num_block_cols; x++) {
//			for (int y=0; y<num_block_rows; y++) {
//				int topx = x*block_width / global_pixel_width;
//				int topy = y*block_height / global_pixel_height;
//				al_draw_filled_rectangle(topx, topy, topx+block_width / global_pixel_width, topy+block_height / global_pixel_height, get_color(x, y));
//			}
//		}
//		al_set_target_bitmap(al_get_backbuffer(global_screen_display));
//	} else {
//		return false;
//	}
//	openfile.close();
//	return true;
//}
//
//sw_game_map::~sw_game_map() {
//	for (int i=0; i<num_block_cols; i++) {
//		delete[] blocks[i];
//	}
//	delete[] blocks;
//	al_destroy_bitmap(bitmap);
//}
//
//int sw_game_map::get_block_rows() {
//	return num_block_rows;
//}
//
//int sw_game_map::get_block_cols() {
//	return num_block_cols;
//}
//
//int sw_game_map::get_block(int x, int y) {
//	return blocks[x][y];
//}
//
//float sw_game_map::get_block_height() {
//	return block_height;
//}
//
//float sw_game_map::get_block_width() {
//	return block_width;
//}
//
//ALLEGRO_COLOR sw_game_map::get_color(int x, int y) {
//	switch(blocks[x][y]) {
//	case START:
//		return al_map_rgb(0, 0, 0);
//	case WALL:
//		return al_map_rgb(255, 0, 0);
//	case NOTHING:
//		return al_map_rgb(0, 0, 0);
//	case ENEMY:
//		return al_map_rgb(0, 0, 0);
//	}
//	return al_map_rgb(255, 0, 255);
//}
//
//ALLEGRO_BITMAP* sw_game_map::get_bitmap() {
//	return bitmap;
//}