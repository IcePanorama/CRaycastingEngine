#include "player.h"
#include "raylib.h"
#include <math.h>

void Draw2DMap (void);
void DrawPlayer (void);

// clang-format off
char map[8][8] = {
  { 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 0, 0, 0, 0, 0, 0, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1 }
};
// clang-format on 

const int WINDOW_WIDTH = 1280 * 2;
const int WINDOW_HEIGHT = 1280;

Player player = { { WINDOW_WIDTH / 4.0, WINDOW_HEIGHT / 2.0}, 0};

int
main (void)
{
  InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT, "This is a test.");

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
  const int SIZE = (WINDOW_WIDTH / 2) / 8;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      Color color = map[i][j] == 1 ? YELLOW : GRAY;
      DrawRectangle(i*SIZE, j*SIZE, SIZE, SIZE, color);
    }
  }
}

void 
DrawPlayer(void)
{
  DrawCircle(player.pos.x, player.pos.y, 25, RED);
  float playerDx = cos(player.angle) * 10;
  float playerDy = sin(player.angle) * 10;
  DrawLine(player.pos.x, player.pos.y, player.pos.x + playerDx * 5, player.pos.y + playerDy * 5, ORANGE);
}
