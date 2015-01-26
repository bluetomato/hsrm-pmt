#include "ArrayList.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * Represents an ArrayList
 *
 * @file ArrayList.c
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

/**
 * Creates a new empty ArrayList
 * Capacity is 5, Size is 0, Data is allocated
 * @return empty ArrayList
 */
ArrayList alCreate() {
	ArrayList this;
	this.capacity = 5;
	this.size = 0;
	this.data = malloc(this.capacity * 8);
	return this;
}

/**
 * Creates a Pointer of a new empty ArrayList
 * Capacity is 5, Size is 0
 * @return pointer to new empty ArrayList
 */
ArrayList* alCreateP() {
	ArrayList* this = malloc(sizeof(ArrayList));
	this->capacity = 5;
	this->size = 0;
	this->data = malloc(this->capacity * 8);
	return this;
}

/**
 * Function for adding an Object to a given ArrayList
 *
 * @param this ArrayList* List where the object is added
 * @param object void* Object to add to the List
 */
void alAdd(ArrayList* this, Object object) {
	/*if there's enough space: put*/
	if (this->size < this->capacity) {
		this->data[this->size] = object;
		this->size++;
		/*else: allocate new space*/
	} else {
		Object* temp = malloc((this->capacity + 5) * 8);
		int i;
		for (i = 0; i < this->size; i++) {
			temp[i] = this->data[i];
		}
		free(this->data);
		this->data = temp;
		this->data[this->size] = object;
		this->size++;
		this->capacity = this->capacity + 5;
	}
}

/**
 * Function for walking through a whole List and
 * apply a consumer to every Element
 *
 * @param this ArrayList - List you want to go through
 * @param cs Consumer - consumer you want to apply
 */
void alForEach(ArrayList this, Consumer cs) {
	int i;
	for (i = 0; i < this.size; i++) {
		cs(*(this.data + i));
	}
}

/**
 * Function for copying a ArrayList
 *
 * @param that ArrayList - List which is copied
 */
ArrayList* alCopy(ArrayList that) {
	ArrayList* this = alCreateP();
	int i;
	for (i = 0; i < that.size; i++) {
		alAdd(this, that.data[i]);
	}
	return this;
}

/**
 * Function for deleting an existing ArrayList
 *
 * @param this ArrayList - List which is going to be deleted
 */
void alDelete(ArrayList this) {
	free(this.data);
	this.capacity = 0;
	this.size = 0;
}

/**
 * Function for getting the data of an ArrayList on
 * a specific index
 *
 * @param this ArrayList - List where the index is beeing looked up
 * @param index unsigned int - Index of the List
 *
 * @return Object at the index' position of the List, if there's no such
 * index return NULL
 */
Object alGet(ArrayList this, unsigned int index) {
	if (index >= this.size) {
		return NULL;
	}
	return (*(this.data + index));
}

/**
 * Function for sorting an ArrayList with an relation
 *
 * @param this ArrayList - List which is beeing sorted
 * @param rel RelationLe - Relation which is beeing applied
 */
void alSort(ArrayList this, RelationLe rel) {
	int i, j;
	Object temp;
	/*for every object in this*/
	for (i = this.size; i > 1; i--) {
		for (j = 0; j < i - 1; j++) {
			if (rel(*(this.data + j), *(this.data + j + 1))) {
				temp = *(this.data + j);
				*(this.data + j) = *(this.data + j + 1);
				*(this.data + j + 1) = temp;
			}
		}
	}
}

/**
 * Function for writing an ArrayList to a XML file
 *
 * @param this ArrayList - List which is going to be written
 * @param ts ToString - toString-Method
 * @param fileName char* - filename for the new XML file
 *
 * return 0 if everything went well, else 1
 */
int alWriteAsXML(ArrayList this, ToString ts, char* fileName) {
	FILE *fp;
	ArrayList* tmp;
	fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("nicht geöffnet.");
		return 1;
	}
	fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
	fprintf(fp, "<Reimwörterbuch>\n");
	int i, j;
	for (i = 0; i < this.size; i++) {
		tmp = this.data[i];
		fprintf(fp, "<Reim>");
		for (j = 0; j < tmp->size; j++) {
			fprintf(fp, "<Wort>");
			fprintf(fp, ts(*(tmp->data + j)));
			fprintf(fp, "</Wort>\n");
		}
		fprintf(fp, "</Reim>");
	}
	fprintf(fp, "</Reimwörterbuch>\n");
	fclose(fp);
	return 0;
}
