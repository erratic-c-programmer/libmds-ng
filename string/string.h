#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../status.h"

/* Struct: string
 * A dynamic string.
 * Supports append, random insertion, random deletion and
 * on-demand resizing.
 * You may rather liberally modify the str array:
 * === Code
 * in->str[4] = 'H'
 * ===
 * But be careful that you do not write past the end of the buffer.
 */
struct string {
	/*
	 * Property: len
	 * Length of the vector.
	 * Trying to access elements after this is
	 * undefined behaviour.
	 */
	size_t len;

	/*
	 * Property: str
	 * The C string used to store data
	 */
	char *str;
};

/* Function: string_init
 * Initialises a string
 *
 * Parameters:
 *  in - string to operate on
 *
 * Returns:
 *  <status>
 */
enum status string_init(struct string *in);

/* Function: string_init
 * De-initialises a string
 *
 * Parameters:
 *  in - string to operate on
 *
 * Returns:
 *  <status>
 */
enum status string_deinit(struct string *in);

/* Function: string_grow
 * Grows a string
 *
 * Parameters:
 *  in - string to operate on
 *  add - how many characters to grow by
 *
 * Returns:
 *  <status>
 *
 * Note:
 *  The new space will be initialised to NULL.
 */
enum status string_grow(struct string *in, const size_t add);

/* Function: string_append
 * Appends a C char array to a string
 * Parameters:
 *  in - string to operate on
 *  str - char array to append
 *
 * Returns:
 *  <status>
 *
 * Note:
 *  str must be NULL-terminated.
 */
enum status string_append(struct string *in, const char *str);

/* Function: string_insert
 * Inserts a C char array in a string _at_ the specified index.
 * All other characters, if any, will be pushed back.
 * Parameters:
 *  in - string to operate on
 *  idx - index to insert at
 *  str - char array to insert
 *
 * Returns:
 *  <status>
 *
 * Note:
 *  str must be NULL-terminated.
 */
enum status string_insert(struct string *in, const size_t idx, const char *str);
