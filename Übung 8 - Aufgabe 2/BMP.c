#include "BMP.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
 * @file BMP.c
 * @brief Class for representing a bitmap file and draw a point, line,
 * barchart an a piechart on it
 *
 * @author Prof. Panitz & Stephanie Scholl
 * @note Matrikelnummer: 979993
 * @note Hochschule RheinMain
 *
 * @note Fach: Programmiermethoden- und Techniken
 * @note 2. Semester
 * @note Projektarbeit
 *
 * @note Professor: Sven Eric Panitz
 * @note Praktikumsleiter: Christian Lassmann
 *
 */

/**
 * Initializes a new BMP
 *
 * @param width Integer - width of the new BMP
 * @param height Integer - height of the new BMP
 *
 * @return Pointer to new BMP
 */
Bmp* newBmp(int width, int height) {
	Bmp* result = (Bmp*) malloc(sizeof(Bmp));
	result->imagedata = (Color*) malloc(sizeof(Color) * width * height);
	result->width = width;
	result->height = height;
	return result;
}

/**
 * Deletes a BMP and frees allocated space
 *
 * @param this Pointer - to actual Struct BMP
 *
 */
void deleteBmp(Bmp* this) {
	free(this->imagedata);
	free(this);
}

/**
 * Sets point on BMP
 *
 * @param this Bmp* - Pointer to actual Struct BMP
 * @param c Color - Color which needs to be painted
 * @param x Integer - coordinate for dot on x-aches
 * @param y Integer - coordinate for dot on y-aches
 *
 */
void setBmpPoint(Bmp* this, Color c, int x, int y) {
	if (!(x < 0 || x >= this->width || y < 0 || y >= this->height)) {
		this->imagedata[y * this->width + x] = c;
	}
}

/**
 * Writes byte in file
 *
 * @param out FILE* - Pointer of file we write to
 * @param ch unsigned char - char which needs to be written
 *
 */
void putByte(FILE* out, unsigned char ch) {
	fputc(ch, out);
}

/**
 * Writes short in file
 *
 * @param out FILE* - Pointer of file we write to
 * @param w unsigned short - short which needs to be written
 *
 */
void putShort(FILE* out, unsigned short w) {
	putByte(out, w & 0xff);
	putByte(out, (w >> 8) & 0xff);
}

/**
 * Writes long in file
 *
 * @param out FILE* - Pointer of file we write to
 * @param l unsigned int - Integer which needs to be written
 *
 */
void putLong(FILE* out, unsigned int l) {
	putByte(out, l & 0xff);
	putByte(out, (l >> 8) & 0xff);
	putByte(out, (l >> 16) & 0xff);
	putByte(out, (l >> 24) & 0xff);
}

/**
 * Writes color in file
 *
 * @param out FILE* - Pointer of file we write to
 * @param c Color - Writes Struct Color (.red, .green, . blue) to file
 *
 */
void putColor(FILE* out, Color c) {
	putByte(out, c.blue);
	putByte(out, c.green);
	putByte(out, c.red);
}

/**
 * Returns number of bytes per line
 *
 * @param this Bmp* - Pointer to actual BMP
 *
 * @return bytesPerLine Integer - number of bytes per line
 *
 */
int getBytesPerLines(Bmp* this) {
	long bytesPerLine = this->width * 3l; /* (for 24 bit images) */
	bytesPerLine = bytesPerLine + (4 - bytesPerLine % 4) % 4;
	return bytesPerLine;
}

/**
 * Writes the Struct BMP to a file
 *
 * @param this Bmp* - Pointer to actual Struct BMP
 * @param fileName char* - Name of file used
 *
 */
void writeBmpToFile(Bmp* this, char* fileName) {
	FILE* out = fopen(fileName, "wb");
	if (out == NULL) {
		printf("Error opening output file\n");
		exit(1);
	}
	putByte(out, 'B'); // "BM"-ID schreiben
	putByte(out, 'M');

	int headersize = 54L;
	int bytesPerLine = getBytesPerLines(this);
	int filesize = headersize + bytesPerLine * this->height;
	putLong(out, filesize);

	putShort(out, 0);
	putShort(out, 0);
	putLong(out, headersize);
	putLong(out, 0x28L);       //infoSize
	putLong(out, this->width);
	putLong(out, this->height);
	putShort(out, 1);          //biPlanes
	putShort(out, 24);         //bits
	putLong(out, 0);           //(no compression)
	putLong(out, 0);
	putLong(out, 0);
	putLong(out, 0);
	putLong(out, 0);
	putLong(out, 0);

	int line, colum;
	for (line = 0; line < this->height; line++) {
		for (colum = 0; colum < this->width; colum++) {
			putColor(out, this->imagedata[line * this->width + colum]);
		}
		int missingBytes = bytesPerLine - 3 * this->width;
		for (; missingBytes > 0; missingBytes--)
			putByte(out, 0);
	}
	fclose(out);
}

