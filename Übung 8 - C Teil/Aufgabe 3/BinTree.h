#ifndef BIN_TREE__H
#define BIN_TREE__H

#include <stdbool.h>
#include "ArrayList.h"

typedef bool le (void*,void*);

struct TR{
  /* im prinzip ist void* so etwas wie irgendwas also: Object */
  void* head;
  /* linkes Kind (darf NULL sein) */
  struct TR* left;
  /* linkes Kind (darf NULL sein) */
  struct TR* right;

  /* die Ordnungsrelation. sollte im jeden Knoten derselbe Zeiger sein */
  le* kleinerGleich;
};

typedef struct TR Tree;
typedef unsigned int nat;

bool isEmpty(Tree* this);

/* mache eine leere Menge */
Tree* newEmptyTree(le kleinerGleich);

/* mache eine einelementige Menge */
Tree* newLeafTree(le kleinerGleich, void* elem);

/* lösche alle Baumknoten, aber nicht die Elemente */
void deleteTree(Tree* this);

/*unsigned int*/ nat length(Tree* this);


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
void add(Tree* this, void* el);

/* kopiere den Baum, aber nicht die Elemente */
Tree* copyTree(Tree* this);

/* enthält der Baum ein bestimmtes Element. Hierzu wird die Ordnungsrelation des Baumes genommen.
x==y bedeutet: kleinerGleich(x,y) && kleinerGleich(y,x).
*/

bool contains(Tree* this,void* elem);

/* mache etwas für alle Elemente, die vom Baum referenziert werden. */
void macheFuerAlle(Tree* this, void consumer(void*) );

bool klGlChar(void* w1,void* w2);
/* Beispiel für int Zeiger:*/

/*bool klGl(void* xp,void* yp){
	return *((int*)xp) <= *((int*)yp);
}

void printInt(void* p){
  printf("%d ",*((int*)p));
}

int main(){
  int xs [] = {34,5,23,6,5345,-34,43,-431,1,43,5445,-265};
  Tree*  t = newEmptyTree(klGl);
  int i;
  for (i=0; i < 12; i++) add(t,xs+i);

  macheFuerAlle(t,printInt);

  deleteTree(t);

  return 0;
}

*/
#endif
