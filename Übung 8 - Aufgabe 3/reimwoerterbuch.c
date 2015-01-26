/**
 * Represents a rhymedictionary
 *
 * @file reimwoerterbuch.c
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

#include "BinTree.h"
#include "ArrayList.h"
#include "Reimwoerterbuch.h"
#include "TestArrayList.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * Initializes a new String and allocates space for data
 *
 * @param s const char* - char array
 *
 * @return pointer to new string struct with added data
 */
String* newString(const char *s) {
	String *this;

	/*allocate space*/
	this = malloc(sizeof(String));
	if (this == 0){
		return 0;
	}

	this->length = strlen(s);
	this->data = malloc(this->length);
	if (this->data == 0) {
		free(this);
		return 0;
	}
	strncpy(this->data, s, this->length);

	return this;
}

/**
 * Function for returning the length of a string
 *
 * @param s String
 *
 * @return int with size of given string
 */
int stringLength(String *s) {
	return s->length;
}

/**
 * Function for returning the character at a particuar index
 *
 * @param s String* - String where you want to find the index
 * @param index int - number for index you are looking for
 *
 * @return data at index or, if there's none: -1
 */
int stringCharAt(String *s, int index) {
	/*if index is bigger than length of s: return -1*/
	if (index < 0 || index >= s->length) {
		return -1;
	} else {
		return s->data[index];
	}
}

/**
 * Prints a String to console
 *
 * @param s String* - String which is going to be printed
 */
void printString(String *s) {
	printf("[%s]\n", s->data);
}

/**
 * Function for returning a String
 * Used at: test3.c to write an XML
 *
 * @param s String* - String that is going to be returned
 *
 * @return String input
 */
String returnString(String *s) {
	return *s;
}

/**
 * Function for printing an ArrayList<ArrayList<String>> to the console
 *
 * @param liste ArrayList - list that you want to be printet to the console
 *
 */
void printListeString(ArrayList liste) {
	int i, j;
	ArrayList* tmp;

	/*walk through every list index*/
	for (i = 0; i < liste.size; i++) {
		tmp = liste.data[i];
		printf("\n");
		for (j = 0; j < tmp->size; j++) {
			printString(tmp->data[j]);
		}
	}
}

/**
 * Converts a word to lowercase if there's a character that is uppercase
 *
 * @param word char* - word that is going to be convertet
 *
 * @return pointer to the converted (lowercase) word
 */
char* toLower(char* word) {
	int i;
	for (i = 0; word[i]; i++) {
		word[i] = tolower(word[i]);
	}
	return word;
}

/**
 * Reads a text file, converts every character to lowercase, and puts the words of this
 * text file into a binary tree
 *
 * @param filename char* - name of textfile
 *
 * @return binary tree with the words of the textfile
 */
Tree* getSetOfWordsFromTextFile(char* filename) {
	Tree* thisTree = newEmptyTree(klGlChar);
	FILE *file;
	char puffer[80];
	const char delimiterChars[12] = { ' ', ',', '.', ':', '\t', '!', '?', ';', '\n', '\r' };
	char *result = NULL;

	/*open file*/
	file = fopen(filename, "rb");
	if (file == NULL) {
		printf("Kann Datei nicht öffnen.");
		return thisTree;
	}

	/*read file and add to tree*/
	while (fgets(puffer, 80, file)) {
		result = strtok(puffer, delimiterChars);
		/*add to tree if result is not null*/
		while (result != NULL) {
			add(thisTree, newString(toLower(result)));
			/*next word*/
			result = strtok(NULL, delimiterChars);
		}
	}
	return thisTree;
}

/**
 * Function that converts a binary tree to an ArrayList
 *
 * @param tree Tree* - Tree that is going to be converted
 *
 * @return A list with all elements of tree
 */
ArrayList treeAsList(Tree* tree) {
	ArrayList thisList = alCreate();
	/*add every node to the list*/
	macheFuerAllePost(tree, &thisList, alAdd);
	return thisList;
}

/**
 * Checks if two words rhyme
 *
 * @param w1 String - first word
 * @param w2 String - second word
 *
 * @return TRUE if the words rhyme, else FALSE
 */
bool rhymeCheck(String* w1, String* w2) {
	/*reverse strings*/
	String *w12 = newString(strReverse(w1->data));
	String *w22 = newString(strReverse(w2->data));

	/*find the smallest string*/
	int i, smallest = stringLength(w12) < stringLength(w22) ? stringLength(w12) : stringLength(w22);

	/*walk through both strings til the smallest ends OR you find out that the words rhyme*/
	for (i = 0; i < smallest; i++) {
		if (stringCharAt(w12, i) == stringCharAt(w22, i)) {
			/*if a, i, o, u, ü, ä, ö are equal: words rhyme*/
			if (stringCharAt(w12, i) == 'a'
					|| stringCharAt(w12, i) == 'i'
					|| stringCharAt(w12, i) == 'o'
					|| stringCharAt(w12, i) == 'u'
					|| stringCharAt(w12, i) == -92 /*ä*/
					|| stringCharAt(w12, i) == -68 /*ü*/
					|| stringCharAt(w12, i) == -74 /*ö*/) {
				return true;
			}
		}
	}
	return false;
}

/**
 * Creates a list of lists with rhymes
 *
 * @param wordsRhymeSorted ArrayList - list of sorted words
 *
 * @return ArrayList with rhyming words
 */
ArrayList mkRhymeList(ArrayList wordsRhymeSorted) {
	ArrayList this = alCreate();
	int act, last;

	if (wordsRhymeSorted.size != 0) {
		ArrayList tmp = alCreate();
		alAdd(&tmp, alGet(wordsRhymeSorted, 0));

		/*walk through list as tuple (act and last)*/
		for (act = 1, last = 0; act < wordsRhymeSorted.size; act++, last++) {

			/*if two words rhyme: add to list*/
			if (rhymeCheck(alGet(wordsRhymeSorted, last), alGet(wordsRhymeSorted, act)) == true) {
				alAdd(&tmp, alGet(wordsRhymeSorted, act));
				/*not: add list to list of lists and create a new one */
			} else {
				alAdd(&this, alCopy(tmp));
				alDelete(tmp);
				tmp = alCreate();
				/*put the next word to the new list*/
				alAdd(&tmp, alGet(wordsRhymeSorted, act));
			}
		}
		/*add the last list to the list of lists*/
		alAdd(&this, alCopy(tmp));
	}
	return this;
}

