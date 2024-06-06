#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "raylib.h"

typedef struct Player
{
  Vector2 pos;
  double angle;
  double speed;
} Player;

void clamp_player_angle (Player *p);

#endif
