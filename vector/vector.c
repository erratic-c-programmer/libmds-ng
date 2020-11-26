#include <vector.h>

/* UTILITIY FUNCTIONS */
static enum lmds_status realloc_if_needed(struct vector *in,
									 const size_t needed)
{
	/*
	 * in and in->data should have been checked before calling
	 * this function!
	 */

	void **t;
	size_t newsz;

	if (in->len + needed > in->cap) {
		newsz = VEC_INCR_OP(in->cap);

		t = realloc(in->data, newsz * sizeof(void *));

		if (t == NULL)
			return LMDS_ALLOC_FAIL;

		in->data = t;

		for (size_t i = in->cap; i < newsz; i++)
			in->data[i] = malloc(in->dsize);

		in->cap = newsz;
	}

	return LMDS_OK;
}


/* INIT/DEINIIT */
enum lmds_status vector_init(struct vector *in, const size_t dsize)
{
	NULLCHK(in);

	in->len = 0;
	in->cap = VEC_INIT_SZ;
	in->dsize = dsize;
	in->data = calloc(VEC_INIT_SZ, sizeof(void *));

	if (in->data == NULL)
		return LMDS_ALLOC_FAIL;

	for (int i = 0; i < VEC_INIT_SZ; i++) {
		in->data[i] = malloc(in->dsize);

		if (in->data[i] == NULL) {
			/* Free previously allocated memory */
			in->cap = i == 0 ? 0 : i - 1;
			vector_deinit(in);
			return LMDS_ALLOC_FAIL;
		}
	}

	return LMDS_OK;
}

enum lmds_status vector_deinit(struct vector *in)
{
	NULLCHK(in);
	NULLCHK(in->data);

	for (size_t i = 0; i < in->cap; i++)
		free(in->data[i]);
	free(in->data);
	return LMDS_OK;
}


/* INSERT */
enum lmds_status vector_pushback(struct vector *in, const void *val)
{
	NULLCHK(in);
	NULLCHK(in->data);
	NULLCHK(val);

	RETIFNOK(realloc_if_needed(in, 1));
	memcpy(in->data[in->len], val, in->dsize);
	in->len += 1;

	return LMDS_OK;
}

enum lmds_status vector_insert(struct vector *in, const size_t idx,
						  const void *val)
{
	NULLCHK(in);
	NULLCHK(in->data);
	NULLCHK(val);
	if (idx > in->len)
		return LMDS_OOB;

	RETIFNOK(realloc_if_needed(in, 1));
	for (size_t i = in->len; i > idx; i--)
		memcpy(in->data[i], in->data[i - 1], in->dsize);

	memcpy(in->data[idx], val, in->dsize);
	in->len += 1;

	return LMDS_OK;
}


/* DELETE */
enum lmds_status vector_pushfront(struct vector *in, const void *val)
{
	NULLCHK(in);
	NULLCHK(in->data);
	NULLCHK(val);

	vector_insert(in, 0, val);

	return LMDS_OK;
}

enum lmds_status vector_popback(struct vector *in)
{
	NULLCHK(in);
	NULLCHK(in->data);

	in->len -= 1;

	return LMDS_OK;
}

enum lmds_status vector_delete(struct vector *in, const size_t idx)
{
	NULLCHK(in);
	NULLCHK(in->data);
	if (idx >= in->len)
		return LMDS_OOB;

	for (size_t i = idx + 1; i < in->len; i++)
		memcpy(in->data[i - 1], in->data[i], in->dsize);
	in->len -= 1;

	return LMDS_OK;
}

enum lmds_status vector_popfront(struct vector *in)
{
	NULLCHK(in);
	NULLCHK(in->data);

	vector_delete(in, 0);

	return LMDS_OK;
}

enum lmds_status vector_modify(struct vector *in, const size_t idx,
		const void *val)
{
	NULLCHK(in);
	NULLCHK(in->data);
	NULLCHK(val);

	memcpy(in->data[idx], val, in->dsize);

	return LMDS_OK;
}
