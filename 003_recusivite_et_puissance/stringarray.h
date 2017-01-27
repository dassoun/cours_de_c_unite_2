#ifndef __STRINGARRAY_H__
#define __STRINGARRAY_H__

#include "tools.h"
#include "jstr.h"

typedef struct _stringarray* stringarray;
typedef struct _stringarray  S_stringarray;

struct _stringarray {
	jstr* data;
	int alloc; 	/* Taille actuellement allouée du champ data 		*/
	int len; 	/* Nombre d'éléments de data qu'on prend en compte 	*/
};

#define stringarray_DEFAULT_ALLOC	8

/* Prototypes des fonctions manipulant des stringarray */
stringarray stringarray_create(int len);
stringarray empty_stringarray_create(int alloc);
stringarray standard_empty_stringarray_create(void);
void stringarray_create_aux(stringarray tab);
/* Désaloue la struct stringarray et le tableau de jstr */
void stringarray_destroy(stringarray tab);
/* Désaloue les jstr de tab en plus de la struct et du tableau de jstr */
void stringarray_destroy_using_jstr_destroy(stringarray tab);

jstr stringarray_get(stringarray tab, int index);
/* Pour les tableaux de taille max fixe seulement */
void stringarray_set(stringarray tab, int index, jstr value);
/* Comme stringarray_set, mais modifie la taille si nécessaire */
void ext_stringarray_set(stringarray tab, int index, jstr value);
void stringarray_resize(stringarray tab, int newalloc);
void stringarray_add(stringarray tab, jstr value);
/*
	Déplace un seul élément (très rapide).
	Attention : modifie l'ordre des éléments de tab.

	Si on souhaite que l'ordre reste inchangé,
	il faut appler la méthode stringarray_delete
*/
void unsorted_stringarray_delete(stringarray tab, int index);
/*
	Déplace jusqu'à N éléments (dans le pire des cas),
	N étant la taille du tableau
*/
void stringarray_delete(stringarray tab, int index);

int stringarray_length(stringarray tab);
/* 
	Retourne l'index de la première occurence dans tab
	d'une jstr qui est equal à value
*/
int stringarray_search(stringarray tab, jstr value);
int stringarray_nb_occurences(stringarray tab, jstr value);

void stringarray_debug_with_delimiter(stringarray tab, char* delimiter);
void stringarray_debug(stringarray tab);
void ext_stringarray_debug(stringarray tab);

stringarray stringarray_concat_using_jstr_clone(stringarray t1, stringarray t2);
stringarray stringarray_concat_aux(stringarray t1, stringarray t2, int clone);
/* 
	retourne le résultat de la concaténation de t1 et t2 
	les jstr de t1 et t2 sont clonées
*/
stringarray stringarray_concat(stringarray t1, stringarray t2);
/* 
	ajoute à la fin de t1 des clones des jstr de t2, 
	en respectant l'oredre de ces derniers.
	Le contenu de T2 n'est pas modifié 
*/
void D_stringarray_concat(stringarray t1, stringarray t2);

/* retourne la plus petite valeur contenue dans tab */
jstr stringarray_get_min(stringarray tab);
/* retourne l'index de la plus petite valeur contenue dans tab */
int stringarray_get_index_of_min(stringarray tab);
/*
	retourne l'index de la plus petite valeur contenue dans tab
	entre la case numéro n et la fin du tableau
*/
int stringarray_get_index_of_min_from(stringarray tab, int n);
/* retourne la plus grande valeur contenue dans tab */
jstr stringarray_get_max(stringarray tab);
/* retourne l'index de la plus grande valeur contenue dans tab */
int stringarray_get_index_of_max(stringarray tab);
/*
	retourne l'index de la plus grande valeur contenue dans tab
	entre la case numéro n et la fin du tableau
*/
int stringarray_get_index_of_max_from(stringarray tab, int n);
/* Tri par sélection du minimum */
void stringarray_sort1(stringarray tab);

stringarray stringarray_clone_aux(stringarray tab, int clone);
stringarray stringarray_clone(stringarray tab);
stringarray stringarray_clone_using_jstr_clone(stringarray tab);

int stringarray_equal(stringarray j1, stringarray j2);

#endif