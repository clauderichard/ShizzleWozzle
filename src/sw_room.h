//#ifndef __SW_ML_ROOM_H__
//#define __SW_ML_ROOM_H__
//
//#include "sw_ml_object.h"
//
//class sw_ml_room {
//	float* _boundary_vertices_x;
//	float* _boundary_vertices_y;
//	int _boundary_vertices_num;
//	float _start_x;
//	float _start_y;
//	float* _enemies_x;
//	float* _enemies_y;
//	int _enemies_num;
//	int* _enemies_layer;
//	
//	float _tiles_width;
//	float _tiles_height;
//	float _tiles_start_x;
//	float _tiles_start_y;
//	int _tiles_numrows;
//	int _tiles_numcols;
//	bool** _tiles;
//
//public:
//	sw_ml_room(char* filename);
//	sw_ml_room(sw_ml_object* parsetree);
//	~sw_ml_room();
//	float get_boundary_vertex_x(int n);
//	float get_boundary_vertex_y(int n);
//	int get_boundary_vertex_num();
//	float get_start_x();
//	float get_start_y();
//	float get_enemy_x(int n);
//	float get_enemy_y(int n);
//	int get_enemy_layer(int n);
//	int get_enemy_num();
//
//	float get_tiles_width();
//	float get_tiles_height();
//	float get_tiles_start_x();
//	float get_tiles_start_y();
//	int get_tiles_numrows();
//	int get_tiles_numcols();
//	bool get_tile(int x, int y);
//};
//
//#endif