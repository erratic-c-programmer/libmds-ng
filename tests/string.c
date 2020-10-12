#include <stdio.h>
#include "../string/string.h"

int main(void)
{
	struct string s;

	string_init(&s);

	string_append(&s, "Held");
	string_insert(&s, 2, "llo, wor");
	string_grow(&s, 1);
	s.str[s.len - 1] = '!';
	string_insert(&s, 7, "MOUSE ");
	string_delete(&s, 7, 12);

	printf("%s\n", s.str);

	string_deinit(&s);
}
