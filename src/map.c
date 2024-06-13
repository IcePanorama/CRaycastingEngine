#include "map.h"
#include "utils.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>

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
draw_2d_map(const int WINDOW_WIDTH)
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
  return (window_width / 2) / MAP_WIDTH;
}

void 
draw_cell (float i, float j, Color color)
{
  const int SIZE = get_cell_size();
  DrawRectangle(i * SIZE, j * SIZE, SIZE - 2, SIZE - 2, color);
}

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

void 
draw_3d_view (Player *player, const int WINDOW_WIDTH, const int WINDOW_HEIGHT)
{
  const float VIEW_PLANE_DIST = 100.0;
  const int SCREEN_START = WINDOW_WIDTH / 2.0;
  float ray_angle = player->angle - (PLAYER_FOV / 2.0) * DEG2RAD;
  for (int ray_count = 0; ray_count < SCREEN_START; ray_count++)
    {
      Vector2 ray;
      calculate_ray_length (&player->pos, &ray, ray_angle);

      float dist = v2_distance (&player->pos, &ray);
      dist *= cos (ray_angle - player->angle);

      int wall_height = (int)((WINDOW_WIDTH / 2.0) / dist * VIEW_PLANE_DIST);

      float shade_factor = 1.0 - (dist / 1500);
      if (shade_factor < 0.0)
        {
          shade_factor = 0.0;
        }
      // If we don't draw the floor, we could have some sort of
      // sky texture that we draw before drawing walls/the floor
      
      /*
      Color ceiling_shade = (Color){(int)(LIGHTGRAY.r * shade_factor),
                                    (int)(LIGHTGRAY.g * shade_factor),
                                    (int)(LIGHTGRAY.b * shade_factor),
                                    LIGHTGRAY.a};
       */
      Color floor_shade = (Color){(int)(GREEN.r * shade_factor),
                                  (int)(GREEN.g * shade_factor),
                                  (int)(GREEN.b * shade_factor), GREEN.a};
      Color wall_shade = (Color){(int)(BLUE.r * shade_factor),
                                 (int)(BLUE.g * shade_factor),
                                 (int)(BLUE.b * shade_factor), BLUE.a};

      // Ceiling
      //DrawLine (ray_count + SCREEN_START, 0, ray_count + SCREEN_START, WINDOW_HEIGHT - wall_height, ceiling_shade);
      // Walls  
      DrawLine (ray_count + SCREEN_START, WINDOW_HEIGHT / 2.0 - wall_height,
                ray_count + SCREEN_START, WINDOW_HEIGHT / 2.0 + wall_height,
                wall_shade);
      // Floor
      DrawLine (ray_count + SCREEN_START, WINDOW_HEIGHT / 2.0 + wall_height,
                ray_count + SCREEN_START, WINDOW_HEIGHT, floor_shade);

      ray_angle += (float)PLAYER_FOV / SCREEN_START * DEG2RAD;
    }
}
