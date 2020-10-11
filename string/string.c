#include "string.h"

/* INIT/DEINIT */
enum status string_init(struct string *in)
{
	NULLCHK(in);

	in->len = 0;
	in->str = NULL;
	return OK;
}

enum status string_deinit(struct string *in)
{
	NULLCHK(in);

	free(in->str);
	return OK;
}

/* MISC */
enum status string_grow(struct string *in, const size_t add)
{
	char *t;

	NULLCHK(in);

	t = realloc(in->str, (in->len + add + 1) * sizeof(char));

	if (t == NULL)
		return ALLOC_FAIL;

	memset(t + in->len, '\0', (add + 1) * sizeof(char));
	in->str = t;
	in->len += add;

	return OK;
}

enum status string_append(struct string *in, const char *str)
{
	NULLCHK(in);
	NULLCHK(str);

	RETIFNOK(string_grow(in, strlen(str)));

	strcat(in->str, str);

	return OK;
}

enum status string_insert(struct string *in, const size_t idx, const char *str)
{
	size_t oldlen;
	size_t len;

	NULLCHK(in);
	NULLCHK(str);

	len = strlen(str);
	oldlen = in->len;

	RETIFNOK(string_grow(in, len));
	memmove(in->str + idx + len, in->str + idx,
			(oldlen - idx) * sizeof(char));
	memcpy(in->str + idx, str, len * sizeof(char));

	return OK;
}
