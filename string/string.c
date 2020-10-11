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

	memset(t + in->len, '\0', add * sizeof(char));
	in->str = t;
	in->len += add;

	return OK;
}

enum status string_append(struct string *in, const char *str)
{
	NULLCHK(in);

	RETIFNOK(string_grow(in, strlen(str)));

	strcat(in->str, str);

	return OK;
}
