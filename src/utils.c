#include "utils.h"

float
float_clamp (float value, const float MIN, const float MAX)
{
  value = value < MIN ? MIN : value;
  return value > MAX ? MAX : value;
}
