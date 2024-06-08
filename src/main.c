#include "map.h"
#include "player.h"
#include "raylib.h"
#include "utils.h"
#include <math.h>
#include <stdbool.h>
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
  const int SCREEN_START = WINDOW_WIDTH / 2.0;
  float ray_angle = player->angle - (PLAYER_FOV / 2.0) * DEG2RAD;
  for (int ray_count = 0; ray_count < SCREEN_START; ray_count++)
    {
      Vector2 ray;
      calculate_ray_length (&player->pos, &ray, ray_angle);

      float dist = v2_distance (&player->pos, &ray);
      // fish-eye fix
      //dist *= cos (ray_angle - player->angle);

      int wall_height = (int)((WINDOW_WIDTH / 2.0) / dist * 50);

      DrawLine (ray_count + SCREEN_START, 0, ray_count + SCREEN_START,
                WINDOW_HEIGHT / 1.0 - wall_height, BLACK);
      DrawLine (ray_count + SCREEN_START, WINDOW_HEIGHT / 2.0 - wall_height,
                ray_count + SCREEN_START, WINDOW_HEIGHT / 2.0 + wall_height,
                BLUE);
      DrawLine (ray_count + SCREEN_START, WINDOW_HEIGHT / 2.0 + wall_height,
                ray_count + SCREEN_START, WINDOW_HEIGHT, GREEN);

      ray_angle += (float)PLAYER_FOV / SCREEN_START * DEG2RAD;
    }
}
