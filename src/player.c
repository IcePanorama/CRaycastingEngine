#include "player.h"
#include "map.h"
#include "utils.h"
#include <math.h>
#include <raylib.h>

const int PLAYER_FOV = 90;

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
  // highlights the cell the player is in
  draw_cell (global_x_to_map_row (p->pos.x), global_y_to_map_col (p->pos.y),
             GREEN);

  DrawCircle (p->pos.x, p->pos.y, 25, RED);

  const int RAY_LEN = 200;
  float player_dx = cos (p->angle) * 100;
  float player_dy = sin (p->angle) * 100;
  DrawLine (p->pos.x, p->pos.y, p->pos.x + player_dx, p->pos.y + player_dy,
            ORANGE);

  float left_fov_angle = p->angle - DEG2RAD * (PLAYER_FOV / 2.0);

  float dx = cos (left_fov_angle) * (RAY_LEN / 100.0);
  float dy = sin (left_fov_angle) * (RAY_LEN / 100.0);
  float line_end_x = p->pos.x + dx;
  float line_end_y = p->pos.y + dy;

  while (!is_cell_wall (global_x_to_map_row (line_end_x),
                        global_y_to_map_col (line_end_y)))
    {
      line_end_x += dx;
      line_end_y += dy;
    }

  DrawLine (p->pos.x, p->pos.y, line_end_x, line_end_y, WHITE);

  float right_fov_angle = p->angle + DEG2RAD * (PLAYER_FOV / 2.0);
  dx = cos (right_fov_angle) * (RAY_LEN / 100.0);
  dy = sin (right_fov_angle) * (RAY_LEN / 100.0);
  line_end_x = p->pos.x + dx;
  line_end_y = p->pos.y + dy;

  while (!is_cell_wall (global_x_to_map_row (line_end_x),
                        global_y_to_map_col (line_end_y)))
    {
      line_end_x += dx;
      line_end_y += dy;
    }

  DrawLine (p->pos.x, p->pos.y, line_end_x, line_end_y, WHITE);
}
