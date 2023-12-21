#ifndef PERLIN_H
#include <math.h>
#include <stdlib.h>
typedef struct Vector2 {
	float x, y;
} vector2;
int generatePerlin(int x, int y, int gridSize, float freq, float amp, int octaves, int seed);
#endif