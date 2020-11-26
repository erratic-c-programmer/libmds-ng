#include <stdio.h>
#include <llist.h>


int main(void)
{
	struct llist new;

	llist_init(&new, sizeof(int));

	for(int i = 0; i < 1000000; i++)
		llist_pushback(&new, &(int) {i});

	printf("Memory used: %lu bytes | Constant size %lu + %lu nodes of size (%lu + %lu) each\n", \
			new.len * (sizeof(struct llist_node) + sizeof(int)) + sizeof(struct llist), \
			sizeof(struct llist), new.len, sizeof(struct llist_node), sizeof(int));

	llist_deinit(&new);
}
