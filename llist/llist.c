#include "llist.h"

/* PUBLIC UTILITY FUNTIONS */
struct llist_node *llist_getnode(struct llist *in, const size_t idx)
{
	size_t i;
	struct llist_node *p;

	if (in == NULL)
		return NULL;

	i = 0;
	p = in->head;
	TRAVERSE_LLIST(p, i++; if (i == idx) return p;);

	return NULL;
}

/* INIT/DEINIT */
enum status llist_init(struct llist *in, const size_t dsize)
{
	NULLCHK(in);

	in->len = 0;
	in->dsize = dsize;
	in->head = NULL;
	in->tail = NULL;
	in->end = malloc(sizeof(struct llist_node *));

	return OK;
}

enum status llist_deinit(struct llist *in)
{
	struct llist_node *p;

	NULLCHK(in);

	p = in->head;
	TRAVERSE_LLIST(p, free(p););

	return OK;
}


/* INSERT */
enum status llist_addnode(struct llist *in, struct llist_node *nod,
		const void *val)
{
	struct llist_node *new;
	NULLCHK(nod);

	new = malloc(sizeof(struct llist_node *));

	if (new == NULL)
		return ALLOC_FAIL;

	new->data = malloc(in->dsize);

	if (new->data == NULL)
		return ALLOC_FAIL;

	memcpy(new->data, val, in->dsize);

	new->prev = nod->prev;
	new->next = nod;
	nod->prev = new;
	nod->prev->next = new;

	in->len += 1;

	return OK;
}
