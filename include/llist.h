#ifndef LLIST_H
#define LLIST_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "../status.h"

/*
 * Macro: TRAVERSE_LLIST
 * traverse a linked list and perform operations on it
 *
 * Parameters:
 *  headptr - _COPY OF_ head of list to be traversed
 *  actions - actions to perform on each traversal.
 *	          There may be multiple actions; in that case
 *	          separate them with a semicolon
 *
 * Warning:
 *  Directly passing the head of the linked list will result in
 *  corruption!
 *
 * See also:
 *  <TRAVERSE_LLIST_BACK>
 */
#define TRAVERSE_LLIST(headptr, actions) \
	while (headptr != NULL) { \
		actions; \
		headptr = headptr->next; \
	}

/*
 * Macro: TRAVERSE_LLIST_BACK
 * traverse a linked list backwards and perform operations on it
 *
 * Parameters:
 *  tailptr - _COPY OF_ tail of list to be traversed
 *  actions - actions to perform on each traversal.
 *	          There may be multiple actions; in that case
 *	          separate them with a semicolon
 *
 * Warning:
 *  Directly passing the tail of the linked list will result in
 *  corruption!
 *
 * See also:
 *  <TRAVERSE_LLIST>
 */
#define TRAVERSE_LLIST_BACK(tailptr, actions) \
	while (tailptr != NULL) { \
		actions; \
		tailptr = tailptr->prev; \
	}

/*
 * Struct: llist_node
 * A node in an <llist>
 */
struct llist_node {
	/*
	 * Property: data
	 * Where the data is stored.
	 */
	void *data;

	/*
	 * Property: next
	 * Pointer to the next node. If this is the last,
	 * then NULL.
	 */
	struct llist_node *next;

	/*
	 * Property: prev
	 * Pointer to the previous node. If this is the first,
	 * then NULL.
	 */
	struct llist_node *prev;
};

/*
 * Struct: llist
 * A dynamic linked list.
 * Supports pushback, pushfront, random insertion,
 * and the equivalant for popping. This struct should *only* be operated on by
 * the llist_* functions! Do not attempt to manually modify any of the members
 * manually; doing so will result in disastrous consequences. Except for the data
 * in nodes; you can modify them like this:
 * === Code
 * memcpy(node->data, val, in->dsize);
 * ===
 */
struct llist {
	/*
	 * Property: len
	 * Holds length of the list.
	 * Trying to access elements after this is
	 * undefined behaviour.
	 */
	size_t len;

	/*
	 * Property: dsize
	 * Size of each element.
	 */
	size_t dsize;

	/*
	 * Property: head
	 * Pointer to the head of the list
	 */
	struct llist_node *head;

	/*
	 * Property: tail
	 * Pointer to the tail of the list
	 */
	struct llist_node *tail;
};

/* Function: llist_getnode
 * Gets the pointer to the node at position idx.
 *
 * Parameters:
 *	in - list to operate on
 *	idx - position to get
 *
 * Returns:
 *	The node at position idx. If there is no such node, or
 *	the list is invalid, returns NULL.
 */
struct llist_node *llist_getnode(struct llist *in, const size_t idx);

/* Function: llist_init
 * Initialises a llist
 *
 * Parameters:
 *	in - list to operate on
 *	dsize - size of data to be pushed into data
 *
 * Returns:
 *	<status>
 *
 * Note:
 *	Remember to call <llist_deinit> later, or there will be
 *	memory leaks!
 *
 * See also:
 *	<llist_deinit>
 */
enum status llist_init(struct llist *in, const size_t dsize);

/* Function: llist_deinit
 * De-initialises a list
 *
 * Parameters:
 *	in - list to operate on
 *
 * Returns:
 *	<status>
 */
enum status llist_deinit(struct llist *in);

/*
 * Function: llist_addnode
 * Adds a node _right at_ nod, pushing outher nodes, if any, back.
 *
 * Parameters:
 *	in - list to operate on
 *	val - pointer to value to push
 */
enum status llist_addnode(struct llist *in, struct llist_node *nod,
						  const void *val);

/*
 * Function: llist_pushback
 * Pushes a value to the back of the list.
 *
 * Returns:
 *	<status>
 *
 * Parameters:
 *	in - list to operate on
 *	val - pointer to value to push
 */
enum status llist_pushback(struct llist *in, const void *val);

/*
 * Function: llist_pushfront
 * Pushes a value to the front of the list.
 *
 * Returns:
 *	<status>
 *
 * Parameters:
 *	in - list to operate on
 *	val - pointer to value to push
 */
enum status llist_pushfront(struct llist *in, const void *val);

/*
 * Function: llist_popback
 * Pops a value from the back of the list.
 *
 * Parameters:
 *	in - list to operate on
 *
 * Returns:
 *	<status>
 */
enum status llist_popback(struct llist *in);

/*
 * Function: llist_delnode
 * Deletes a node from a linked list
 *
 * Parameters:
 *	in - list to operate on
 *	nod - pointer to node to delete
 *
 * Returns:
 *	<status>
 */
enum status llist_delnode(struct llist *in, struct llist_node *nod);

/*
 * Function: llist_popfront
 * Pops a value from the front of the list.
 *
 * Parameters:
 *	in - list to operate on
 *
 * Returns:
 *	<status>
 */
enum status llist_popfront(struct llist *in);

#endif /* LLIST_H */
