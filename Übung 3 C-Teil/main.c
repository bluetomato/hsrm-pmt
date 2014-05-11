#include <stdio.h>
#include "List.c"

int main()
{
  int wert0 = 1;
  int wert1 = 2;
  int wert2 = 3;
  int wert3 = 4;
  int wert4 = 5;

  List* l1 = newConsList(&wert0, newConsList(&wert1,newEmptyList()));

  printf("\nListe mit 2 Elementen\n");
  void gebeAus(void* aus)
  {
    int* par = (int*) aus;
    printf("Werte: %d\n",*par);
  }

  macheFuerAlle(l1, gebeAus);

  printf("\nListe mit 3 Elementen\n");
  l1 = add(l1, &wert2);

  macheFuerAlle(l1, gebeAus);

  printf("\nCopyList\n");
  List* l2 = copyList(l1);
  deleteList(l1);
  macheFuerAlle(l2,gebeAus);

  printf("\nGeloeschte Liste\n");
  macheFuerAlle(l1,gebeAus);

  List* l3 = newConsList(&wert3, newConsList(&wert4,newEmptyList()));

  printf("\nl2\n");
  macheFuerAlle(l2,gebeAus);

  printf("\nl3\n");
  macheFuerAlle(l3,gebeAus);

  List* l4 = append(l2,l3);
  List* l9 = copyList(l4);
  List* l7 = append(l9,l4);

  printf("******************************************************");
  printf("\n append l2 und l3\n");
  macheFuerAlle(l4,gebeAus);

  printf("******************************************************");
  printf("\ndrop 1 Element von li4\n");
  l4 = drop(l4,1);
  macheFuerAlle(l4,gebeAus);

  printf("******************************************************");
  printf("\nnimm die ersten 2 Elemente von l4\n");
  List* li6 = take(l4,2);
  macheFuerAlle(li6,gebeAus);

  printf("******************************************************");
  printf("\nErzeuge sublist von l7 ab index 3 Laenge 3\n");
  printf("l7\n");
  macheFuerAlle(l7,gebeAus);
  List* l8 = sublist(l7,3,3);
  printf("sublist\n");
  macheFuerAlle(l8,gebeAus);

  printf("******************************************************");
  printf("\nGet von li8 element 1\n");
  int* aus = get(l8,1);
  printf("%d\n",*aus);

  return 0;
}
