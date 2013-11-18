#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * EDAA25: Assignment 3 - Polynomials, by:
 * Ludwig Jacobsson | 870501-2097 | knd09lja
 */

#include "poly.h"


static void poly_test(char* a, char* b)
{
	poly_t*		p;
	poly_t*		q;
	poly_t*		r;

	printf("Begin polynomial test of (%s) * (%s)\n", a, b);

	p = new_poly_from_string(a);
	q = new_poly_from_string(b);

	print_poly(p);
	print_poly(q);

	r = mul(p, q);

	print_poly(r);

	free_poly(p);
	free_poly(q);
	free_poly(r);

	printf("End polynomial test of (%s) * (%s)\n", a, b);
}

int main(void)
{	
	poly_test("x^2 - 7x + 1", "3x + 2");
	poly_test("x^10000000 + 2", "2x^2 + 3x + 4");

	return 0;
}
