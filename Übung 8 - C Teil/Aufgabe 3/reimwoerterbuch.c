#include "BinTree.h"
#include "ArrayList.h"
#include "Reimwoerterbuch.h"
#include "TestArrayList.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

String* newString(const char *s) {
	String *this;
	this = malloc(sizeof(String));
	if (this == 0)
		return 0;
	this->length = strlen(s);
	this->data = malloc(this->length);
	if (this->data == 0) {
		free(this);
		return 0;
	}
	strncpy(this->data, s, this->length);
	return this;
}

int stringLength(String *s) {
	return s->length;
}

int stringCharAt(String *s, int index) {
	if (index < 0 || index >= s->length) {
		return -1;
	} else {
		return s->data[index];
	}
}

void printString(String *s) {
	printf("[%s]\n", s->data);
}

String returnString(String *s) {
	return *s;
}

void printListeString(ArrayList liste) {
	int i, j;
	ArrayList* tmp;
	for (i = 0; i < liste.size; i++) {
		tmp = liste.data[i];
		printf("\n");
		for (j = 0; j < tmp->size; j++) {
			printString(tmp->data[j]);
		}
		/*alForEach((ArrayList)alGet(liste,i), printString);*/
	}
}

char* toLower(char* word) {
	int i;
	for (i = 0; word[i]; i++) {
		word[i] = tolower(word[i]);
	}
	return word;
}

/*Es soll eine Textdatei eingelesen werden. Großbuchstaben sollen in Kleinbuchstaben
 umgewandelt werden. Schließlich sollen die Wörter, die in dieser Textdatei stehen,
 in der als Binärbaum realisierten Menge gespeichert werden.
 * */
Tree* getSetOfWordsFromTextFile(char* filename) {
	Tree* thisTree = newEmptyTree(klGlChar);
	FILE *file;
	char puffer[80];
	const char delimiterChars[12] = { ' ', ',', '.', ':', '\t', '!', '?', ';',
			'\n', '\r' };
	char *result = NULL;

	file = fopen(filename, "rb");
	if (file == NULL) {
		printf("Kann Datei nicht öffnen.");
		return thisTree;
	}
	while (fgets(puffer, 80, file)) {
		result = strtok(puffer, delimiterChars);
		while (result != NULL) {
			add(thisTree, newString(toLower(result)));
			result = strtok(NULL, delimiterChars);
		}
	}
	return thisTree;
}

/*Schreiben Sie eine Funktion ArrayList treeAsList(Tree* tree), die die Elemente der Menge
 * entsprechend der Ordnungsrelation in der richtigen
 * Reihenfolge in eine Liste einfügen.*/
ArrayList treeAsList(Tree* tree) {
	ArrayList thisList = alCreate();
	macheFuerAllePost(tree, &thisList, alAdd);
	return thisList;
}

bool rhymeCheck(String* w1, String* w2) {
	String *w12 = newString(strReverse(w1->data));
	String *w22 = newString(strReverse(w2->data));
	int i, smallest =
			stringLength(w12) < stringLength(w22) ?
					stringLength(w12) : stringLength(w22);
	for (i = 0; i < smallest; i++) {
		if (stringCharAt(w12, i) == stringCharAt(w22, i)) {
			if (stringCharAt(w12, i) == 'a' || stringCharAt(w12, i) == 'i'
					|| stringCharAt(w12, i) == 'o'
					|| stringCharAt(w12, i) == 'u'
					|| stringCharAt(w12, i) == -92 /*ä*/
					|| stringCharAt(w12, i) == -68 /*ü*/
					|| stringCharAt(w12, i) == -74 /*ö*/) {
				/*printf("%s und %s reimen sich!\n", w1->data, w2->data);*/
				return true;
			}
		}
	}
	/*printf("%s und %s reimen sich nicht!\n", w1->data, w2->data);*/
	return false;
}
/*Es soll eine Liste von Listen sich reimenden Wörter erstellt werden. Die Eingabeliste
 ist dabei bereits die sortierte Liste aus der letzten Unteraufgabe. Diese muss also
 in Teillisten gesplittet werden.
 Zwei Wörter sollen dabei als reimend erkannt werden, wenn sie ein gemeinsames
 Ende haben, das mindestens einen der folgenden Buchstaben enthält: a, i, o ,u. (Der
 Buchstabe e ist ausgenommen, weil er im deutschen allein fast nur in unbetonten
 Endungen auftritt.)*/
ArrayList/*<ArrayList<char*>>*/mkRhymeList(ArrayList/*<char*>*/wordsRhymeSorted) {
	ArrayList this = alCreate();
	if (wordsRhymeSorted.size != 0) {
		ArrayList tmp = alCreate();
		alAdd(&tmp, alGet(wordsRhymeSorted, 0));
		int act, last;
		for (act = 1, last = 0; act < wordsRhymeSorted.size; act++, last++) {
			/*printf("act: %d, last: %d\n", act, last);*/
			/*printf("%d./%d (act: %d) vergleich: ", last, wordsRhymeSorted.size, act);*/
			if (rhymeCheck(alGet(wordsRhymeSorted, last),
					alGet(wordsRhymeSorted, act)) == true) {
				alAdd(&tmp, alGet(wordsRhymeSorted, act));
			} else {
				alAdd(&this, alCopy(tmp));
				/*printf("-act: %d, last: %d\n", act, last);*/
				alDelete(tmp);
				tmp = alCreate();
				alAdd(&tmp, alGet(wordsRhymeSorted, act));
			}
		}
		alAdd(&this, alCopy(tmp));
	}
	printf("ende\n");
	return this;
}

