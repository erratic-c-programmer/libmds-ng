#include <stdio.h>
#include <vector.h>


int main(void)
{
	struct vector new;

	vector_init(&new, sizeof(int));

	for(int i = 0; i < 1000000; i++)
		vector_pushback(&new, &(int) {i});

	printf("Memory used: %lu bytes | Constant size %lu + %lu elements of size (%lu + %lu) each\n", \
			sizeof(struct vector) + new.cap * new.dsize + new.cap * sizeof(void*), \
			sizeof(struct vector), new.cap, new.dsize, sizeof(void*));

	vector_deinit(&new);
}