/**
 * Fills complete Background of bitmap with an color
 *
 * @param this Bmp* - Pointer to actual Struct BMP
 * @param c Color - Color which needs to be painted
 *
 */
void background(Bmp* this, Color c) {
	int i;
	/*Every index of this->imagedata is beeing colored in the same color*/
	for (i = 0; i < (this->width * this->height); i++) {
		this->imagedata[i] = c;
	}
}

/**
 * Places and fills an specific rectangle on BMP
 *
 * @param this Bmp* - Pointer to actual Struct BMP
 * @param c Color - Color which needs to be painted
 * @param x Integer - coordinate for start of rectangle on x-aches
 * @param y Integer - coordinate for start of rectangle on y-aches
 * @param w Integer - width of the rectangle
 * @param h Integer - height of the rectangle
 *
 */
void fillRect(Bmp* this, Color c, int x, int y, int w, int h) {
	int start, i, j;
	start = x;
	/*x achses (from start till width w is reached)*/
	for (i = start; i < start + w; i++) {
		/*y achses (from point y till height h is reached)*/
		for (j = y; j < y + h; j++) {
			setBmpPoint(this, c, i, j);
		}
	}
}

/**
 * Draws line on BMP (from one coordinate to another)
 *
 * @param this Bmp* - Pointer to actual Struct BMP
 * @param c Color - Color which needs to be painted
 * @param fromX Integer - coordinate for start of line on x-aches
 * @param fromY Integer - coordinate for start of line on y-aches
 * @param toX Integer - coordinate for end of line on x-aches
 * @param toY Integer - coordinate for end of line on y-aches
 *
 */
void drawLine(Bmp* this, Color c, int fromX, int fromY, int toX, int toY) {
	int dx = abs(toX - fromX);
	int sx = fromX < toX ? 1 : -1;
	int dy = abs(toY - fromY);
	int sy = fromY < toY ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;
	/*bresenham algorithm*/
	for (;;) {
		setBmpPoint(this, c, fromX, fromY);
		if (fromX == toX && fromY == toY) {
			break;
		}
		e2 = err;
		if (e2 > -dx) {
			err -= dy;
			fromX += sx;
		}
		if (e2 < dy) {
			err += dx;
			fromY += sy;
		}
	}
}

/**
 * Method for calculating the lowest x Value of a function
 *
 * @param minX double - lowest x value of the wished range
 * @param maxX double - highest x value of the wished range
 * @param f function* - forwarded function
 *
 * @return min double - lowest x value
 */
double min(double minX, double maxX, double f(double)) {
	double i;
	double min = f(minX); /* random min */

	/* looks in the Intervall for the lowest y-Value */
	for (i = minX; i <= maxX; i++) {
		if (f(i) < min) {
			min = f(i);
		}
	}
	return min;
}

/**
 * Method for calculating the highest x Value of a function
 *
 * @param minX double - lowest x value of the wished range
 * @param maxX double - highest x value of the wished range
 * @param f function* - forwarded function
 *
 * @return max double - highest x value
 */
double max(double minX, double maxX, double f(double)) {
	double i;
	double max = f(maxX); /* random max */

	/* looks in the Intervall for the highest y-Value */
	for (i = minX; i <= maxX; i++) {
		if (f(i) > max) {
			max = f(i);
		}
	}
	return max;
}

/**
 * Method for drawing a coordinate system onto the given bitmap
 *
 * @param this Bmp* - given bitmap
 * @param size const double - size of the given bitmap
 * @param minX double - lowest x value
 * @param minY double - lowest y value
 * @param skalX double - quotient for scaling the x achses
 * @param skalY double - quotient for scaling the y achses
 * @param margin int - margin
 *
 * @return p Point - Origin of the coordinate system (0/0)
 */
Point *drawCoordinateSystem(Bmp* this, const double size, double minX, double minY, double skalX, double skalY, int margin) {
	double i;
	Point *p = malloc(sizeof(Point));

	p->xValue = skalX * fabs(minX) + margin; /*x of origin*/
	p->yValue = skalY * fabs(minY) + margin; /*y of origin*/

	/*x achses*/
	drawLine(this, GRAY, margin, p->yValue, size - margin, p->yValue);
	/*y achses*/
	drawLine(this, GRAY, p->xValue, margin, p->xValue, size - margin);

	/*line for orientation on x achses*/
	if (skalX > 0) {
		/*positive side*/
		for (i = p->xValue; i <= size - margin; i += skalX) {
			drawLine(this, GRAY, i, p->yValue - 5, i, p->yValue + 5);
		}
		/*negative side*/
		for (i = p->xValue; i >= margin; i -= skalX) {
			drawLine(this, GRAY, i, p->yValue - 5, i, p->yValue + 5);
		}
	}
	/*line for orientation on y achses*/
	if (skalY > 0) {
		/*positive side*/
		for (i = p->yValue; i <= 1000 - 50; i += skalY) { /*eigentlich resolution-margin*/
			drawLine(this, GRAY, p->xValue - 5, i, p->xValue + 5, i);
		}
		/*negative side*/
		for (i = p->yValue; i >= 50; i -= skalY) { /*eigentlich margin*/
			drawLine(this, GRAY, p->xValue - 5, i, p->xValue + 5, i);
		}
	}
	return p;
}

