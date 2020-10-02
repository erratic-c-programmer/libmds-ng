#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../status.h"

/*
 * Macro: TRAVERSE_LLIST
 * traverse a linked list and perform operations on it
 *
 * Parameters:
 *  headptr - head of list to be traversed
 *  actions - actions to perform on each traversal.
 *	          There may be multiple actions; in that case
 *	          separate them with a semicolon
 */
#define TRAVERSE_LLIST(headptr, actions) \
	while (headptr != NULL) { \
		actions; \
		headptr = headptr->next; \
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
 * manually; doing so will result in disastrous consequences.
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
 *	The pointer to the node at position idx. If there
 *	is no such node, or the list is invalid, returns NULL.
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
 *
 * Note:
 *	The list must have been initialised!
 */
enum status llist_deinit(struct llist *in);

/*
 * Function: llist_addnode
 * Adds a node right before nod
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
