#include "ArrayList.h"
#include <stdio.h>
#include <stdlib.h>
//#include "MemoryTest.h"

ArrayList alCreate() {
	//ArrayList this = malloc(sizeof(ArrayList));
	ArrayList this;
	this.capacity = 5;
	this.size = 0;
	this.data = malloc(this.capacity * 8);
	return this;
}

ArrayList* alCreateP() {
	ArrayList* this = malloc(sizeof(ArrayList));
	//ArrayList this;
	this->capacity = 5;
	this->size = 0;
	this->data = malloc(this->capacity * 8);
	return this;
}

void alAdd(ArrayList* this, Object object) {
	if (this->size < this->capacity) {
		this->data[this->size] = object;
		this->size++;
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

void alForEach(ArrayList this, Consumer cs) {
	int i;
	for (i = 0; i < this.size; i++) {
		cs(*(this.data + i));
	}
}

ArrayList* alCopy(ArrayList that){
	ArrayList* this = alCreateP();
	int i;
	for(i = 0; i < that.size; i++){
		alAdd(this, that.data[i]);
	}
	return this;
}

void alDelete(ArrayList this) {
	free(this.data);
	this.capacity = 0;
	this.size = 0;
}

Object alGet(ArrayList this, unsigned int index) {
	if (index >= this.size) {
		return NULL;
	}
	return (*(this.data + index));
}

void alSort(ArrayList this, RelationLe rel) {
	int i, j;
	Object temp;
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
/*int i, j;
	ArrayList* tmp;
	for (i = 0; i < liste.size; i++) {
		tmp = liste.data[i];
		printf("\n");
		for (j = 0; j < tmp->size; j++) {
			printString(tmp->data[j]);
		}
	}
	*/
int alWriteAsXML(ArrayList this, ToString ts, char* fileName) {
	FILE *fp;
	ArrayList* tmp;
	fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("nicht geöffnet.");
		return 1;
	}
	printf("da");
	fprintf(fp,
			"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
	fprintf(fp, "<Reimwörterbuch>\n");
	int i, j;
	for (i = 0; i < this.size; i++) {
		tmp = this.data[i];
		fprintf(fp, "<Reim>");
		for(j = 0; j < tmp->size; j++){
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
