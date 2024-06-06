#include "player.h"

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
