// clang-format off
#include <math.h>
#include <stdio.h>

#include "map.h"
#include "player.h"
#include "raylib.h"
#include "utils.h"
// clang-format on 

const int WINDOW_WIDTH = 1280 * 2;
const int WINDOW_HEIGHT = 1280;

Player player = { { WINDOW_WIDTH / 4.0, WINDOW_HEIGHT / 2.0}, 0, 100.0};

void draw_player (void);
void handle_player_input (void);

//TODO: restructure projects so headers and .c files are in the same folder
int
main (void)
{
  InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT, "Raycasting Engine");

  SetTargetFPS (60);

  while (!WindowShouldClose ())
    {
      ClearBackground(BLACK);
      handle_player_input ();
      BeginDrawing ();
      draw_2d_map (WINDOW_WIDTH);//, WINDOW_HEIGHT);
      draw_player ();
      EndDrawing ();
    }

  CloseWindow ();

  return 0;
}

void 
draw_player(void)
{
  DrawCircle(player.pos.x, player.pos.y, 25, RED);

  const int RAY_LEN = 200;
  float player_dx = cos(player.angle) * (RAY_LEN / 2);
  float player_dy = sin(player.angle) * (RAY_LEN / 2);
  DrawLine(player.pos.x, player.pos.y, player.pos.x + player_dx, player.pos.y + player_dy, ORANGE);

  // Left FOV Line
  player_dx = cos(player.angle - DEG2RAD * 30) * RAY_LEN;
  player_dy = sin(player.angle - DEG2RAD * 30) * RAY_LEN;
  float line_end_x = player.pos.x + player_dx;
  float line_end_y = player.pos.y + player_dy;

  DrawLine(player.pos.x, player.pos.y, line_end_x, line_end_y, WHITE);

  // Right FOV Line
  player_dx = cos(player.angle + DEG2RAD * 30) * RAY_LEN;
  player_dy = sin(player.angle + DEG2RAD * 30) * RAY_LEN;
  line_end_x = player.pos.x + player_dx;
  line_end_y = player.pos.y + player_dy;

  DrawLine(player.pos.x, player.pos.y, line_end_x, line_end_y, WHITE);
}

void
handle_player_input (void)
{
  if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
  {
    player.angle -= DEG2RAD * GetFrameTime() * player.speed;
  }
  if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
  {
    player.angle += DEG2RAD * GetFrameTime() * player.speed;
  }
}
