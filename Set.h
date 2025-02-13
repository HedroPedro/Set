#ifndef SET_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#define PRINT_ERROR(reason, func) fprintf(stderr, "ERRO: '%s'; LINHA: %i; FUNCAO: %s", reason, __LINE__, #func)
#define PRINT_SET(set) printf("%s = ", #set); \
		 print(set)

typedef struct value {
	int value;
	bool is_set;
} Value;

typedef struct set {
	Value *values;
	int actual_size;
	int m;
} Set;

inline int hash(int k, int m);
inline Set* create_empty(int size);
void add(Set* set, int key);
Set *create_set(int size, int *arr);
bool isEmpty(Set* set);
bool isIn(Set *set, int elem);
bool isNotIn(Set *set, int elem);
bool isDisjoint(Set *set1, Set *set2);
bool isSubSet(Set *set1, Set *set2);
bool isSuperSet(Set *set1, Set *set2);
int len(Set *set);
int pop(Set* set);
void removeElem(Set *set, int elem);
void print(Set* set);
void clear(Set *set);
void copy(Set *set1, Set *set2);
Set *Union(Set *set1, Set *set2);
Set *Intersection(Set *set1, Set *set2);
Set *Difference(Set *set1, Set *set2);
Set *Symmetric_difference(Set *set1, Set *set2);
void free_set(Set** set);
#endif // !SET_H_

