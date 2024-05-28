#include "raylib.h"

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

Vector2 PlayerPos = { WINDOW_WIDTH / 4.0, WINDOW_HEIGHT / 2.0};

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
  DrawCircle(PlayerPos.x, PlayerPos.y, 25, RED);
}
