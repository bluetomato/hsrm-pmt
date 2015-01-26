/**
 * Represents a rhymedictionary
 *
 * @file Reimwoerterbuch.h
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

#ifndef REIMWOERTERBUCH__H
#define REIMWOERTERBUCH__H

#include <stdbool.h>
#include "BinTree.h"

/**
 * Stuct for a String
 */
typedef struct {
	char *data; /**< data as char**/
	int length; /**< length of data*/
} String;

String* newString(const char *s);
int stringLength(String *s);
int stringCharAt(String *s, int index);
void printString(String *s);
String returnString(String *s);
void printListeString(ArrayList liste);

Tree* getSetOfWordsFromTextFile(char* filename);
ArrayList treeAsList(Tree* tree);
ArrayList mkRhymeList(ArrayList wordsRhymeSorted);

#endif
