#ifndef poly_h
#define poly_h

/* EDAA25: Assignment 3 - Polynomials, by:
 * Ludwig Jacobsson | 870501-2097 | knd09lja
 */

#define MAX 10

typedef struct poly_t poly_t;
typedef struct term term;

struct term {
	int coeff;
	int exp;
};

struct poly_t {
	/*
	 * term:
	 * [[1:term], [2:term], ... [(MAX-1):term]
	 */

	struct term t[MAX];
	int no_terms;
};


poly_t*			new_poly_from_string(const char*);
void			free_poly(poly_t*);


poly_t*			mul(poly_t*, poly_t*);

void 			print_poly(poly_t*);



#endif
