/**
 * File with String functions
 *
 * @file TestArrayList.c
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
 */

#include "ArrayList.h"
#include "Reimwoerterbuch.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Prints Object as Integer to console
 *
 * @param o Object - value that is going to be printed
 */
void printInt(Object o) {
	printf(" %d", *(int*) o);
}

/**
 * smaller/equals function for Integers
 *
 * @param o1 Object - object one
 * @param o2 Object - object twi
 *
 * @return TRUE if o1 is smaller/equals o2, else FALSE
 */
bool leInt(Object o1, Object o2) {
	return *(int*) o1 <= *(int*) o2;
}

/**
 * Converts object to char* and returns it
 *
 * @param o Object - object that is beeing converted
 *
 * @return converted string as char*
 */
char* toStringInt(Object o) {
	char* result = malloc(sizeof(char) * 15);
	sprintf(result, "%d", *(int*) o);
	return result;
}

/**
 * Reverses a String
 *
 * @param str char* - String that must be reversed
 *
 * @return reversed char*
 */
char* strReverse(char* str) {
	unsigned int length = strlen(str);
	char* result = malloc((length + 1) * sizeof(char));
	/*add end of string*/
	result[length] = '\0';
	int i;
	/*put data on index of str to result string*/
	for (i = 0; i < length; i++) {
		result[length - 1 - i] = str[i];
	}
	return result;
}

/**
 * Prints String reversed
 *
 * @param o Object - normal word that's beeing reversed and printed
 *
 */
void printReverseString(Object o) {
	char* r = strReverse(*(char**) o);
	printf(" %s", r);
	free(r);
}

/**
 * Print String function of Prof. Panitz, not used.
 *
 * @param o Object - object that's beeing printed
 */
void printStrings(Object o) {
	printf(" %s", *(char**) o);
}

/**
 * Checks if a string is smaller/equals as an other one
 *
 * @param o1 Object - first String
 * @param o2 Object - second String
 *
 * @return TRUE if o1 is smaller/equals o2, else FALSE
 */
bool leString(Object o1, Object o2) {
	return strcmp(*(char**) o1, *(char**) o2) <= 0 ? true : false;
}

/**
 * Function that converts an object to an char*
 *
 * @param o Object - object that's beeing converted
 *
 * @return new string
 */
char* toStringString(Object o) {
	char* result = malloc((strlen(*(char**) o) + 1) * sizeof(char));
	/*copy object to string*/
	strcpy(result, *(char**) o);
	return result;
}

/**
 * Function that reverses the input objects and checks if they're qual
 *
 * @param o1 Object - input one
 * @param o2 Object - inpur two
 *
 * @return TRUE if o1 and o2 are equal, else FALSE
 */
bool leReverseString(Object o1, Object o2) {
	char* r1 = strReverse(*(char**) o1);
	char* r2 = strReverse(*(char**) o2);
	bool result = strcmp(r1, r2) <= 0 ? true : false;
	free(r1);
	free(r2);
	return result;
}