/**
 * Draws one graph and coordinate system onto bitmap and returns it
 *
 * @param f function* double - Given function for drawing
 * @param minX double - lowest x value of the given range
 * @param maxX double - highest x value of the given range
 *
 * @return this Bmp* - finished bitmap
 */
Bmp* drawGraph(double f(double), double minX, double maxX) {
	const int size = 1000;
	Bmp* this = newBmp(size, size);
	background(this, WHITE);

	Point *origin; /*origin*/
	const double resolution = 900.0;
	const int margin = 50;
	double i;
	double minY, maxY;
	double skalY, skalX;

	/*break if limits are changed*/
	if (minX >= maxX) {
		return 0;
	}
	minY = min(minX, maxX, f);
	maxY = max(minX, maxX, f);

	/*scale factor*/
	skalX = resolution / fabs(maxX - minX);
	skalY = resolution / fabs(maxY - minY);

	origin = drawCoordinateSystem(this, size, minX, minY, skalX, skalY, margin);

	/*draw function within range minX and maxX*/
	for (i = minX; i < maxX; i += 0.01) {
		drawLine(this, BLACK, (origin->xValue) + (skalX * i),
				(origin->yValue) + (skalY * f(i)),
				(origin->xValue) + (skalX * (i + 0.01)),
				(origin->yValue) + (skalY * f(i + 0.01)));
	}
	free(origin);
	return this;
}

/**
 * Draws one graph of the given function, his derivations and one coordinate
 * system onto bitmap and returns it.
 *
 * @param f function* double - Given function for drawing
 * @param minX double - lowest x value of the given range
 * @param maxX double - highest x value of the given range
 * @param numberOfDiffs unsigned int - number of wished derivations
 *
 * @return this Bmp* - finished bitmap
 */
Bmp* drawGraphWithDiffs(double f(double), double minX, double maxX, unsigned int numberOfDiffs) {
	const int size = 1000;
	Bmp* this = newBmp(size, size);
	background(this, WHITE);
	Color colors[] = { BLACK, BLUE, GREEN, YELLOW, RED };

	Point *origin; /*origin*/
	const double resolution = 900.0;
	const int margin = 50;
	double i;
	int j;
	double minY, maxY;
	double skalY, skalX;

	/*break if limits are changed*/
	if (minX >= maxX) {
		return 0;
	}

	/*find maxY and invert it for minY*/
	maxY = max(minX, maxX, f);
	minY = -maxY;

	/*scale factor*/
	skalX = resolution / fabs(maxX - minX);
	skalY = resolution / fabs(maxY - minY);

	origin = drawCoordinateSystem(this, size, minX, minY, skalX, skalY, margin);

	/*draw function*/
	for (i = minX; i < maxX; i += 0.01) {
		drawLine(this, colors[0], (origin->xValue) + (skalX * i),
				(origin->yValue) + (skalY * f(i)),
				(origin->xValue) + (skalX * (i + 0.01)),
				(origin->yValue) + (skalY * f(i + 0.01)));
		/*draw derivations*/
		for (j = 1; j <= numberOfDiffs; j++) {
			drawLine(this, colors[j % (sizeof(colors) / sizeof(Color))],
					(origin->xValue) + (skalX * i),
					(origin->yValue) + (skalY * abN(f, i, j)),
					(origin->xValue) + (skalX * (i + 0.01)),
					(origin->yValue) + (skalY * abN(f, i + 0.01, j)));
		}
	}

	free(origin);
	return this;
}
/**
 * Calculates one derivation of a function
 *
 * @param f double - given function for derivation
 * @param x double - coordinate which needs to be derivated
 *
 * @return double - value of new x coordinate
 */

double ab(double f(double), double x) {
	const double deltaX = 0.001;
	/*usual derivation function*/
	return ((f(x + deltaX) - f(x)) / deltaX);
}

/**
 * n. derivation of a function
 *
 * @param f function* double - given function for derivation
 * @param x double - coordinate which needs to be derivated
 * @param n unsigned int - number of derivations wanted
 *
 * @return double - value of new coordinate
 */
double abN(double f(double), double x, unsigned int n) {
	double res = x;
	double ableitung(double x) {
		return ab(f, x);
	}
	/*if n equals 1, we need only one derivative of the function f*/
	if (n <= 1) {
		res = ab(f, res);
	} else {
		res = abN(ableitung, x, --n);
	}
	return res;
}

