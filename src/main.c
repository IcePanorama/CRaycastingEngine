#include "map.h"
#include "player.h"
#include "raylib.h"

const int WINDOW_WIDTH = 1280 * 2;
const int WINDOW_HEIGHT = 1280;

// void draw_3d_view (Player* player);

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
      ClearBackground (BLACK);
      draw_2d_map (WINDOW_WIDTH); //, WINDOW_HEIGHT);
      draw_player (&player);
      // draw_3d_view (&player);
      EndDrawing ();
    }

  CloseWindow ();

  return 0;
}
/*
void
draw_3d_view (Player* player)
{
  float start = player->angle - DEG2RAD * (PLAYER_FOV / 2.0);
  float end = player->angle + DEG2RAD * (PLAYER_FOV / 2.0);
  for (float a = start; start < end; start += DEG2RAD)
  {
  }
}*/
