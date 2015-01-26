#include<stdio.h>
#include"BMP.h"

/**
 * @file test.c
 * @brief Class for testing BMP.c
 *
 * I initialized an array with percentages of the EU elections 2014
 * It's been written as barchart to "bars.bmp" ans as piechart
 * to "piechart.bmp"
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
 * main function
 */
int main(){
	/*array with percentages of the EU election 2014*/
	double EUwahl14[] = {30.0, 27.3, 10.7, 3.4, 7.4, 5.3, 1.5, 0.4, 1.2, 0.7, 1.4, 0.6, 0.2, 0.3, 0.2, 0.1, 0.2, 0.1, 0.0, 0.0, 7.1, 0.2, 0.2, 0.1, 1.0, 0.6};

	Bmp* bars = barChart(EUwahl14, sizeof(EUwahl14)/sizeof(double));
	writeBmpToFile(bars, "bars.bmp");

	Bmp* cake = pieChart(EUwahl14, sizeof(EUwahl14)/sizeof(double));
	writeBmpToFile(cake, "cake.bmp");

	return 0;
}
