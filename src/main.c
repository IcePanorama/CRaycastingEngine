#include "raylib.h"
#include <stdio.h>

int
main (void)
{
  puts ("hello world!");

  const int WINDOW_WIDTH = 1280;
  const int WINDOW_HEIGHT = 960;

  InitWindow (WINDOW_WIDTH, WINDOW_HEIGHT, "This is a test.");

  SetTargetFPS (60);

  while (!WindowShouldClose ())
    {
      BeginDrawing ();
      ClearBackground (RAYWHITE);
      DrawText ("Hello world.", 190, 200, 20, LIGHTGRAY);
      EndDrawing ();
    }

  CloseWindow ();

  return 0;
}
