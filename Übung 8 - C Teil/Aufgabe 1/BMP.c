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
	for (i = start; i < start + w; i++) {
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
	int i, tmp;

	if (fromX == toX && fromY == toY) {
		setBmpPoint(this, c, fromX, fromY);
	} else if (abs(toX - fromX) > abs(toY - fromY)) {
		if (fromX > toX) {
			tmp = fromX;
			fromX = toX;
			toX = tmp;

			tmp = fromY;
			fromY = toY;
			toY = tmp;
		}
		double grade = (toY - fromY) / (toX - fromX);
		for (i = fromX; i < toX + 1; i++) {
			setBmpPoint(this, c, i, fromY + (int) (i - fromX) * grade);
		}
	} else {
		if (fromY > toY) {
			tmp = fromX;
			fromX = toX;
			toX = tmp;

			tmp = fromY;
			fromY = toY;
			toY = tmp;
		}
		double grade = (toX - fromX) / (toY - fromY);
		for (i = fromY; i < toY + 1; i++) {
			setBmpPoint(this, c, fromX + (int) (i - fromY) * grade, i);
		}
	}
}

/**
 * Fills Circle on BMP on specific coordinate
 *
 * @param this Bmp* - Pointer to actual Struct BMP
 * @param c Color - Color which needs to be painted
 * @param x Integer - center of circle on x-achses
 * @param y Integer - center of circle on x-achses
 * @param radius Integer - radius of circle
 *
 */
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

/**
 * Creates a barchart out of an array
 *
 * @param values double[] - values you want to display
 * @param valueLength Integer - length of array which needs to be displayed
 *
 * @return new BMP with a barchart
 */
Bmp* barChart(double values[], int valueLength) {
	const int barWidth = 100;
	double newBarHeight;
	const int margin = 30;
	const int padding = 10;
	const int bmpWidth = valueLength * barWidth + (valueLength - 1) * padding
			+ 2 * margin;
	const int bmpHeight = 1000;
	Bmp* this = newBmp(bmpWidth, bmpHeight);
	background(this, WHITE);
	Color colors[] = { BLUE, BLACK, GREEN, RED, YELLOW };
	const int colorsSize = 5;
	int colorIndex = 0;
	double biggestValue = values[0];
	int i;

	for (i = 1; i < valueLength; i++) {
		if (values[i] > biggestValue) {
			biggestValue = values[i];
		}
	}
	for (i = 0; i < valueLength; i++) {
		newBarHeight = (bmpHeight - 2 * margin) * (values[i] / biggestValue);
		fillRect(this, colors[colorIndex++],
				(margin + (barWidth + padding) * i), margin, barWidth,
				newBarHeight);
		if (colorIndex == colorsSize) {
			colorIndex = 0;
		}
	}

	return this;
}

/**
 * Draws parts of the piechart to bitmap.
 *
 * @param this Bmp* - Pointer to actual Struct BMP
 * @param c Color - Color which needs to be painted
 * @param x Integer - center of circle on x-achses
 * @param y Integer - center of circle on x-achses
 * @param radius Integer - radius of circle
 * @param startPie double - degree where the pie starts
 * @param endPie double - degree where the pie ends
 *
 */
void drawPie(Bmp* this, Color c, int x, int y, int radius, double startPie,
		double endPie) {
	const int maxAlpha = 360 * (1 + radius / 10);
	int r, alpha, xbmp, ybmp;

	if (radius < 0) {
		radius = -radius;
	}
	/*b=pi*r²*(Alpha/360)*/
	for (r = radius; r > 0; r--) {
		for (alpha = startPie * (1 + radius / 10);
				alpha < endPie * (1 + radius / 10); alpha++) {
			xbmp = x + (r * sin(2 * M_PI * alpha / maxAlpha));
			ybmp = y + (r * cos(2 * M_PI * alpha / maxAlpha));
			setBmpPoint(this, c, xbmp, ybmp);
		}
	}
}

/**
 * Creates a piechart out of an array
 *
 * @param values double[] - values you want to display
 * @param valueLength Integer - length of array which needs to be displayed
 *
 * @return new BMP with a piechart
 */
Bmp* pieChart(double values[], int valueLength) {
	Color colors[] = { BLUE, BLACK, GREEN, RED, YELLOW };
	int colorIndex = 0;
	const int colorsSize = 5;
	double sum = 0.0;
	double startPie, endPie;
	int i;

	Bmp* this = newBmp(1000, 1000);
	background(this, WHITE);

	for (i = 0; i < valueLength; i++) {
		sum += values[i];
	}
	startPie = 0.0;
	endPie = 0.0;

	for (i = 0; i < valueLength; i++) {
		endPie = startPie + (values[i] / sum) * 360;
		drawPie(this, colors[colorIndex++], 500, 500, 400, startPie, endPie);
		startPie = endPie;
		if (colorIndex >= colorsSize) {
			colorIndex = 0;
		}
	}
	return this;
}
