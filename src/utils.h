#ifndef _UTILS_H_
#define _UTILS_H_

#include <raylib.h>

float float_clamp (float value, float MIN, float MAX);
double distance (float ax, float ay, float bx, float by);
void calculate_ray_length (Vector2 *start, Vector2 *end, float angle);

#endif
