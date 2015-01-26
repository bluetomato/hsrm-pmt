/**
 * @file BMP.h
 * @brief Header data for BMP.c
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

#ifndef BMP__H_
#define BMP__H_

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Struct Point
 *
 * Represents a Point with his x and y coordinates
 */
typedef struct {
	double xValue;	/**< value on x achses*/
	double yValue;	/**< value on y achses*/
} Point;

/**
 * @brief Struct Color
 *
 * Represents a Color using three values for RGB.
 * 0 as lowest, 255 as highest number.
 */
typedef struct {
	unsigned char red; 		/**< value between 0 an 255 for red colorrange*/
	unsigned char green; 	/**< value between 0 an 255 for green colorrange*/
	unsigned char blue; 	/**< value between 0 an 255 for blue colorrange*/
} Color;

const static Color BLACK = {0,0,0};
const static Color WHITE = {255,255,255};
const static Color RED   = {255,0,0};
const static Color GREEN = {0,255,0};
const static Color BLUE  = {0,0,255};
const static Color YELLOW= {255,255,0};
const static Color GRAY	 = {120,120,120};

/**
 * @brief Struct Bmp
 *
 * Represents a Bmp in witdh, height and
 * a pointer to a color
 */
typedef struct {
	int width; 			/**< Integer - value for the width of the bmp*/
	int height; 		/**< Integer - value for the height of the bmp*/
	Color* imagedata ; 	/**< Color* - pointer to an color*/
} Bmp;

Bmp* newBmp(int width,int height);
void deleteBmp(Bmp* this);
void writeBmpToFile(Bmp* this,char* fileName);
void setBmpPoint(Bmp* b,Color c,int x, int y);
void background(Bmp* this, Color c);
void drawLine(Bmp* this, Color c, int fromX, int fromY, int toX, int toY);
double min(double minX, double maxX, double f(double));
double max(double minX, double maxX, double f(double));
Point *drawCoordinateSystem(Bmp* this, const double size, double minX, double minY, double skalX, double skalY, int margin);
Bmp* drawGraph(double f(double), double minX, double maxX);
Bmp* drawGraphWithDiffs (double f(double), double minX, double maxX ,unsigned int numberOfDiffs);
double ab(double f(double), double x);
double abN(double f(double),double x,unsigned int n);

#endif

