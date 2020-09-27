#include "vector.h"

static void realloc_if_needed(struct vector *in, const size_t needed)
{
	void **t;
	size_t newsz;

	if (in->len + needed > in->cap) {
		newsz = VEC_INCR_OP(in->cap);

		t = realloc(in->data, newsz * sizeof(void *));
		in->data = t;

		for (size_t i = in->cap; i < newsz; i++)
			in->data[i] = malloc(in->dsize);

		in->cap = newsz;
	}
}

void vector_init(struct vector *in, const size_t dsize)
{
	in->len = 0;
	in->cap = VEC_INIT_SZ;
	in->dsize = dsize;
	in->data = calloc(VEC_INIT_SZ, sizeof(void *));
	for (int i = 0; i < VEC_INIT_SZ; i++) {
		in->data[i] = malloc(in->dsize);
	}
}

void vector_deinit(struct vector *in)
{
	for (size_t i = 0; i < in->cap; i++) {
		free(in->data[i]);
	}
	free(in->data);
}

void vector_pushback(struct vector *in, const void *val)
{
	realloc_if_needed(in, 1);
	memcpy(in->data[in->len], val, in->dsize);
	in->len += 1;
}

void vector_pushfront(struct vector *in, const void *val)
{
	realloc_if_needed(in, 1);
	for (int i = in->len; i > 0; i--)
		memcpy(in->data[i], in->data[i - 1], in->dsize);

	memcpy(in->data[0], val, in->dsize);
	in->len += 1;
}

void vector_popback(struct vector *in)
{
	in->len -= 1;
}

void vector_popfront(struct vector *in)
{
	for (size_t i = 1; i < in->len; i--)
		memcpy(in->data[i - 1], in->data[i], in->dsize);
	in->len -= 1;
}
