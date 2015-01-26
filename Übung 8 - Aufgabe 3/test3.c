/**
 * Test method
 *
 * @file test3.c
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
#include "BinTree.h"
#include "Reimwoerterbuch.h"
#include "TestArrayList.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * main
 */
int main() {
	printf("1\n");
	Tree* tree = getSetOfWordsFromTextFile("text.txt");
	printf("1\n");
	ArrayList list = treeAsList(tree);
	printf("1\n");
	alSort(list, leReverseString);
	printf("1\n");
	ArrayList rhymeList = mkRhymeList(list);
	printf("1\n");
	alWriteAsXML(rhymeList, returnString, "Reimwoerterbuch.xml");
	printf("1\n");
	return 0;
}
