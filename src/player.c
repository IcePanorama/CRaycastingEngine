#include "player.h"
#include "map.h"
#include <math.h>

void
clamp_player_angle (Player *p)
{
  if (p->angle < 0)
    {
      p->angle += 2 * PI;
    }
  else if (p->angle > 2 * PI)
    {
      p->angle -= 2 * PI;
    }
}

void
handle_player_input (Player *p)
{
  if (IsKeyDown (KEY_A) || IsKeyDown (KEY_LEFT))
    {
      p->angle -= DEG2RAD * GetFrameTime () * p->speed;
      clamp_player_angle (p);
    }
  if (IsKeyDown (KEY_D) || IsKeyDown (KEY_RIGHT))
    {
      p->angle += DEG2RAD * GetFrameTime () * p->speed;
      clamp_player_angle (p);
    }
  if (IsKeyDown (KEY_W) || IsKeyDown (KEY_UP))
    {
      p->pos.x += cos (p->angle) * p->speed * GetFrameTime ();
      p->pos.y += sin (p->angle) * p->speed * GetFrameTime ();
    }
  if (IsKeyDown (KEY_S) || IsKeyDown (KEY_DOWN))
    {
      p->pos.x -= cos (p->angle) * p->speed * GetFrameTime ();
      p->pos.y -= sin (p->angle) * p->speed * GetFrameTime ();
    }
}

void
draw_player (Player *p)
{
  draw_cell (global_x_to_map_row (p->pos.x), global_y_to_map_col (p->pos.y),
             GREEN);
  DrawCircle (p->pos.x, p->pos.y, 25, RED);

  const int RAY_LEN = 200;
  float player_dx = cos (p->angle) * (RAY_LEN / 2.0);
  float player_dy = sin (p->angle) * (RAY_LEN / 2.0);
  DrawLine (p->pos.x, p->pos.y, p->pos.x + player_dx, p->pos.y + player_dy,
            ORANGE);

  // Left FOV Line
  player_dx = cos (p->angle - DEG2RAD * 30) * RAY_LEN;
  player_dy = sin (p->angle - DEG2RAD * 30) * RAY_LEN;
  float line_end_x = p->pos.x + player_dx;
  float line_end_y = p->pos.y + player_dy;

  DrawLine (p->pos.x, p->pos.y, line_end_x, line_end_y, WHITE);

  // Right FOV Line
  player_dx = cos (p->angle + DEG2RAD * 30) * RAY_LEN;
  player_dy = sin (p->angle + DEG2RAD * 30) * RAY_LEN;
  line_end_x = p->pos.x + player_dx;
  line_end_y = p->pos.y + player_dy;

  DrawLine (p->pos.x, p->pos.y, line_end_x, line_end_y, WHITE);
}
