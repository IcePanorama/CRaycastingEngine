#include "player.h"
#include "raylib.h"
#include <math.h>

#define MAP_WIDTH 9
#define MAP_HEIGHT 9

void Draw2DMap (void);
void DrawPlayer (void);

// clang-format off
char map[MAP_WIDTH][MAP_HEIGHT] = {
  { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};
// clang-format on 

const int WINDOW_WIDTH = 1280 * 2;
const int WINDOW_HEIGHT = 1280;

Player player = { { WINDOW_WIDTH / 4.0, WINDOW_HEIGHT / 2.0}, 0};

int
main (void)
{
  InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT, "Raycasting Engine");

  SetTargetFPS (60);

  while (!WindowShouldClose ())
    {
      BeginDrawing ();

      Draw2DMap();
      DrawPlayer();

      EndDrawing ();
    }

  CloseWindow ();

  return 0;
}

void 
Draw2DMap(void)
{
  const int SIZE = (WINDOW_WIDTH / 2) / MAP_WIDTH;
  for (int i = 0; i < MAP_WIDTH; i++)
  {
    for (int j = 0; j < MAP_HEIGHT; j++)
    {
      Color color = map[i][j] == 1 ? YELLOW : GRAY;
      DrawRectangle(i*SIZE, j*SIZE, SIZE, SIZE, color);
    }
  }
}

void 
DrawPlayer(void)
{
  const int RAY_LEN = 100;
  DrawCircle(player.pos.x, player.pos.y, 25, RED);

  float playerDx = cos(player.angle) * RAY_LEN;
  float playerDy = sin(player.angle) * RAY_LEN;
  DrawLine(player.pos.x, player.pos.y, player.pos.x + playerDx, player.pos.y + playerDy, ORANGE);

  playerDx = cos(player.angle - DEG2RAD * 30) * RAY_LEN;
  playerDy = sin(player.angle - DEG2RAD * 30) * RAY_LEN;
  DrawLine(player.pos.x, player.pos.y, player.pos.x + playerDx, player.pos.y + playerDy, WHITE);

  playerDx = cos(player.angle + DEG2RAD * 30) * RAY_LEN;
  playerDy = sin(player.angle + DEG2RAD * 30) * RAY_LEN;
  DrawLine(player.pos.x, player.pos.y, player.pos.x + playerDx, player.pos.y + playerDy, WHITE);
}
