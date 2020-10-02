#include <stdio.h>
#include "../llist/llist.h"

int main(void)
{
	struct llist_node *p;
	size_t i = 0;

	struct llist v;
	if (llist_init(&v, sizeof(int)) == ALLOC_FAIL) {
		printf("ERROR! Out of memory.\n");
		exit(1);
	}
	llist_pushback(&v, &(int) { 2 });
	llist_pushfront(&v, &(int) { 1 });
	llist_pushfront(&v, &(int) { 9 });
	llist_addnode(&v, llist_getnode(&v, 2), &(int) { 3 });
	llist_pushback(&v, &(int) { 4 });
	llist_addnode(&v, llist_getnode(&v, 2), &(int) { 3 });
	llist_delnode(&v, llist_getnode(&v, 2));
	llist_popfront(&v);

	p = v.head;
	TRAVERSE_LLIST(p, printf("Value at index %lu: %d\n", i, *(int *) p); i++;);

	llist_deinit(&v);
}
