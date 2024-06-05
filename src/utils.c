#include "utils.h"

float
float_clamp (float value, const float MIN, const float MAX)
{
  float clamped_val = value < MIN ? MIN : value;
  return clamped_val > MAX ? MAX : clamped_val;
}
