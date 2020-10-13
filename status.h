/*
 * Enum: status
 * Enumerate the return values of functions
 *
 * OK - OK
 * ALLOC_FAIL - Memory allocation failure
 * OOB - Out of bounds
 * NULLPTR - NULL pointer given
 */
enum status {
	OK = 0,
	ALLOC_FAIL,
	OOB,
	NULLPTR,
};

/* Related error-checking macros */
#define RETIFNOK(val) if (val != OK) return val;
#define NULLCHK(in) if (in == NULL) return NULLPTR;
