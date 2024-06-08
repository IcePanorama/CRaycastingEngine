#include "utils.h"
#include "map.h"
#include <math.h>

float
float_clamp (float value, const float MIN, const float MAX)
{
  float clamped_val = value < MIN ? MIN : value;
  return clamped_val > MAX ? MAX : clamped_val;
}

float
v2_distance (Vector2 *a, Vector2 *b)
{
  return sqrt ((b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y));
}

void
calculate_ray_length (Vector2 *start, Vector2 *end, float angle)
{
  const int RAY_LEN = 2;
  const int MAX_RANGE = 1000;
  float dx = cos (angle) * RAY_LEN;
  float dy = sin (angle) * RAY_LEN;
  end->x = start->x + dx;
  end->y = start->y + dy;

  int counter = 0;
  while (counter < MAX_RANGE
         && !is_cell_wall (global_x_to_map_row (end->x),
                           global_y_to_map_col (end->y)))
    {
      end->x += dx;
      end->y += dy;
      counter++;
    }
}
