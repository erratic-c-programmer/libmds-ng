#include <stdio.h>
#include "../string/string.h"

int main(void)
{
	struct string s;

	string_init(&s);

	string_append(&s, "Held!");
	string_insert(&s, 2, "llo, wor");

	printf("%s\n", s.str);

	string_deinit(&s);
}
