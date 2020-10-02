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

	/*
	 * Property: end
	 * Pointer to a virtual node right after the tail.
	 * Writeing to this is undefined behaviour.
	 */

	struct lllist_node *end;
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
 * Function: vector_insert
 * Inserts a value at a specified index. The value will be
 * placed _at_ the index
 *
 * Parameters:
 *	in - vector to operate on
 *	idx - index to insert at
 *	val - pointer to value to insert
 *
 * Returns:
 *	<status>
 *
 * Note:
 * idx must not be greater than len.
 */
enum status vector_insert(struct vector *in, const size_t idx,
		const void *val);

/*
 * Function: vector_pushfront
 * Pushes a value to the front of the vector.
 *
 * Returns:
 *	<status>
 *
 * Parameters:
 *	in - vector to operate on
 *	val - pointer to value to push
 */
enum status vector_pushfront(struct vector *in, const void *val);

/*
 * Function: vector_popback
 * Pops a value from the back of the vector.
 *
 * Parameters:
 *	in - vector to operate on
 *
 * Returns:
 *	<status>
 */
enum status vector_popback(struct vector *in);

/*
 * Function: vector_delete
 * Deletes a value at a specified index. The value _at_ the
 * index will be deleted.
 *
 * Parameters:
 *	in - vector to operate on
 *	idx - index to insert at
 *
 * Returns:
 *	<status>
 *
 * Note:
 * idx must be strictly smaller than len.
 */
enum status vector_delete(struct vector *in, const size_t idx);

/*
 * Function: vector_popfront
 * Pops a value from the front of the vector.
 *
 * Parameters:
 *	in - vector to operate on
 *
 * Returns:
 *	<status>
 */
enum status vector_popfront(struct vector *in);
