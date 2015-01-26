#include "BMP.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Bmp* newBmp(int width, int height) {
	Bmp* result = (Bmp*) malloc(sizeof(Bmp));
	result->imagedata = (Color*) malloc(sizeof(Color) * width * height);
	result->width = width;
	result->height = height;
	return result;
}
void deleteBmp(Bmp* this) {
	free(this->imagedata);
	free(this);
}

void setBmpPoint(Bmp* this, Color c, int x, int y) {
	if (!(x < 0 || x >= this->width || y < 0 || y >= this->height)) {
		this->imagedata[y * this->width + x] = c;
	}
}

void putByte(FILE* out, unsigned char ch) {
	fputc(ch, out);
}

void putShort(FILE* out, unsigned short w) {
	putByte(out, w & 0xff);
	putByte(out, (w >> 8) & 0xff);
}

void putLong(FILE* out, unsigned int l) {
	putByte(out, l & 0xff);
	putByte(out, (l >> 8) & 0xff);
	putByte(out, (l >> 16) & 0xff);
	putByte(out, (l >> 24) & 0xff);
}

void putColor(FILE* out, Color c) {
	putByte(out, c.blue);
	putByte(out, c.green);
	putByte(out, c.red);
}

int getBytesPerLines(Bmp* this) {
	long bytesPerLine = this->width * 3l; /* (for 24 bit images) */
	bytesPerLine = bytesPerLine + (4 - bytesPerLine % 4) % 4;
	return bytesPerLine;
}
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
	putLong(out, 0);            //(no compression)
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

void background(Bmp* this, Color c) {
	int i;
	for (i = 0; i < (this->width * this->height); i++) {
		this->imagedata[i] = c;
	}
}

/*http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C*/
void drawLine(Bmp* this, Color c, int fromX, int fromY, int toX, int toY) {
	int dx = abs(toX - fromX);
	int sx = fromX < toX ? 1 : -1;
	int dy = abs(toY - fromY);
	int sy = fromY < toY ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

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

void fillCircle(Bmp* this, Color c, int x, int y, int radius) {
	int i, j;

	for (i = -radius; i <= radius; i++) {
		for (j = -radius; j <= radius; j++) {
			if (j * j + i * i <= radius * radius) {
				setBmpPoint(this, c, x + j, y + i);
			}
		}
	}
}
/* looks in the Intervall for the lowest and highest y-Value */
double min(double minX, double maxX, double (f)(double)) {
	double i;
	double min = f(minX); /* random min */

	/* looks in the Intervall for the lowest and highest y-Value */
	for (i = minX; i <= maxX; i++) {
		if (f(i) < min) {
			min = f(i);
		}
	}
	return min;
}
double max(double minX, double maxX, double (f)(double)) {
	double i;
	double max = f(maxX); /* random max */

	/* looks in the Intervall for the lowest and highest y-Value */
	for (i = minX; i <= maxX; i++) {
		if (f(i) > max) {
			max = f(i);
		}
	}
	return max;
}
Point *drawCoordinateSystem(Bmp* this, const double size, double minX,
		double minY, double skalX, double skalY, int margin) {
	double i;
	Point *p = malloc(sizeof(Point));

	p->xValue = skalX * fabs(minX) + margin; /*x of origin*/
	p->yValue = skalY * fabs(minY) + margin; /*y of origin*/

	/*x*/
	drawLine(this, GRAY, margin, p->yValue, size - margin, p->yValue);
	/*y*/
	drawLine(this, GRAY, p->xValue, margin, p->xValue, size - margin);

	/*orientierungslinien für x negativbereich*/
	if (skalX > 0) {
		for (i = p->xValue; i <= size - margin; i += skalX) {
			drawLine(this, GRAY, i, p->yValue - 5, i, p->yValue + 5);
		}
		for (i = p->xValue; i >= margin; i -= skalX) {
			drawLine(this, GRAY, i, p->yValue - 5, i, p->yValue + 5);
		}
	}
	/*orientierungslinien für y*/
	if (skalY > 0) {
		for (i = p->yValue; i <= 1000 - 50; i += skalY) { /*eigentlich resolution-margin*/
			drawLine(this, GRAY, p->xValue - 5, i, p->xValue + 5, i);
		}
		for (i = p->yValue; i >= 50; i -= skalY) { /*eigentlich margin*/
			drawLine(this, GRAY, p->xValue - 5, i, p->xValue + 5, i);
		}
	}
	return p;
}

Bmp* drawGraph(double (f)(double), double minX, double maxX) {
	const int size = 1000;
	Bmp* this = newBmp(size, size);
	background(this, WHITE);

	Point *origin; /*origin*/
	const double resolution = 900.0;
	const int margin = 50;
	double i;
	double minY, maxY;
	double skalY, skalX;

	if (minX >= maxX) {
		return 0;
	}
	minY = min(minX, maxX, f);
	maxY = max(minX, maxX, f);

	skalX = resolution / fabs(maxX - minX);
	skalY = resolution / fabs(maxY - minY);

	origin = drawCoordinateSystem(this, size, minX, minY, skalX, skalY, margin);

	for (i = minX; i < maxX; i += 0.01) {
		drawLine(this, BLACK, (origin->xValue) + (skalX * i),
				(origin->yValue) + (skalY * f(i)),
				(origin->xValue) + (skalX * (i + 0.01)),
				(origin->yValue) + (skalY * f(i + 0.01)));
	}
	free(origin);
	return this;
}

Bmp* drawGraphWithDiffs(double (f)(double), double minX, double maxX,
		unsigned int numberOfDiffs) {
	const int size = 1000;
	Bmp* this = newBmp(size, size);
	background(this, WHITE);
	Color colors[] = { BLACK, BLUE, GREEN, YELLOW, RED };
	int colorsSize = 5;

	Point *origin; /*origin*/
	const double resolution = 900.0;
	const int margin = 50;
	double i;
	int j;
	double minY, maxY;
	double skalY, skalX;

	if (minX >= maxX) {
		return 0;
	}
	maxY = max(minX, maxX, f);
	minY = -maxY;
	/*for (i = 1; i <= numberOfDiffs; i++) {
		if (minY > abN(f, minY, i)) {
			minY = abN(f, minY, i);
		}
		if (maxY < abN(f, maxY, i)) {
			maxY = abN(f, maxY, i);
		}
	}*/

	skalX = resolution / fabs(maxX - minX);
	skalY = resolution / fabs(maxY - minY);

	origin = drawCoordinateSystem(this, size, minX, minY, skalX, skalY, margin);

	/*Funktion zeichnen*/
	for (i = minX; i < maxX; i += 0.01) {
		drawLine(this, colors[0], (origin->xValue) + (skalX * i),
				(origin->yValue) + (skalY * f(i)),
				(origin->xValue) + (skalX * (i + 0.01)),
				(origin->yValue) + (skalY * f(i + 0.01)));
		/*Ableitungen zeichnen*/
		for (j = 1; j <= numberOfDiffs; j++) {
			drawLine(this, colors[j % colorsSize],
					(origin->xValue) + (skalX * i),
					(origin->yValue) + (skalY * abN(f, i, j)),
					(origin->xValue) + (skalX * (i + 0.01)),
					(origin->yValue) + (skalY * abN(f, i + 0.01, j)));
		}
	}

	free(origin);
	return this;
}

double ab(double (f)(double), double x) {
	const double deltaX = 0.001;
	return ((f(x + deltaX) - f(x)) / deltaX);
}

double abN(double (f)(double), double x, unsigned int n) {
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

