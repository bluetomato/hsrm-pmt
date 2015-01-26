#include "ArrayList.h"
#include "BinTree.h"
#include "Reimwoerterbuch.h"
#include "TestArrayList.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "MemoryTest.h"


int main(){

	Tree* tree = getSetOfWordsFromTextFile("text.txt");
	ArrayList list = treeAsList(tree);
	alForEach(list, printString);
	printf("\nREVERSE:\n");
	alSort(list,leReverseString);
	alForEach(list, printString);
	printf("\n\n\nReimlisten\n");
	ArrayList rhymeList= mkRhymeList(list);

	printf("lala");
	printListeString(rhymeList);
	alWriteAsXML(rhymeList, returnString, "Reimwörterbuch.xml");
	printf("feddisch");
	return 0;

  /*ArrayList is = alCreate();
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

  alForEach(xs,printString);
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


  return res;*/
}
