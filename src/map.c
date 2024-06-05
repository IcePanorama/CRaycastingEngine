#include "map.h"
#include "raylib.h"

#define MAP_WIDTH 9
#define MAP_HEIGHT 9

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

void 
draw_2d_map(const int WINDOW_WIDTH)//, const int WINDOW_HEIGHT)
{
  const int SIZE = (WINDOW_WIDTH / 2) / MAP_WIDTH + 1;
  for (int i = 0; i < MAP_WIDTH; i++)
  {
    for (int j = 0; j < MAP_HEIGHT; j++)
    {
      Color color = map[i][j] == 1 ? YELLOW : GRAY;
      // +1, -2 for showing grid lines
      DrawRectangle(i*SIZE + 1, j*SIZE + 1, SIZE - 2, SIZE - 2, color);
    }
  }
}

