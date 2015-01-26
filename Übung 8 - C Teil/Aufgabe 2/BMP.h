#ifndef BMP__H_
#define BMP__H_

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	double xValue;
	double yValue;
} Point;

typedef struct {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} Color;

const static Color BLACK = {0,0,0};
const static Color WHITE = {255,255,255};
const static Color RED   = {255,0,0};
const static Color GREEN = {0,255,0};
const static Color BLUE  = {0,0,255};
const static Color YELLOW= {255,255,0};
const static Color GRAY	 = {120,120,120};

typedef struct {
	int width;
	int height;
	Color* imagedata ;
} Bmp;

Bmp* newBmp(int width,int height);
void deleteBmp(Bmp* this);
void writeBmpToFile(Bmp* this,char* fileName);
void setBmpPoint(Bmp* b,Color c,int x, int y);
void background(Bmp* this, Color c);
void drawLine(Bmp* this, Color c, int fromX, int fromY, int toX, int toY);
void fillCircle(Bmp* this, Color c, int x, int y, int radius);
double min(double minX, double maxX, double (f)(double));
double max(double minX, double maxX, double (f)(double));
Point *drawCoordinateSystem(Bmp* this, const double size, double minX, double minY, double skalX, double skalY, int margin);
Bmp* drawGraph(double (f)(double), double minX, double maxX);
Bmp* drawGraphWithDiffs (double (f)(double), double minX, double maxX ,unsigned int numberOfDiffs);
double ab(double (f)(double), double x);
double abN(double (f)(double),double x,unsigned int n);

#endif

