#include "ArrayList.h"
#include "Reimwoerterbuch.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void printInt(Object o) {
	printf(" %d", *(int*) o);
}

bool leInt(Object o1, Object o2) {
	return *(int*) o1 <= *(int*) o2;
}

char* toStringInt(Object o) {
	char* result = malloc(sizeof(char) * 15);
	sprintf(result, "%d", *(int*) o);
	return result;
}

char* strReverse(char* str) {
	unsigned int length = strlen(str);
	char* result = malloc((length + 1) * sizeof(char));
	result[length] = '\0';
	int i;
	for (i = 0; i < length; i++) {
		result[length - 1 - i] = str[i];
	}
	return result;
}

void printReverseString(Object o) {
	char* r = strReverse(*(char**) o);
	printf(" %s", r);
	free(r);
}

void printStrings(Object o) {
	printf(" %s", *(char**) o);
}

bool leString(Object o1, Object o2) {
	return strcmp(*(char**) o1, *(char**) o2) <= 0 ? true : false;
}

char* toStringString(Object o) {
	char* result = malloc((strlen(*(char**) o) + 1) * sizeof(char));
	strcpy(result, *(char**) o);
	return result;
}

bool leReverseString(Object o1, Object o2) {
	char* r1 = strReverse(*(char**) o1);
	char* r2 = strReverse(*(char**) o2);
	bool result = strcmp(r1, r2) <= 0 ? true : false;
	free(r1);
	free(r2);
	return result;
}
/*
 int main(){
 ArrayList is = alCreate();
 int numbers [] = {1456,24,7,-798,0,67,2,2,2,42,43,-42,19,17,16,5,576,-678,-78,19,21};
 int i;
 for (i=0;i<21;i++) alAdd(&is,numbers+i);

 alForEach(is,printInt);
 printf("\n");
 alSort(is,leInt);
 alForEach(is,printInt);
 printf("\n");

 int res = alWriteAsXML(is,toStringInt,"liste.xml");

 alDelete(is);


 ArrayList xs = alCreate();
 char* strings [] = {"lieber","haus","maus","mutter","schieber","kutter","ratte","butter","fieber","kaputter"};
 for (i=0;i<10;i++) alAdd(&xs,strings+i);

 alForEach(xs,printStrings);
 printf("\n");
 alForEach(xs,printReverseString);
 printf("\n");
 alSort(xs,leString);
 alForEach(xs,printString);
 printf("\n");


 alSort(xs,leReverseString);
 alForEach(xs,printString);
 printf("\n");

 res += alWriteAsXML(xs,toStringString,"liste2.xml");

 alDelete(xs);

 printf("alloc %d free %d diff %d\n",speicherAlloc,speicherFree,speicherAlloc-speicherFree);


 return res;
 }*/
