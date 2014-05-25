#include <stdio.h>
#include <stdlib.h>
#include "BinTree.h"

bool isEmpty(Tree* this){
	return this->head == NULL;
}

/* mache eine leere Menge */
Tree* newEmptyTree(le kleinerGleich){
	return newLeafTree(kleinerGleich, NULL);
}

/* mache eine einelementige Menge */
Tree* newLeafTree(le kleinerGleich, void* elem){
	Tree* newTree = malloc(sizeof(Tree));
	newTree->head = elem;
	newTree->left = NULL;
	newTree->right = NULL;
	newTree->kleinerGleich = kleinerGleich;
	return newTree;
}

/* lösche alle Baumknoten, aber nicht die Elemente */
void deleteTree(Tree* this){
	if(this != NULL){
	  deleteTree(this->left);
	  deleteTree(this->right);
	  free(this);
	}
}

/*unsigned int*/ nat length(Tree* this){
	if(this->head == NULL){
		return 0;
	}else if(this->left == NULL && this->right == NULL){
		return 1;
	}else{
		return length(this->left) + length(this->right) + 1;
	}
}


/* Algorithmus für das Hinzufügen eines Elements:

   1. Schaue ob this leerer Baum: dann this->head = el
   2. sonst
       vergleiche: this->kleinerGleich(el,head)
         a) Ja! dann checke:  this->kleinerGleich(head,el)
             i) Ja! dann return (ohne weitere aktion)
	     ii) sonst add(this->left,el) (wenn this-> left nicht NULL)
                 (oder this->left = newLeafTree(this->kleinerGleich,el)
        b) analog wie oben nur rechte Seite rechts
*/
void add(Tree* this, void* el){
	if(isEmpty(this)){
	  this->head = el;

	}else{
	  if(this->kleinerGleich(el, this->head)){
	    if(this->kleinerGleich(this->head, el)){
	      return;
	    }else{
	      if(this->left != NULL){
		add(this->left, el);
	      }else{
		this->left = newLeafTree(this->kleinerGleich,el);
	      }
	    }
	  }else{
	    if(this->kleinerGleich(this->head, el)){
	      if(this->right != NULL){
		add(this->right, el);
	      }else{
		this->right = newLeafTree(this->kleinerGleich,el);
	      }
	    }else{
	      return;
	    }

	  }
	}
}

/* kopiere den Baum, aber nicht die Elemente */
Tree* copyTree(Tree* this){
  if(this == NULL){
    return NULL;
  }
  Tree* l = copyTree(this->left);
  Tree* r = copyTree(this->right);
  Tree* n = newLeafTree(this->kleinerGleich,this->head);
  n->left = l;
  n->right = r;
  return n;
}

/* enthält der Baum ein bestimmtes Element. Hierzu wird die Ordnungsrelation des Baumes genommen.
x==y bedeutet: kleinerGleich(x,y) && kleinerGleich(y,x).
*/

bool contains(Tree* this,void* elem){

  if(this != NULL){
    if((this->kleinerGleich(this->head, elem)) && (this->kleinerGleich(elem, this->head))){
      return true;
    }

    return contains(this->right, elem) || contains(this->left, elem);
  }
  return false;
}

/* mache etwas für alle Elemente, die vom Baum referenziert werden. */
void macheFuerAlle(Tree* this, void consumer(void*) ){
  if(this != NULL){
    macheFuerAlle(this->left, consumer);
    macheFuerAlle(this->right, consumer);
    consumer(this->head);
  }
}

void macheFuerAllePre(Tree* this, void consumer(void*) )
{
  if(this != NULL){
    consumer(this->head);
    macheFuerAllePre(this->left, consumer);
    macheFuerAllePre(this->right, consumer);
  }
}


/* Beispiel für int Zeiger: */

bool klGlInt(void* xp,void* yp){
  return *((int*)xp) <= *((int*)yp);
}

void printInt(void* p){
  printf("%d \n",*((int*)p));
}

int main(){
  int xs [] = {34,5,23,6,5345,-34,43,-431,1,43,5445,-265};
  int test[] = {0, 1, -34, -432};
  Tree*  t = newEmptyTree(klGlInt);
  int i;
  for (i=0; i < 12; i++) add(t,xs+i);

  macheFuerAlle(t,printInt);

  printf("\n\n");
  printf("Contains 0: %d \n", contains(t, &test[0]));
  printf("Contains 1: %d \n", contains(t, &test[1]));
  printf("Contains -34: %d \n", contains(t, &test[2]));
  printf("Contains -432: %d \n", contains(t, &test[3]));

  /*deleteTree(t);*/


  return 0;
}
