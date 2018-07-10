//#include "sw_ml_room.h"
//
//#include <fstream>
//using namespace std;
//
//sw_ml_room::sw_ml_room(char* filename) {
//	ifstream openfile(filename);
//
//	if (openfile.is_open()) {
//		// delete blocks
//		//delete[] _boundary_vertices_x;
//		//delete[] _boundary_vertices_y;
//
//		// boundaries
//		openfile >> _boundary_vertices_num;
//		_boundary_vertices_x = new float[_boundary_vertices_num];
//		_boundary_vertices_y = new float[_boundary_vertices_num];
//		for (int i=0; i<_boundary_vertices_num; i++) {
//			openfile >> _boundary_vertices_x[i] >> _boundary_vertices_y[i];
//		}
//
//		// start of shizzle
//		openfile >> _start_x >> _start_y;
//
//		// enemies
//		openfile >> _enemies_num;
//		_enemies_layer = new int[_enemies_num];
//		_enemies_x = new float[_enemies_num];
//		_enemies_y = new float[_enemies_num];
//		for (int i=0; i<_enemies_num; i++) {
//			openfile >> _enemies_layer[i] >> _enemies_x[i] >> _enemies_y[i];
//		}
//
//		// tiles
//		openfile >> _tiles_start_x >> _tiles_start_y >> _tiles_width >> _tiles_height >> _tiles_numcols >> _tiles_numrows;
//		_tiles = new bool*[_tiles_numcols];
//		for (int i=0; i<_tiles_numcols; i++) {
//			_tiles[i] = new bool[_tiles_numrows];
//		}
//		int temp;
//		for (int i=0; i<_tiles_numrows; i++) {
//			for (int j=0; j<_tiles_numcols; j++) {
//				openfile >> temp;
//				_tiles[j][i] = temp!=0; // false if zero, true otherwise
//			}
//		}
//
//		//while(!openfile.eof())
//		//{
//		//	openfile >> blocks[r][c];
//		//	r ++;
//		//	if (r >= num_block_cols) {
//		//		r = 0;
//		//		c ++;
//		//	}
//		//}
//	}
//	openfile.close();
//}
//
//sw_ml_room::~sw_ml_room() {
//	delete[] _boundary_vertices_x;
//	delete[] _boundary_vertices_y;
//	delete[] _enemies_x;
//	delete[] _enemies_y;
//	delete[] _enemies_layer;
//	for (int i=0; i<_tiles_numcols; i++) {
//		delete[] _tiles[i];
//	}
//	delete[] _tiles;
//}
//
//float sw_ml_room::get_boundary_vertex_x(int n) {
//	return _boundary_vertices_x[n];
//}
//
//float sw_ml_room::get_boundary_vertex_y(int n) {
//	return _boundary_vertices_y[n];
//}
//
//int sw_ml_room::get_boundary_vertex_num() {
//	return _boundary_vertices_num;
//}
//
//float sw_ml_room::get_start_x() {
//	return _start_x;
//}
//
//float sw_ml_room::get_start_y() {
//	return _start_y;
//}
//
//int sw_ml_room::get_enemy_num() {
//	return _enemies_num;
//}
//
//float sw_ml_room::get_enemy_x(int n) {
//	return _enemies_x[n];
//}
//
//float sw_ml_room::get_enemy_y(int n) {
//	return _enemies_y[n];
//}
//
//int sw_ml_room::get_enemy_layer(int n) {
//	return _enemies_layer[n];
//}
//
//float sw_ml_room::get_tiles_width() {
//	return _tiles_width;
//}
//
//float sw_ml_room::get_tiles_height() {
//	return _tiles_height;
//}
//
//float sw_ml_room::get_tiles_start_x() {
//	return _tiles_start_x;
//}
//
//float sw_ml_room::get_tiles_start_y() {
//	return _tiles_start_y;
//}
//
//int sw_ml_room::get_tiles_numrows() {
//	return _tiles_numrows;
//}
//
//int sw_ml_room::get_tiles_numcols() {
//	return _tiles_numcols;
//}
//
//bool sw_ml_room::get_tile(int x, int y) {
//	return _tiles[x][y];
//}