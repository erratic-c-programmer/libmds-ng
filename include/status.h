#ifndef STATUS_H
#define STATUS_H

/*
 * Enum: status
 * Enumerate the return values of functions
 *
 * OK - OK
 * ALLOC_FAIL - Memory allocation failure
 * OOB - Out of bounds
 * NULLPTR - NULL pointer given
 */
enum lmds_status {
	LMDS_OK = 0,
	LMDS_ALLOC_FAIL,
	LMDS_OOB,
	LMDS_NULLPTR,
};

/* Related error-checking macros */
#define RETIFNOK(val) if (val != LMDS_OK) return val;
#define NULLCHK(in) if (in == NULL) return LMDS_NULLPTR;

#endif /* STATUS_H */
