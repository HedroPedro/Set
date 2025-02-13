#include <stdio.h>
#include <time.h>
#include "Set.h"

int main() {
	srand(clock() >> 4);
	Set* A = create_set(5, ((int []) { 2, 4, 2, 1, 5 }));
	Set* B = create_set(4, ((int[]) {3, 5, 5, 5}));
	Set* C = create_set(1, ((int[]) {-9}));
	Set* D = create_empty(5);

	PRINT_SET(A);
	PRINT_SET(B);
	PRINT_SET(C);
	PRINT_SET(D);

	Set* UnionAB = Union(A, B);
	Set* InterAB = Intersection(A, B);
	Set* SymDiffAB = Symmetric_difference(A, B);
	Set* DiffBD = Difference(B, D);

	PRINT_SET(UnionAB);
	PRINT_SET(InterAB);
	PRINT_SET(SymDiffAB);
	PRINT_SET(DiffBD);

	printf("A intersecao entre C e A e vazia? %i\n", isDisjoint(A, C));
	printf("Conjunto D e vazio? %i\n", isEmpty(D));
	printf("D e subconjunto de A? %i\n", isSubSet(D, A));
	printf("C e superconjunto de D? %i\n", isSuperSet(C, D));
	printf("B e superconjunto de A? %i\n", isSuperSet(B, A));

	printf("O valor removido de A foi: %i\n", pop(A));
	removeElem(B, 3);

	PRINT_SET(A);
	PRINT_SET(B);

	add(D, 7);
	add(D, 7);
	add(D, 7);
	PRINT_SET(D);
	
	clear(A);
	PRINT_SET(A);
	
	free_set(&A);
	free_set(&B);
	free_set(&C);
	free_set(&D);
	free_set(&UnionAB);
	free_set(&InterAB);
	free_set(&SymDiffAB);
	free_set(&DiffBD);
}