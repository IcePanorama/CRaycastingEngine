#include "map.h"
#include "utils.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>

#define MAP_WIDTH 9
#define MAP_HEIGHT 9
#define TEXTURE_WIDTH 8
#define TEXTURE_HEIGHT 8

/* clang-format off */
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

char test_texture[TEXTURE_WIDTH][TEXTURE_HEIGHT] = {
  { 1, 0, 1, 0, 1, 0, 1, 0},
  { 0, 1, 0, 1, 0, 1, 0, 1},
  { 1, 0, 1, 0, 1, 0, 1, 0},
  { 0, 1, 0, 1, 0, 1, 0, 1},
  { 1, 0, 1, 0, 1, 0, 1, 0},
  { 0, 1, 0, 1, 0, 1, 0, 1},
  { 1, 0, 1, 0, 1, 0, 1, 0},
  { 0, 1, 0, 1, 0, 1, 0, 1},
};
/* clang-format on */

int window_width;

void apply_color_shading (Color *wall_shade, float shade_factor);

void
draw_2d_map (const int WINDOW_WIDTH)
{
  window_width = WINDOW_WIDTH;
  for (int i = 0; i < MAP_WIDTH; i++)
    {
      for (int j = 0; j < MAP_HEIGHT; j++)
        {
          Color color = map[i][j] == 1 ? YELLOW : GRAY;
          draw_cell (i, j, color);
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
  const int SIZE = get_cell_size ();
  DrawRectangle (i * SIZE, j * SIZE, SIZE - 2, SIZE - 2, color);
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
  return row * get_cell_size ();
}

float
map_col_to_global_y (int col)
{
  return col * get_cell_size ();
}

void
get_cell_center (Vector2 *center, int row, int col)
{
  center->x = map_row_to_global_x (row);
  center->y = map_col_to_global_y (col);
}

bool
is_cell_wall (int i, int j)
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
  // View plane dist should be a func of the window size
  // TODO: figure out such a formula
  const float VIEW_PLANE_DIST = 30.0;
  const int SCREEN_START = WINDOW_WIDTH / 2.0;
  float ray_angle = player->angle - (PLAYER_FOV / 2.0) * DEG2RAD;
  for (int ray_count = 0; ray_count < SCREEN_START; ray_count++)
    {
      Vector2 ray;
      calculate_ray_length (&player->pos, &ray, ray_angle);

      float dist = v2_distance (&player->pos, &ray);
      dist *= cos (ray_angle - player->angle);

      int wall_height = (int)(SCREEN_START / dist * VIEW_PLANE_DIST);

      // the denominator here is likely a product of something
      // either the view plane distance or the window size or
      // something like that. Try to figure out a formula for
      // this so that this isn't as hard-coded.
      float shade_factor = 1.0 - (dist / 500);
      if (shade_factor < 0.0)
        {
          shade_factor = 0.0;
        }

      // Walls
      for (int y = WINDOW_HEIGHT / 2.0 - wall_height;
           y <= WINDOW_HEIGHT / 2.0 + wall_height; y++)
        {
          // How do I get this to scale over a distance??
          // probably need to figure out what wall cell we're looking at
          // and then draw that entire cell (?)
          int text_x = ((int)((ray_count - TEXTURE_WIDTH) / TEXTURE_WIDTH)
                        % TEXTURE_WIDTH);
          int text_y = ((int)((y - TEXTURE_HEIGHT) / TEXTURE_HEIGHT)
                        % TEXTURE_HEIGHT);

          Color wall_shade;
          if (test_texture[text_x][text_y] == 1)
            {
              wall_shade = WHITE;
            }
          else
            {
              wall_shade = BLACK;
            }

          apply_color_shading (&wall_shade, shade_factor);
          DrawPixel (ray_count + SCREEN_START, y, wall_shade);
        }

      // Floor
      for (int y = WINDOW_HEIGHT / 2.0 + wall_height; y <= WINDOW_HEIGHT; y++)
        {
          Color floor_shading = GREEN;
          // apply_color_shading (&floor_shading, shade_factor);

          DrawPixel (ray_count + SCREEN_START, y, floor_shading);
        }

      ray_angle += (float)PLAYER_FOV / SCREEN_START * DEG2RAD;
    }
}

void
apply_color_shading (Color *wall_shade, float shade_factor)
{
  *wall_shade = (Color){ (int)(wall_shade->r * shade_factor),
                         (int)(wall_shade->g * shade_factor),
                         (int)(wall_shade->b * shade_factor), wall_shade->a };
}
