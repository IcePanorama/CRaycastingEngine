#include "map.h"
#include "player.h"
#include "raylib.h"
#include "utils.h"
#include <linux/limits.h>
#include <math.h>
#include <stdio.h>

const int WINDOW_WIDTH = 1280 * 2;
const int WINDOW_HEIGHT = 1280;

void draw_3d_view (Player *player);

int
main (void)
{
  Player player
      = { { WINDOW_WIDTH / 4.0, WINDOW_HEIGHT / 2.0 }, 270 * DEG2RAD, 100.0 };

  InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT, "Raycasting Engine");

  SetTargetFPS (60);

  while (!WindowShouldClose ())
    {
      handle_player_input (&player);

      BeginDrawing ();
      ClearBackground (DARKGRAY);
      draw_2d_map (WINDOW_WIDTH); //, WINDOW_HEIGHT);
      draw_player (&player);
      draw_3d_view (&player);
      EndDrawing ();
    }

  CloseWindow ();

  return 0;
}

void
draw_3d_view (Player *player)
{
  // float start = player->angle - DEG2RAD * (PLAYER_FOV / 2.0);
  // float end = player->angle + DEG2RAD * (PLAYER_FOV / 2.0);
  // float angle_step = 0.5 * DEG2RAD + (0 * player->speed);

  // num_rays is just the FOV (when angle step is 1 deg)
  // has an inverse relationship with the angle step
  // e.g.) .5 deg step => 2 * FOV

  // float num_cols = (WINDOW_WIDTH / 2.0) / (PLAYER_FOV) + 0 * player->speed;
  // printf("%f\n", num_cols);
  int scaling_factor = (WINDOW_WIDTH / PLAYER_FOV);

  // want to find a multiplier for player FOV
  // that results in an even num of cols
  for (int col = 0; col < WINDOW_WIDTH / 2; col++)
    {
      float ray_angle = player->angle - (PLAYER_FOV / 2.0)
                        + (col / (WINDOW_WIDTH / 2.0)) * PLAYER_FOV;

      Vector2 wall;
      calculate_ray_length (&player->pos, &wall, ray_angle);
      float distance_to_wall = v2_distance (&player->pos, &wall);
    float corrected_dist = distance_to_wall * cos(ray_angle - player->angle);
      float wall_height = (WINDOW_HEIGHT / corrected_dist) * scaling_factor;
      //printf ("%f\n", wall_height);
      float wall_start = (WINDOW_HEIGHT - wall_height) / 2.0;
      float wall_end = wall_start + wall_height;

      int curr_col = scaling_factor * col + (WINDOW_WIDTH / 2);
      // Ceiling
      DrawRectangle(curr_col, 0, scaling_factor, wall_start, BLACK);
      // Wall
      DrawRectangle(curr_col, wall_start, scaling_factor, wall_end - wall_start, BLUE);
      // Floor
      DrawRectangle(curr_col, wall_end, scaling_factor, WINDOW_HEIGHT - wall_end, GREEN);
    }
}
