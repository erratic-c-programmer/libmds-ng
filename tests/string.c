#include <stdio.h>
#include "../string/string.h"

int main(void)
{
	struct string s;

	string_init(&s);

	string_append(&s, "Hello, world!");

	printf("%s\n", s.str);

	string_deinit(&s);
}
