#include "perlin.h"
vector2 randomGradient(int ix, int iy, int seed) {
	// Hashing function (crazy math)
	const unsigned w = 8 * sizeof(unsigned);
	const unsigned s = w / 2;
	unsigned a = ix + seed, b = iy + seed;
	a *= 3284157443;

	b ^= a << s | a >> (w - s);
	b *= 1911520717;

	a ^= b << s | b >> (w - s);
	a *= 2048419325;
	float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]

	vector2 v;
	v.x = sin(random);
	v.y = cos(random);

	return v;
}
float dotGridGradient(int ix, int iy, float x, float y, int seed) {
	// Get the dot grid gradient product
	vector2 gradient = randomGradient(ix, iy, seed);
	float dx = x - (float)ix;
	float dy = y - (float)iy;

	return (dx * gradient.x + dy * gradient.y);
}
float interpolate(float a0, float a1, float w) {
	return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}
float perlin(float x, float y, int seed) {
	// Determine grid cell corner coordinates (floor them)
	int x0 = (int)x;
	int y0 = (int)y;

	// Add 1 to get to other side of current gridbox
	int x1 = x0 + 1;
	int y1 = y0 + 1;

	// Compute Interpolation weights
	float sx = x - (float)x0;
	float sy = y - (float)y0;

	// Compute and interpolate top two corners
	float n0 = dotGridGradient(x0, y0, x, y, seed);
	float n1 = dotGridGradient(x1, y0, x, y, seed);
	float ix0 = interpolate(n0, n1, sx);

	// Compute and interpolate bot two corners
	n0 = dotGridGradient(x0, y1, x, y, seed);
	n1 = dotGridGradient(x1, y1, x, y, seed);
	float ix1 = interpolate(n0, n1, sx);

	// Interpolate between the two previous interpolated values, now in y
	float value = interpolate(ix0, ix1, sy);
	return value;
}
int brown(int x, int y, int gridSize, float freq, float amp, int octaves, int seed) {
	float val = 0;
	for (int i = 0; i < octaves; i++) {
		val += perlin(x * freq / gridSize, y * freq / gridSize, seed) * amp;
		freq *= 2;
		amp /= 2;
	}
	// Clipping
	if (val > 1.0f) {
		val = 1.0f;
	} else if (val < -1.0f) {
		val = -1.0f;
	}
	int hue = (int)(((val + 1.0f) * 0.5f) * 255);
	return hue;
}

int generatePerlin(int x, int y, int gridSize, float freq, float amp, int octaves, int seed) {
	return brown(x, y, gridSize, freq, amp, octaves, seed);
}