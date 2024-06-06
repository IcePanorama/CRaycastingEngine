#include "utils.h"
#include <math.h>

float
float_clamp (float value, const float MIN, const float MAX)
{
  float clamped_val = value < MIN ? MIN : value;
  return clamped_val > MAX ? MAX : clamped_val;
}

double
distance (float ax, float ay, float bx, float by)
{
  return sqrt (fabs ((ax * ax - bx * bx) + (ay * ay - by * by)));
}
