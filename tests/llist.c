#include <stdio.h>
#include "../llist/llist.h"

int main(void)
{
	struct llist_node *p;
	size_t i = 0;
	struct llist l;

	if (llist_init(&l, sizeof(int)) == ALLOC_FAIL) {
		printf("ERROR! Out of memory.\n");
		exit(1);
	}

	llist_pushback(&l, &(int){3});
	llist_pushback(&l, &(int){8});
	llist_pushfront(&l, &(int){1});
	llist_pushfront(&l, &(int){9});
	llist_addnode(&l, llist_getnode(&l, 2), &(int){2});
	llist_popfront(&l);
	llist_pushfront(&l, &(int){7});
	llist_delnode(&l, llist_getnode(&l, 0));
	llist_popback(&l);

	p = l.head;
	TRAVERSE_LLIST(p, printf("Value at index %lu: %d\n", i, *(int *) p->data); i++;);

	llist_deinit(&l);
}
