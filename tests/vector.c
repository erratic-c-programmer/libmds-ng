#include <stdio.h>
#include "../vector/vector.h"

int main(void)
{
	struct vector v;
	if (vector_init(&v, sizeof(int)) == LMDS_ALLOC_FAIL) {
		printf("ERROR! Out of memory.\n");
		exit(1);
	}
	vector_pushback(&v, &(int) { 2 });
	vector_pushfront(&v, &(int) { 1 });
	vector_pushfront(&v, &(int) { 9 });
	vector_insert(&v, 3, &(int) { 3 });
	vector_pushback(&v, &(int) { 4 });
	vector_insert(&v, 2, &(int) { 3 });
	vector_delete(&v, 2);
	vector_popfront(&v);
	vector_popback(&v);

	for (size_t i = 0; i < v.len; i++)
		printf("Value at index %lu: %d\n", i, *(int *) v.data[i]);

	vector_deinit(&v);
}
