#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <status.h>

#define VEC_INIT_SZ 4
#define VEC_INCR_OP(osz) (osz*2)

/*
 * Struct: vector
 * A dynamic vector.
 * Supports pushback, pushfront, random insertion,
 * and the equivalants of those for popping. This struct should *only*
 * be operated on by the vector_* functions! Do not attempt to manually
 * modify any of the members manually; doing so will result in disastrous
 * consequences. Except for the data array; you can modify it like this:
 *
 * === Code
 * memcpy(in->data[idx], val, in->dsize);
 * ===
 *
 * But it is encouraged to use the function <vector_modify> instead
 */
struct vector {
	/*
	 * Property: len
	 * Length of the vector.
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
 *  in - vector to operate on
 *  dsize - size of data to be pushed into data
 *
 * Returns:
 *  <lmds_status>
 *
 * Note:
 *  Remember to call <vector_deinit> later, or there will be
 *  memory leaks!
 *
 * See also:
 *  <vector_deinit>
 */
enum lmds_status vector_init(struct vector *in, const size_t dsize);

/* Function: vector_deinit
 * De-initialises a vector
 *
 * Parameters:
 *  in - vector to operate on
 *
 * Returns:
 *  <lmds_status>
 *
 * Note:
 *  The vector must have been initialised!
 */
enum lmds_status vector_deinit(struct vector *in);

/*
 * Function: vector_pushback
 * Pushes a value to the back of the vector.
 *
 * Parameters:
 *  in - vector to operate on
 *  val - pointer to value to push
 */
enum lmds_status vector_pushback(struct vector *in, const void *val);

/*
 * Function: vector_insert
 * Inserts a value at a specified index. The value will be
 * placed _at_ the index. It pushes the rest of the elements, if any,
 * back.
 *
 * Parameters:
 *  in - vector to operate on
 *  idx - index to insert at
 *  val - pointer to value to insert
 *
 * Returns:
 *  <lmds_status>
 *
 * Note:
 * idx must not be greater than len.
 */
enum lmds_status vector_insert(struct vector *in, const size_t idx,
						  const void *val);

/*
 * Function: vector_pushfront
 * Pushes a value to the front of the vector.
 *
 * Returns:
 *  <lmds_status>
 *
 * Parameters:
 *  in - vector to operate on
 *  val - pointer to value to push
 */
enum lmds_status vector_pushfront(struct vector *in, const void *val);

/*
 * Function: vector_popback
 * Pops a value from the back of the vector.
 *
 * Parameters:
 *  in - vector to operate on
 *
 * Returns:
 *  <lmds_status>
 */
enum lmds_status vector_popback(struct vector *in);

/*
 * Function: vector_delete
 * Deletes a value at a specified index. The value _at_ the
 * index will be deleted.
 *
 * Parameters:
 *  in - vector to operate on
 *  idx - index to delete
 *
 * Returns:
 *  <lmds_status>
 *
 * Note:
 * idx must be strictly smaller than len.
 */
enum lmds_status vector_delete(struct vector *in, const size_t idx);

/*
 * Function: vector_popfront
 * Pops a value from the front of the vector.
 *
 * Parameters:
 *  in - vector to operate on
 *
 * Returns:
 *  <lmds_status>
 */
enum lmds_status vector_popfront(struct vector *in);

/*
 * Function: vector_modify
 * Modify the value in the vector at idx
 *
 * Parameters:
 *  in - vector to operate on
 *  idx - index to modify
 *  val - new value
 *
 * Returns:
 *  <lmds_status>
 */
enum lmds_status vector_modify(struct vector *in, const size_t idx,
						  const void *val);

#endif /* VECTOR_H */
