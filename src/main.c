#include "raylib.h"
#include <stdio.h>

void Draw2DMap (void);

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

int
main (void)
{
  const int WINDOW_WIDTH = 1280;
  const int WINDOW_HEIGHT = 960;


  printf("%c\n", map[0][0]);

  InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT, "This is a test.");

  SetTargetFPS (60);

  while (!WindowShouldClose ())
    {
      BeginDrawing ();

      Draw2DMap();

      EndDrawing ();
    }

  CloseWindow ();

  return 0;
}

void 
Draw2DMap(void)
{
  const int SIZE = 100;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      Color color = map[i][j] == 1 ? YELLOW : GRAY;
      DrawRectangle(i*SIZE, j*SIZE, SIZE, SIZE, color);
    }
  }
}
