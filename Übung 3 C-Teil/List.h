#include <stdbool.h>

struct Li{
	void* head;
	struct Li* tail;
};

typedef struct Li List;

bool isEmpty(List* this);
List* newEmptyList();
List* newConsList(void* hd, List* tl);

void deleteList(List* this);

unsigned int length(List* this);
List* add(List* this, void* el);

List* copyList(List* this);
List* append(List* this, List* that);
List* drop(List* this, int i);
List* take(List* this, int i);
List* sublist(List* this, int start, int length);
void* get(List* this, int index);

void macheFuerAlle(List* this, void consumer(void*) );

