#include "map.h"
#include "player.h"
#include "raylib.h"

const int WINDOW_WIDTH = 480 * 2;
const int WINDOW_HEIGHT = 480;

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
      draw_2d_map (WINDOW_WIDTH);
      draw_player (&player);
      draw_3d_view (&player, WINDOW_WIDTH, WINDOW_HEIGHT);
      EndDrawing ();
    }

  CloseWindow ();

  return 0;
}
