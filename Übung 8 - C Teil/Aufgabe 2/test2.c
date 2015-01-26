#include <stdio.h>
#include "BMP.h"
#include <math.h>

double polynomialDegreeZero(double x) {
	return -1;
}

double polynomialDegreeOne(double x) {
	return 3 * x + 5;
}

double polynomialDegreeTwo(double x) {
	return x * x - x - 2;
}

double polynomialDegreeThree(double x) {
	return 4 * x * x * x - 2 * x * x + 7 * x + 2;
}

double polynomialDegreeFour(double x) {
	return 6 * x * x * x * x - x * x * x + 4 * x * x + 2 * x + 2;
}

double polynomialDegreeSeven(double x) {
	return (x - 3) * (x - 2) * (x - 1) * (x) * (x + 1) * (x + 2) * (x + 3);
}

double sinus(double x) {
	return sin(x);
}

double cosinus(double x) {
	return cos(x);
}

int main() {
	Bmp* this0 = drawGraphWithDiffs(polynomialDegreeZero, -3.0, 3.0, 0);
	writeBmpToFile(this0, "polynomialDegreeZero.bmp");

	Bmp* this1 = drawGraphWithDiffs(polynomialDegreeOne, -3.0, 3.0, 0);
	writeBmpToFile(this1, "polynomialDegreeOne.bmp");

	Bmp* this2 = drawGraphWithDiffs(polynomialDegreeTwo, -3.0, 4.0, 1);
	writeBmpToFile(this2, "polynomialDegreeTwo.bmp");

	Bmp* this3 = drawGraphWithDiffs(polynomialDegreeThree, -5.0, 4.0, 2);
	writeBmpToFile(this3, "polynomialDegreeThree.bmp");

	Bmp* this4 = drawGraphWithDiffs(polynomialDegreeFour, -5.0, 4.0, 3);
	writeBmpToFile(this4, "polynomialDegreeFour.bmp");

	Bmp* this7 = drawGraphWithDiffs(polynomialDegreeSeven, -3.5, 3.5, 4);
	writeBmpToFile(this7, "polynomialDegreeSeven.bmp");

	Bmp* thisSin = drawGraphWithDiffs(sinus, -3.5, 3.5, 3);
	writeBmpToFile(thisSin, "sinus.bmp");

	Bmp* thisCos = drawGraphWithDiffs(cosinus, -3.5, 3.5, 2);
	writeBmpToFile(thisCos, "cosinus.bmp");

	return 0;
}
