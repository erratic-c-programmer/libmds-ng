#include <llist.h>

/* PUBLIC UTILITY FUNCTIONS */
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
enum lmds_status llist_init(struct llist *in, const size_t dsize)
{
	NULLCHK(in);

	in->len = 0;
	in->dsize = dsize;
	in->head = NULL;
	in->tail = NULL;

	return LMDS_OK;
}

enum lmds_status llist_deinit(struct llist *in)
{
	struct llist_node *p;
	struct llist_node *prev;

	NULLCHK(in);

	p = in->head;
	prev = NULL;
	TRAVERSE_LLIST(p, free(p->data); free(prev); prev = p;);
	free(in->tail);

	return LMDS_OK;
}


/* INSERT */
enum lmds_status llist_pushback(struct llist *in, const void *val)
{
	struct llist_node *new;
	NULLCHK(in);
	NULLCHK(val);


	new = malloc(sizeof(struct llist_node));

	if (new == NULL)
		return LMDS_ALLOC_FAIL;

	new->data = malloc(in->dsize);

	if (new->data == NULL) {
		free(new);
		return LMDS_ALLOC_FAIL;
	}

	memcpy(new->data, val, in->dsize);

	new->prev = in->tail;
	new->next = NULL;

	if (in->len == 0)
		in->head = in->tail = new;
	else
		in->tail->next = new;

	in->tail = new;
	in->len += 1;

	return LMDS_OK;
}

enum lmds_status llist_addnode(struct llist *in, struct llist_node *nod,
		const void *val)
{
	struct llist_node *new;
	NULLCHK(in);
	NULLCHK(nod);
	NULLCHK(val);

	new = malloc(sizeof(struct llist_node));

	if (new == NULL) {
		free(new);
		return LMDS_ALLOC_FAIL;
	}

	new->data = malloc(in->dsize);

	if (new->data == NULL) {
		free(new);
		return LMDS_ALLOC_FAIL;
	}

	memcpy(new->data, val, in->dsize);

	new->prev = nod->prev;
	new->next = nod;

	nod->prev->next = new;
	nod->prev = new;

	in->len += 1;

	return LMDS_OK;
}

enum lmds_status llist_pushfront(struct llist *in, const void *val)
{
	struct llist_node *new;
	NULLCHK(in);
	NULLCHK(val);

	new = malloc(sizeof(struct llist_node));

	if (new == NULL) {
		free(new);
		return LMDS_ALLOC_FAIL;
	}

	new->data = malloc(in->dsize);

	if (new->data == NULL) {
		free(new);
		return LMDS_ALLOC_FAIL;
	}

	memcpy(new->data, val, in->dsize);

	new->prev = NULL;
	new->next = in->head;

	if (in->len == 0)
		in->head = in->tail = new;
	else
		in->head->prev = new;

	in->head = new;
	in->len += 1;

	return LMDS_OK;
}

enum lmds_status llist_popback(struct llist *in)
{
	struct llist_node *old;

	NULLCHK(in);

	if (in->len == 0)
		return LMDS_OOB;

	old = in->tail;

	if (in->tail != in->head) {
		in->tail->prev->next = NULL;
		in->tail = in->tail->prev;
	}

	free(old->data);
	free(old);

	in->len -= 1;

	return LMDS_OK;
}

enum lmds_status llist_delnode(struct llist *in, struct llist_node *nod)
{
	NULLCHK(in);
	NULLCHK(nod);

	if (nod != in->head)
		nod->prev->next = nod->next;
	if (nod != in->tail)
		nod->next->prev = nod->prev;
	if (nod == in->head)
		in->head = nod->next;
	if (nod == in->tail)
		in->tail = nod->prev;

	free(nod->data);
	free(nod);

	in->len -= 1;

	return LMDS_OK;
}

enum lmds_status llist_popfront(struct llist *in)
{
	NULLCHK(in);

	if (in->len == 0)
		return LMDS_OOB;

	llist_delnode(in, llist_getnode(in, 0));

	return LMDS_OK;
}
