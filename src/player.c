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

  /* Center FOV Line */
  float player_dx = cos (p->angle) * 100;
  float player_dy = sin (p->angle) * 100;
  DrawLine (p->pos.x, p->pos.y, p->pos.x + player_dx, p->pos.y + player_dy,
            ORANGE);

  /* Left FOV Line */
  Vector2 line_end;
  float left_fov_angle = p->angle - DEG2RAD * (PLAYER_FOV / 2.0);
  calculate_ray_length (&p->pos, &line_end, left_fov_angle);
  DrawLine (p->pos.x, p->pos.y, line_end.x, line_end.y, WHITE);

  /* Right FOV Line */
  float right_fov_angle = p->angle + DEG2RAD * (PLAYER_FOV / 2.0);
  calculate_ray_length (&p->pos, &line_end, right_fov_angle);
  DrawLine (p->pos.x, p->pos.y, line_end.x, line_end.y, WHITE);
}
