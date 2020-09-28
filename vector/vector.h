#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define VEC_INIT_SZ 4
#define VEC_INCR_OP(osz) (osz*2)

/*
 * Struct: vector
 * A dynamic vector.
 * Supports pushback, pushfront, random insertion,
 * and the equivalant for popping. This struct should *only* be operated on by
 * the vector_* functions! Do not attempt to manually modify any of the members
 * manually; doing so will result in disastrous consequences.
 */
struct vector {
	/*
	 * Property: len
	 * Holds length of the vector.
	 * Trying to access elements after this is
	 * undefined behaviour.
	 */
	size_t len;

	/* This member is not for public use */
	size_t cap;

	/*
	 * Property: dsize
	 * Size of each element.
	 */
	size_t dsize;

	/*
	 * Property: data
	 * Where all the data is stored.
	 */
	void **data;
};

/* Function: vector_init
 * Initialises a vector
 *
 * Parameters:
 *	in - vector to operate on
 *	dsize - size of data to be pushed into data
 *
 * Note:
 *	Remember to call <vector_deinit> later, or there will be
 *	memory leaks!
 *
 * See also:
 *	<vector_deinit>
 */
void vector_init(struct vector *in, const size_t dsize);

/* Function: vector_deinit
 * De-initialises a vector
 *
 * Parameters:
 *	in - vector to operate on
 *
 * Note:
 *	If the vector has not yet been initialised,
 *	*the program will crash, badly.*
 */
void vector_deinit(struct vector *in);

/*
 * Function: vector_pushback
 * Pushes a value to the back of the vector.
 *
 * Parameters:
 *	in - vector to operate on
 *	val - value to push
 */
void vector_pushback(struct vector *in, const void *val);

/*
 * Function: vector_pushfront
 * Pushes a value to the front of the vector.
 *
 * Parameters:
 *	in - vector to operate on
 *	val - value to push
 */
void vector_pushfront(struct vector *in, const void *val);

/*
 * Function: vector_popback
 * Pops a value from the back of the vector.
 *
 * Parameters:
 *	in - vector to operate on
 */
void vector_popback(struct vector *in);

/*
 * Function: vector_delete
 * Deletes a value at a specified index. The value _at_ the
 * index will be deleted.
 *
 * Parameters:
 *	in - vector to operate on
 *	idx - index to insert at
 *
 * Note:
 * idx must be less than len and greater or equal to 0.
 */
void vector_delete(struct vector *in, const size_t idx);

/*
 * Function: vector_popfront
 * Pops a value from the front of the vector.
 *
 * Parameters:
 *	in - vector to operate on
 */
void vector_popfront(struct vector *in);
