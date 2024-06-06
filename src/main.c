#include <math.h>
#include <stdio.h>

#include "map.h"
#include "player.h"
#include "raylib.h"

const int WINDOW_WIDTH = 1280 * 2;
const int WINDOW_HEIGHT = 1280;

Player player
    = { { WINDOW_WIDTH / 4.0, WINDOW_HEIGHT / 2.0 }, 270 * DEG2RAD, 100.0 };

void draw_player (void);
void handle_player_input (void);

int
main (void)
{
  InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT, "Raycasting Engine");

  SetTargetFPS (60);

  while (!WindowShouldClose ())
    {
      handle_player_input ();

      BeginDrawing ();
      ClearBackground (BLACK);
      draw_2d_map (WINDOW_WIDTH); //, WINDOW_HEIGHT);
      draw_player ();
      EndDrawing ();
    }

  CloseWindow ();

  return 0;
}

void
draw_player (void)
{
  draw_cell (global_x_to_map_row (player.pos.x),
             global_y_to_map_col (player.pos.y), GREEN);
  DrawCircle (player.pos.x, player.pos.y, 25, RED);

  const int RAY_LEN = 200;
  float player_dx = cos (player.angle) * (RAY_LEN / 2.0);
  float player_dy = sin (player.angle) * (RAY_LEN / 2.0);
  DrawLine (player.pos.x, player.pos.y, player.pos.x + player_dx,
            player.pos.y + player_dy, ORANGE);

  // Left FOV Line
  player_dx = cos (player.angle - DEG2RAD * 30) * RAY_LEN;
  player_dy = sin (player.angle - DEG2RAD * 30) * RAY_LEN;
  float line_end_x = player.pos.x + player_dx;
  float line_end_y = player.pos.y + player_dy;

  DrawLine (player.pos.x, player.pos.y, line_end_x, line_end_y, WHITE);

  // Right FOV Line
  player_dx = cos (player.angle + DEG2RAD * 30) * RAY_LEN;
  player_dy = sin (player.angle + DEG2RAD * 30) * RAY_LEN;
  line_end_x = player.pos.x + player_dx;
  line_end_y = player.pos.y + player_dy;

  DrawLine (player.pos.x, player.pos.y, line_end_x, line_end_y, WHITE);
}

void
handle_player_input (void)
{
  if (IsKeyDown (KEY_A) || IsKeyDown (KEY_LEFT))
    {
      player.angle -= DEG2RAD * GetFrameTime () * player.speed;
      clamp_player_angle (&player);
    }
  if (IsKeyDown (KEY_D) || IsKeyDown (KEY_RIGHT))
    {
      player.angle += DEG2RAD * GetFrameTime () * player.speed;
      clamp_player_angle (&player);
    }
  if (IsKeyDown (KEY_W) || IsKeyDown (KEY_UP))
    {
      player.pos.x += cos (player.angle) * player.speed * GetFrameTime ();
      player.pos.y += sin (player.angle) * player.speed * GetFrameTime ();
    }
  if (IsKeyDown (KEY_S) || IsKeyDown (KEY_DOWN))
    {
      player.pos.x -= cos (player.angle) * player.speed * GetFrameTime ();
      player.pos.y -= sin (player.angle) * player.speed * GetFrameTime ();
    }
}
