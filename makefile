# EDAA25: Assignment 3 - Polynomials, by
# Ludwig Jacobsson | 870501-2097 | knd09lja

CC=gcc
CFLAGS=-I -g

polymake: poly_test.c poly.c
	$(CC) -o poly_test poly_test.c poly.c -I.

clean:
	rm -f poly_test	
