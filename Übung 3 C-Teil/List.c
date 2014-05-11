#include "List.h"
#include <stdio.h>
#include <stdlib.h>

bool isEmpty(List* this){
	return this->head == NULL && this->tail == NULL;
}

List* newEmptyList(){
	List* this = malloc(sizeof(List));
	this->head = NULL;
	this->tail = NULL;
	return this;
}

List* newConsList(void* head, List* tail){
	List* this = malloc(sizeof(List));
	this->head = head;
	this->tail = tail;
	return this;
}

void deleteList(List* this){
	if (!isEmpty(this)) deleteList(this->tail);
	free(this);
}

/* Gibt die Länge der Liste zurück */
unsigned int length(List* this){
	int tmp = 0;
	if(isEmpty(this)){
		return 0;
	}

	tmp = length(this->tail);
	return tmp+1;
}

List* add(List* this, void* el){
	int i;
	List* tmp = this->tail;
	for(i = 1; i < length(this); i++)
	{
		tmp = tmp->tail;
	}

	tmp->head = el;
	tmp->tail = newEmptyList();
	return this;
}


List* copyList(List* this){
	if(isEmpty(this))
	{
		return newEmptyList();
	}

	List* tmp = newConsList(this->head, newEmptyList());
	List* acttmp = this->tail;

	int i = 0;
	for(i = 1; i< length(this); i++)
	{
		tmp = add(tmp,acttmp->head);
		acttmp = acttmp->tail;
	}

	return tmp;
}

List* append(List* this, List* that){
	List* tmp = this->tail;

	int i;
	for(i = 1; i < length(this); i++)
	{
		tmp = tmp->tail;
	}
	tmp->head = that->head;
	tmp->tail = that->tail;
	return this;
}

List* drop(List* this, int i){
	List* tmp;
	List* tmp1;
	int j;

	if(i >= length(this))
	{
		tmp = this;

	    int a;
	    while(a < length(this))
	    {
	    	tmp1 = tmp->tail;
	    	free(tmp);
	    	tmp = tmp1;
	    	a++;
	    }

	    return newEmptyList();
	}

	tmp = this->tail;
	free(this);

	for(j = 1; j < i; j++)
	{
		tmp1 = tmp->tail;
	    free(tmp);
	    tmp = tmp1;
	}

	return tmp;
}

List* take(List* this, int i){
	return sublist(this, 0, i);
}

List* sublist(List* this, int start, int length){
	List* newList = copyList(this);
	List* tmp = newList;
	int i;

	if(start > length(this))
	{
		return newEmptyList();
	}
	if(start + length > length(this))
	{
		length = length(this) - start;
	}

	for(i = 0; i < start; i++)
	{
		tmp = tmp->tail;
	}

	List* ret = newConsList(tmp->head, newEmptyList());
	tmp = tmp->tail;

	for(i = start + 1; i < (start + length); i++)
	{
		ret = add(ret, tmp->head);
		tmp = tmp->tail;
	}
	return ret;
}

void* get(List* this, int index){
	int i;

	if(index > length(this)-1)
	{
		return newEmptyList();
	}

	for(i = 0; i < index; i++)
	{
		this = this->tail;
	}
	return this->head;
}


void macheFuerAlle(List* this, void consumer(void*) ){
	int l = length(this);
	int i;
	for(i = 0; i< l; i++)
	{
		consumer(this->head);
	    this = this->tail;
	}
}

