#include <stdio.h>
#include "BMP.h"
#include <math.h>

/**
 * @file test2.c
 * @brief Class for testing BMP.c
 *
 * Includes methods for testing different functions and
 * put them into a bitmap file.
 *
 * @author Stephanie Scholl
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
 * @brief Polynomial Test Function Grade Zero
 *
 * @param x double - value of x achses
 *
 * @return -1 double - because it's a line
 */
double polynomialDegreeZero(double x) {
	return -1;
}

/**
 * @brief Polynomial Test Function Grade One
 *
 * @param x double - value of x achses
 *
 * @return 3*x+5 double - parable
 */
double polynomialDegreeOne(double x) {
	return 3 * x + 5;
}

/**
 * @brief Polynomial Test Function Grade Two
 *
 * @param x double - value of x achses
 *
 * @return x*x-x-2 double
 */
double polynomialDegreeTwo(double x) {
	return x * x - x - 2;
}

/**
 * @brief Polynomial Test Function Grade Tree
 *
 * @param x double - value of x achses
 *
 * @return 4*x*x*x-2*x*x+7*x+2 double
 */
double polynomialDegreeThree(double x) {
	return 4 * x * x * x - 2 * x * x + 7 * x + 2;
}

/**
 * @brief Polynomial Test Function Grade Four
 *
 * @param x double - value of x achses
 *
 * @return 6*x*x*x*x-x*x*x+4*x*x+2*x+2 double
 */
double polynomialDegreeFour(double x) {
	return 6 * x * x * x * x - x * x * x + 4 * x * x + 2 * x + 2;
}

/**
 * @brief Polynomial Test Function Grade Seven
 *
 * @param x double - value of x achses
 *
 * @return (x-3)*(x-2)*(x-1)*(x)*(x+1)*(x+2)*(x+3) double
 */
double polynomialDegreeSeven(double x) {
	return (x - 3) * (x - 2) * (x - 1) * (x) * (x + 1) * (x + 2) * (x + 3);
}

/**
 * @brief Test Sinus Function
 *
 * @param x double - value of x achses
 *
 * @return sin(x) double
 */
double sinus(double x) {
	return sin(x);
}

/**
 * @brief Test cosinus function
 *
 * @param x double - value of x achses
 *
 * @return cos(x) double
 */
double cosinus(double x) {
	return cos(x);
}

/**
 * @brief main function
 *
 * builts different bitmaps of the test methods and
 * writes them as bitmaps
 */
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
