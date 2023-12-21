#include "bitmap.h"
#include "perlin.h"
int *colorPixel(int hue) {
	int *rgb = malloc(sizeof(int) * 3);
	int waterBreakpoint = 120;
	int foamBreakpoint = 122;
	int sandBreakpoint = 140;
	int treeBreakpoint = 180;
	int mountainBreakpoint = 210;
	if (hue < waterBreakpoint) {
		rgb[0] = hue * 2;
		rgb[1] = 0;
		rgb[2] = 0;
	} else if (hue < foamBreakpoint) {
		rgb[0] = 255;
		rgb[1] = 255;
		rgb[2] = 255;
	} else if (hue < sandBreakpoint) {
		rgb[0] = 165 - (hue - waterBreakpoint) * 3.2;
		rgb[1] = 205 - (hue - waterBreakpoint) * 3.2;
		rgb[2] = 255 - (hue - waterBreakpoint) * 3.2;
	} else if (hue < treeBreakpoint) {
		rgb[0] = 0;
		rgb[1] = 300 - hue;
		rgb[2] = 0;
	} else if (hue < mountainBreakpoint) {
		rgb[0] = hue - 90;
		rgb[1] = hue - 90;
		rgb[2] = hue - 90;
	} else if (hue >= mountainBreakpoint) {
		rgb[0] = hue;
		rgb[1] = hue;
		rgb[2] = hue;
	}
	return rgb;
}
int main(int argc, char const *argv[]) {
	if (argc < 3) {
		printf("First argument is gridsize, second argument is seed.\n");
		printf("Example: ./perlin 400 42\n");
		return 0;
	}
	int seed = atoi(argv[2]);
	int gridSize = atoi(argv[1]);
	int width = 400;
	int height = 400;
	int colorPixels[width * height][3];
	int huePixels[width * height][3];
	int hue;
	int *rgb;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			hue = generatePerlin(x, y, gridSize, 1, 1, 12, seed);
			int hueList[3] = {hue, hue, hue};
			memcpy(huePixels[height * y + x], hueList, sizeof(int) * 3);

			rgb = colorPixel(hue);
			memcpy(colorPixels[height * y + x], rgb, sizeof(int) * 3);
			free(rgb);
		}
	}
	generateBitMap(width, height, colorPixels, "colorPerlin.bmp");
	generateBitMap(width, height, huePixels, "huePerlin.bmp");
	return 0;
}
