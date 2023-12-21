#include "bitmap.h"
#define HEADER_SIZE 54
// Something is wrong, as some width and heights do not work
void writeBMP(char *header, unsigned char *pixels, int width, int height, const char *fileName) {
	FILE *fout = fopen(fileName, "wb");
	fwrite(header, 1, HEADER_SIZE, fout);
	fwrite(pixels, 1, width * height * 3, fout);
	fclose(fout);

	free(pixels);
	free(header);
}
unsigned char *populatePixels(int width, int height, int input[width * height][3]) {
	int size = width * height * 3; // 3 bytes per pixel (no alpha channel)
	unsigned char *pixels = malloc(size);
	int a = 0;
	for (int row = height - 1; row >= 0; row--) {
		for (int column = 0; column < width; column++) {
			int p = (row * width + column) * 3;
			pixels[p + 0] = input[a][0];
			pixels[p + 1] = input[a][1];
			pixels[p + 2] = input[a][2];
			a++;
		}
	}
	return pixels;
}
char *createHeader(int width, int height) {
	char *header = calloc(HEADER_SIZE, sizeof(char));

	// Bitmap signature
	strcpy(header, "BM");

	// File size
	int size = width * height;
	*((int *)&header[2]) = HEADER_SIZE + size;

	// Offset to pixel array
	*((int *)&header[10]) = HEADER_SIZE;

	// DIB header size
	*((int *)&header[14]) = 40;

	// Image width and height
	*((int *)&header[18]) = width;
	*((int *)&header[22]) = height;

	// Planes (1) and Bits per Pixel (24)
	*((short *)&header[26]) = 1;
	*((short *)&header[28]) = 24;

	// Image Size
	*((int *)&header[34]) = size;

	return header;
}
void generateBitMap(int width, int height, int input[width * height][3], const char *fileName) {
	char *header = createHeader(width, height);
	unsigned char *pixels = populatePixels(width, height, input);
	writeBMP(header, pixels, width, height, fileName);
}