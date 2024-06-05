// clang-format off
#include <math.h>

#include "map.h"
#include "player.h"
#include "raylib.h"
#include "utils.h"
// clang-format on 

const int WINDOW_WIDTH = 1280 * 2;
const int WINDOW_HEIGHT = 1280;

Player player = { { WINDOW_WIDTH / 4.0, WINDOW_HEIGHT / 2.0}, 0};

void DrawPlayer (void);

int
main (void)
{
  InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT, "Raycasting Engine");

  SetTargetFPS (60);

  while (!WindowShouldClose ())
    {
      BeginDrawing ();
      Draw2DMap(WINDOW_WIDTH);//, WINDOW_HEIGHT);
      DrawPlayer();
      EndDrawing ();
    }

  CloseWindow ();

  return 0;
}

void 
DrawPlayer(void)
{
  DrawCircle(player.pos.x, player.pos.y, 25, RED);

  const int RAY_LEN = 100;
  float player_dx = cos(player.angle) * RAY_LEN;
  float player_dy = sin(player.angle) * RAY_LEN;
  DrawLine(player.pos.x, player.pos.y, player.pos.x + player_dx, player.pos.y + player_dy, ORANGE);

  // Left FOV Line
  player_dx = cos(player.angle - DEG2RAD * 30) * RAY_LEN * RAY_LEN;
  player_dy = sin(player.angle - DEG2RAD * 30) * RAY_LEN * RAY_LEN;
  float line_end_x = float_clamp(player.pos.x + player_dx, 0, WINDOW_WIDTH / 2.0);
  float line_end_y = float_clamp(player.pos.y + player_dy, 0, WINDOW_WIDTH / 2.0);
  DrawLine(player.pos.x, player.pos.y, line_end_x, line_end_y, WHITE);

  // Right FOV Line
  player_dx = cos(player.angle + DEG2RAD * 30) * RAY_LEN * RAY_LEN;
  player_dy = sin(player.angle + DEG2RAD * 30) * RAY_LEN * RAY_LEN;
  line_end_x = float_clamp(player.pos.x + player_dx, 0, WINDOW_WIDTH / 2.0);
  line_end_y = float_clamp(player.pos.y + player_dy, 0, WINDOW_WIDTH / 2.0);
  DrawLine(player.pos.x, player.pos.y, line_end_x, line_end_y, WHITE);
}
