#ifndef ARRAY_LIST__H
#define ARRAY_LIST__H

#include <stdbool.h>

/** We want to implement a generic list for different types. This is done
    via a void*, which is regarded as an general object. **/
typedef void* Object;

/** The struct ArrayList contains a maximal capacity, the actual number
    if elements and an array as the internal data store.**/
typedef struct{
  /** The maximum capacity, i.e. the size of the data store.**/
  unsigned int capacity;
  /** The current number of elements in the list.**/
  unsigned int size;
  /** The data store with the list elements.**/
  Object* data;
} ArrayList;

/** This function will be used for comparing objects in a sort function. **/
typedef bool RelationLe(Object,Object);

/** This function will generate a string representation of the given object.
    A new string will be allocated and needs to get a call to free. **/
typedef char* ToString(Object);

/** This function will do something with an object.
    Usually it has some side effect, like io operations.
**/
typedef void Consumer(Object);

/** This function will generate a new ArrayList. It has some initial capacity.
    The internal data store gets allocated. The initial size is 0.**/
ArrayList alCreate();

/** This function will free the allocated data store of the given ArrayList.**/
void alDelete(ArrayList this);

/** This function add a further element to the end of the list.
    If the capacity is not sufficient, a new internal data store is
    allocated and the elements are copied to the new store.
    Then the old data store needs a call to free, which is done within this
    function. **/
void alAdd(ArrayList* this, void* object);

/** Returns the element at a given index. If the given index is greater or
    equal to the size, then NULL will be returned. **/
Object alGet(ArrayList this,unsigned int index);

/** Sorts the list in place with a given relation. Bubble sort is used a
    sotring algorithm. **/
void alSort(ArrayList this,RelationLe rel);

/** Performs the Consumer function to each element. **/
void alForEach(ArrayList this,Consumer cs);

/** Writes an XML file, which represents the list. The elements are converted
    into strings by the given ToString function. The temporary created
    string results of the ToString function will get a call to free. **/
int alWriteAsXML(ArrayList this,ToString ts,char* fileName);

ArrayList/*<ArrayList<char*>>*/mkRhymeList(ArrayList/*<char*>*/ wordsRhymeSorted);

#endif
