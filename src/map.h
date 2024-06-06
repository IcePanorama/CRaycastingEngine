#ifndef _MAP_H_
#define _MAP_H_

#include "raylib.h"

void draw_2d_map (const int WINDOW_WIDTH); //, const int WINDOW_HEIGHT);
int get_cell_size (void);
void draw_cell (float i, float j, Color color);
int global_x_to_map_row (float x);
int global_y_to_map_col (float y);
float map_row_to_global_x (int row);
float map_col_to_global_y (int col);
void get_cell_center (Vector2 *center, int row, int col);

#endif
