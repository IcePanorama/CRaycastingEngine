#ifndef _UTILS_H_
#define _UTILS_H_

#include <raylib.h>

float float_clamp (float value, float MIN, float MAX);
void calculate_ray_length (Vector2 *start, Vector2 *end, float angle);
float v2_distance (Vector2 *a, Vector2 *b);

#endif
