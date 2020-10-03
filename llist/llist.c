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
	TRAVERSE_LLIST(p, if (i++ == idx) return p;);

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

	return OK;
}

enum status llist_deinit(struct llist *in)
{
	struct llist_node *p;
	struct llist_node *prev;

	NULLCHK(in);

	p = in->head;
	prev = NULL;
	TRAVERSE_LLIST(p, free(p->data); free(prev); prev = p;);
	free(in->tail);

	return OK;
}


/* INSERT */
enum status llist_pushback(struct llist *in, const void *val)
{
	struct llist_node *new;
	NULLCHK(in);
	NULLCHK(val);


	new = malloc(sizeof(struct llist_node));

	if (new == NULL)
		return ALLOC_FAIL;

	new->data = malloc(in->dsize);

	if (new->data == NULL)
		return ALLOC_FAIL;

	memcpy(new->data, val, in->dsize);

	new->prev = in->tail;
	new->next = NULL;

	if (in->len == 0)
		in->head = in->tail = new;
	else
		in->tail->next = new;

	in->tail = new;
	in->len += 1;

	return OK;
}

enum status llist_addnode(struct llist *in, struct llist_node *nod,
		const void *val)
{
	struct llist_node *new;
	NULLCHK(in);
	NULLCHK(nod);
	NULLCHK(val);

	new = malloc(sizeof(struct llist_node));

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

enum status llist_pushfront(struct llist *in, const void *val)
{
	struct llist_node *new;
	NULLCHK(in);
	NULLCHK(val);

	new = malloc(sizeof(struct llist_node));

	if (new == NULL)
		return ALLOC_FAIL;

	new->data = malloc(in->dsize);

	if (new->data == NULL)
		return ALLOC_FAIL;

	memcpy(new->data, val, in->dsize);

	new->prev = NULL;
	new->next = in->head;

	if (in->len == 0)
		in->head = in->tail = new;
	else
		in->head->prev = new;

	in->head = new;
	in->len += 1;

	return OK;
}

enum status llist_popback(struct llist *in)
{
	NULLCHK(in);

	if (in->len == 0)
		return OOB;

	free(in->tail->data);
	in->tail->prev->next = NULL;
	free(in->tail);

	in->len -= 1;

	return OK;
}

enum status llist_delnode(struct llist *in, struct llist_node *nod)
{
	NULLCHK(in);
	NULLCHK(nod);

	if (nod != in->head)
		nod->prev->next = nod->next;
	if (nod != in->tail)
		nod->next->prev = nod->prev;
	free(nod->data);
	free(nod);

	in->len -= 1;

	return OK;
}

enum status llist_popfront(struct llist *in)
{
	NULLCHK(in);

	if (in->len == 0)
		return OOB;

	in->head->next->prev = NULL;
	free(in->head->data);
	free(in->head);

	in->len -= 1;

	return OK;
}
