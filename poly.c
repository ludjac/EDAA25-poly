#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/*
 * EDAA25: Assignment 3 - Polynomials, by:
 * Ludwig Jacobsson | 870501-2097 | knd09lja
 */ 

#include "poly.h"

void init_poly(poly_t*);
void add_term(poly_t*, int, int);
int get_coeff(char*);
int get_exp(char*);

poly_t* new_poly_from_string(const char* poly_str_in)
{
       	poly_t* 	poly;
	int 		sign;	
	char*		poly_str;
	char*		term_str;	

	poly = malloc(sizeof(poly_t));
	// Memory allocation check
	assert(poly != NULL);

	init_poly(poly);
	
	sign = 1;

	// strdup(char*) - duplicate string	
	poly_str = strdup(poly_str_in);
	// strtok(char*, char*) split string on delimiter (second input)
	term_str = strtok(poly_str, " ");
	while (term_str != NULL) {
		
		if ((term_str[0] == '+') || (term_str[0] == '-')) {
			if (term_str[0] == '+'){
				sign = 1;
			} else {
				sign = -1;
			}
		}
		if ((term_str[0] != '+') && (term_str[0] != '-'))
		{
			add_term(poly, sign*get_coeff(term_str), get_exp(term_str));
		}
	// Move to next piece of the string
	term_str = strtok(NULL, " ");	
	}
	return poly;
}

poly_t* mul(poly_t* poly_1, poly_t* poly_2)
{
	poly_t*		poly_r;
	int 		ind_1, ind_2, coeff, exp;

	poly_r = malloc(sizeof(poly_t));
	assert(poly_r != NULL);

	init_poly(poly_r);

	for (ind_1 = 0; ind_1 < poly_1->no_terms; ind_1++) {
		for (ind_2 = 0; ind_2 < poly_2->no_terms; ind_2++) {
			coeff = poly_1->t[ind_1].coeff*poly_2->t[ind_2].coeff;
			exp = poly_1->t[ind_1].exp+poly_2->t[ind_2].exp;
			add_term(poly_r,  coeff, exp);
		}
	}

	return poly_r;
}

void free_poly(poly_t* poly)
{
	assert(poly != NULL);

	free(poly);
}

int sign(int i)
{
	/*
	 * returns the sign of the int.
	 */

	return (i>0)-(i<0);
}

int abs(int i)
{
	/*
	 *Returns the absolute value of the int.
	 */

	return sign(i)*i;
}

void print_poly(poly_t* poly)
{
	int	k, coeff, exp;
	
	for (k=0; k < (poly->no_terms); k++) {
		coeff 	= poly->t[k].coeff;
		exp	= poly->t[k].exp;
		// Print sign
		if (k > 0) {
			if (sign(coeff)==-1) {
				printf(" - ");
			} else {
				printf(" + ");
			}
			coeff = abs(coeff);
		}
		
		if (exp > 0) {
			if (coeff == 1) {
				printf("x^%d", exp);
			} else{
				printf("%dx^%d", coeff, exp);
			}
		} else {
			printf("%d", coeff);
		}
	}
	printf("\n");
}

int get_coeff(char* term_str)
{
	if (isdigit(term_str[0])) {
		return term_str[0] - '0';
	} else {
		return 1;
	}
}

int get_exp(char* term_str)
{
	char* 	temp;
	int 	k, exp;

	// Cannot utilize strtok() again since it manipulates the string. 
	// ie. the previous string would be changed.
	
	// strchr(char*, char) - returns a pointer to the first instance of the
	// char in the string.  
	if ((temp = strchr(term_str, '^')) != NULL){
		// Length of the exponent
		int exp_length = strlen(term_str)-(temp-term_str)-1;
		char exp_str[exp_length];
		// Build the exponent
		for (k = 0; k <= exp_length; k++) {
			exp_str[k] = *(temp+k+1);
		}
		// atoi(char*) - convert string to int. 
		// Could use some check to see if exp_str is digits. 
		return atoi(exp_str);
	} else if ((strchr(term_str, '^') == NULL) && (strchr(term_str, 'x') != NULL)) {	
		return 1;
	} else {
		return 0;
		}
}

void add_term(poly_t* poly, int coeff, int exp)
{
	int i;
	// Check if there are any excisting terms 
	// of the same power as input - then add.  
	for (i = 0; i<poly->no_terms; i++) {
		if (poly->t[i].exp == exp) {
			poly->t[i].coeff += coeff;
			return;	
		}
	}

	poly->t[poly->no_terms].coeff = coeff;
	poly->t[poly->no_terms].exp = exp;
	(poly->no_terms)++;
}

void init_poly(poly_t* poly)
{	
	int	k;
	for (k = 0; k<MAX; k++){
		poly->t[k].coeff = 0;
		poly->t[k].exp = 0;
	}
	poly->no_terms = 0;
}
