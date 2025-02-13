#include "Set.h"

inline int hash(int k, int m) {
	k ^= (k >> 8) | (k << 11);
	k *= 0xCD4457AB;
	k = (k << 13) | (k >> 17);
	return abs(k % m);
}

inline Set* create_empty(int size) {
	Set* set = (Set*)malloc(sizeof(Set));
	if (set == NULL) {
		PRINT_ERROR("SEM ESPACO PARA ALOCAR CONJUNTO", create_set);
		exit(EXIT_FAILURE);
	}

	set->m = size > 0 ? size : 1;
	set->actual_size = 0;
	set->values = (Value*) calloc(size, sizeof(Value));
	if (set->values == NULL) {
		PRINT_ERROR("SEM ESPACO PARA ALOCAR VETOR", create_set);
		exit(EXIT_FAILURE);
	}

	return set;
}

void add(Set* set, int elem) {
	if (isIn(set, elem)) return;

	if (set->actual_size == set->m) {
		PRINT_ERROR("CONJUNTO CHEIO", add);
		exit(EXIT_FAILURE);
	}

	int k = hash(elem, set->m);
	int prev = k;
	while (set->values[k].is_set && k < set->m) k++;
	
	if (k == set->m) {
		k = 0;
		while (k < prev && set->values[k].is_set) k++;
	}

	set->actual_size++;
	set->values[k].is_set = true;
	set->values[k].value = elem;
}

Set *create_set(int size, int* arr) {
	Set *set = create_empty(size);

	for(int i = 0; i < size; i++) {
		add(set, arr[i]);
	}

	return set;
}

bool isEmpty(Set* set) {
	return !set->actual_size;
}

bool isIn(Set* set, int elem) {
	int k = hash(elem, set->m);
	int prev = k;
	for (k; k < set->m; k++) {
		if (set->values[k].is_set && set->values[k].value == elem)
			return true;
	}

	for (int i = 0; i < prev; i++) {
		if (set->values[i].is_set && set->values[i].value == elem)
			return true;
	}

	return false;
}

bool isNotIn(Set* set, int elem) {
	return !isIn(set, elem);
}

bool isDisjoint(Set* set1, Set* set2) {
	for (int i = 0; i < set1->m; i++) {
		if (set1->values[i].is_set && isIn(set2, set1->values[i].value)) 
			return false;
	}

	return true;
}

bool isSubSet(Set* set1, Set* set2) {
	if (set1->actual_size > set2->actual_size)
		return false;

	for (int i = 0; i < set1->m; i++) {
		if (set1->values[i].is_set && !isIn(set2, set1->values[i].value))
			return false;
	}

	return true;
}

bool isSuperSet(Set* set1, Set* set2) {
	return isSubSet(set2, set1);
}

int len(Set* set) {
	return set->actual_size;
}

void removeElem(Set* set, int elem) {
	int i = hash(elem, set->m);
	int prev = i;

	for (int i = hash(elem, set->m); i < set->m; i++) {
		if(set->values[i].is_set && elem == set->values[i].value) {
			set->actual_size--;
			set->values[i].is_set = false;
			return;
		}
	}

	for (i = 0; i < prev; i++) {
		if (set->values[i].is_set && elem == set->values[i].value) {
			set->actual_size--;
			set->values[i].is_set = false;
			return;
		}
	}
}

void print(Set *set) {
	int rel_index = set->actual_size-1;
	printf("{");
	for (int i = 0; i < set->m; i++) {
		if (set->values[i].is_set) {
			if (!rel_index) {
				printf("%i", set->values[i].value);
				break;
			}
			printf("%i, ", set->values[i].value);
			rel_index--;
		}
	}
	printf("}\n");
}

int pop(Set *set) {
	int rel_index = rand() % set->actual_size;
	int value = 0;
	for (int i = 0; i < set->m; i++) {
		if (set->values[i].is_set) {
			if (!rel_index) {
				set->actual_size--;
				set->values[i].is_set = false;
				value = set->values[i].value;
				break;
			}
			rel_index--;
		}
	}
	return value;
}

void clear(Set* set) {
	set->actual_size = 0;
	for (int i = 0; i < set->m; i++) {
		set->values[i].is_set = false;
	}
}

void copy(Set* set1, Set* set2) {
	set2->m = set1->m;
	set2->actual_size = set1->actual_size;
	free(set2->values);
	
	set2->values = (struct value*)malloc(sizeof(struct value) * set1->m);
	if (set2->values == NULL) {
		PRINT_ERROR("VETOR DE VALORES PARA COPIA NAO PDOE SER ALOCADO", copy);
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < set1->m; i++) {
		set2->values[i] = set1->values[i];
	}
}

Set* Union(Set *set1, Set *set2) {
	Set *new_set = create_empty(set1->actual_size+set2->actual_size);
	int i;
	for (i = 0; i < set1->m; i++) {
		if (set1->values[i].is_set)
			add(new_set, set1->values[i].value);
	}


	for (i = 0; i < set2->m; i++) {
		if (set2->values[i].is_set)
			add(new_set, set2->values[i].value);
	}

	return new_set;
}

Set* Intersection(Set* set1, Set* set2) {
	Set* inter = create_empty(set1->actual_size | set2->actual_size);
	for (int i = 0; i < set1->m; i++) {
		if (set1->values[i].is_set && isIn(set2, set1->values[i].value))
			add(inter, set1->values[i].value);
	}
	return inter;
}

Set* Difference(Set* set1, Set* set2) {
	Set *diff = create_empty(set1->actual_size);
	for (int i = 0; i < set1->m; i++) {
		if (set1->values[i].is_set && !isIn(set2, set1->values[i].value)) {
			add(diff, set1->values[i].value);
		}
	}

	return diff;
}

Set* Symmetric_difference(Set *set1, Set *set2) {
	Set* sym_diff = create_empty(set1->actual_size+set2->actual_size);
	int i;
	for (i = 0; i < set1->m; i++) {
		if (set1->values[i].is_set && !isIn(set2, set1->values[i].value)) {
			add(sym_diff, set1->values[i].value);
		}
	}

	for (i = 0; i < set2->m; i++) {
		if (set2->values[i].is_set && !isIn(set1, set2->values[i].value)) {
			add(sym_diff, set2->values[i].value);
		}
	}

	return sym_diff;
}

void free_set(Set** set) {
	free((*set)->values);
	free((*set));
	(*set) = NULL;
}