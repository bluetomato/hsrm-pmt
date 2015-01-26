#ifndef REIMWOERTERBUCH__H
#define REIMWOERTERBUCH__H

#include <stdbool.h>
#include "BinTree.h"

typedef struct {
	char *data;
	int length;
} String;

String* newString(const char *s);
int stringLength(String *s);
int stringCharAt(String *s, int index);
void printString(String *s);
String returnString(String *s);
void printListeString(ArrayList liste);

Tree* getSetOfWordsFromTextFile(char* filename);
ArrayList treeAsList(Tree* tree);
ArrayList/*<ArrayList<char*>>*/mkRhymeList(ArrayList/*<char*>*/wordsRhymeSorted);

#endif
