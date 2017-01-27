#ifndef __INTARRAY_H__
#define __INTARRAY_H__

#include "tools.h"

typedef struct _intarray* intarray;
typedef struct _intarray  S_intarray;

struct _intarray {
	int* data;
	int alloc; 	/* Taille actuellement allouée du champ data 		*/
	int len; 	/* Nombre d'éléments de data qu'on prend en compte 	*/
};

#define INTARRAY_DEFAULT_ALLOC	8

/* Prototypes des fonctions manipulant des intarray */
intarray intarray_create(int len);
intarray empty_intarray_create(int alloc);
intarray standard_empty_intarray_create(void);
void intarray_create_aux(intarray tab);
void intarray_destroy(intarray tab);
int intarray_get(intarray tab, int index);
/* Pour les tableaux de taille max fixe seulement */
void intarray_set(intarray tab, int index, int value);
/* Comme intarray_set, mais modifie la taille si nécessaire */
void ext_intarray_set(intarray tab, int index, int value);
void intarray_resize(intarray tab, int newalloc);
void intarray_add(intarray tab, int value);
/*
	Déplace un seul élément (très rapide).
	Attention : modifie l'ordre des éléments de tab.

	Si on souhaite que l'ordre reste inchangé,
	il faut appler la méthode intarray_delete
*/
void unsorted_intarray_delete(intarray tab, int index);
/*
	Déplace jusqu'à N éléments (dans le pire des cas),
	N étant la taille du tableau
*/
void intarray_delete(intarray tab, int index);

int intarray_length(intarray tab);
void intarray_print_positive_values(intarray tab);
int intarray_search(intarray tab, int n);
int intarray_nb_occurences(intarray tab, int n);
void intarray_debug(intarray tab);
void ext_intarray_debug(intarray tab);
/* retourne le résultat de la concaténation de t1 et t2 */
intarray intarray_concat(intarray t1, intarray t2);
/* retourne la plus petite valeur contenue dans tab */
int intarray_get_min(intarray tab);
/* retourne l'index de la plus petite valeur contenue dans tab */
int intarray_get_index_of_min(intarray tab);
/*
	retourne l'index de la plus petite valeur contenue dans tab
	entre la case numéro n et la fin du tableau
*/
int intarray_get_index_of_min_from(intarray tab, int n);
/* retourne la plus grande valeur contenue dans tab */
int intarray_get_max(intarray tab);
/* retourne l'index de la plus grande valeur contenue dans tab */
int intarray_get_index_of_max(intarray tab);
/*
	retourne l'index de la plus grande valeur contenue dans tab
	entre la case numéro n et la fin du tableau
*/
int intarray_get_index_of_max_from(intarray tab, int n);
/* Tri par sélection du minimum */
void intarray_sort1(intarray tab);

int intarray_sum(intarray tab);
float intarray_average(intarray tab);
float intarray_median(intarray tab);
intarray intarray_clone(intarray tab);

#endif