#include "map.h"
#include "raylib.h"

#define MAP_WIDTH 9
#define MAP_HEIGHT 9

// clang-format off
char map[MAP_WIDTH][MAP_HEIGHT] = {
  { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 1, 1, 0, 0, 0, 0, 1 },
  { 1, 0, 1, 1, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};
// clang-format on 

int window_width;

void 
draw_2d_map(const int WINDOW_WIDTH)//, const int WINDOW_HEIGHT)
{
  window_width = WINDOW_WIDTH;
  for (int i = 0; i < MAP_WIDTH; i++)
  {
    for (int j = 0; j < MAP_HEIGHT; j++)
    {
      Color color = map[i][j] == 1 ? YELLOW : GRAY;
      draw_cell(i, j, color);
    }
  }
}

int 
get_cell_size (void)
{
  return (window_width / 2) / MAP_WIDTH + 1;
}

void 
draw_cell (float i, float j, Color color)
{
  const int SIZE = get_cell_size();
  DrawRectangle(i * SIZE + 1,j * SIZE + 1, SIZE - 2, SIZE - 2, color);
}

// why am I using floats everywhere? should switch to double lol
int 
global_x_to_map_row (float x)
{
  return (int)(x / get_cell_size ());
}

int 
global_y_to_map_col (float y)
{
  return (int)(y / get_cell_size ());
}

float 
map_row_to_global_x (int row)
{
  return row * get_cell_size();
}

float
map_col_to_global_y (int col)
{
  return col * get_cell_size();
}

void
get_cell_center (Vector2* center, int row, int col)
{
  center->x = map_row_to_global_x(row);
  center->y = map_col_to_global_y(col);
}

bool 
is_cell_wall(int i, int j)
{
  if (i < 0 || i >= MAP_WIDTH || j < 0 || j >= MAP_HEIGHT)
  {
    return false;
  }
  return map[i][j] == 1;
}

/*void 
draw_3d_view (void)
{
}*/
