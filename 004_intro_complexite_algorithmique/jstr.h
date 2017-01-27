#ifndef __JSTR_H__
#define __JSTR_H__

#include "tools.h"
#include "intarray.h"

typedef struct _jstr* jstr;
typedef struct _jstr  S_jstr;

struct _jstr {
	char* data;
	int alloc; 	/* Taille actuellement allouée du champ data 		*/
	int len; 	/* Nombre d'éléments de data qu'on prend en compte 	*/
};

#define jstr_DEFAULT_ALLOC	8

/* Prototypes des fonctions manipulant des jstr */
jstr jstr_create(int len);
jstr empty_jstr_create(int alloc);
jstr standard_empty_jstr_create(void);
void jstr_create_aux(jstr tab);
void jstr_destroy(jstr tab);
void regular_jstr_destroy(jstr* tab);

jstr regstr_to_jstr(char* str);	/* Plus tard : regstr au lieu de char* */
char* jstr_to_regstr(jstr tab); /* et aussi dans le .c */

char jstr_get(jstr tab, int index);
/* Pour les tableaux de taille max fixe seulement */
void jstr_set(jstr tab, int index, char value);
/* Comme jstr_set, mais modifie la taille si nécessaire */
void ext_jstr_set(jstr tab, int index, char value);
void jstr_resize(jstr tab, int newalloc);
void jstr_add(jstr tab, char value);
/*
	Déplace un seul élément (très rapide).
	Attention : modifie l'ordre des éléments de tab.

	Si on souhaite que l'ordre reste inchangé,
	il faut appler la méthode jstr_delete
*/
void unsorted_jstr_delete(jstr tab, int index);
/*
	Déplace jusqu'à N éléments (dans le pire des cas),
	N étant la taille du tableau
*/
void jstr_delete(jstr tab, int index);

int jstr_length(jstr tab);
void jstr_print_positive_values(jstr tab);
int jstr_search(jstr tab, char n);
int jstr_nb_occurences(jstr tab, char n);
void jstr_debug(jstr tab);
void ext_jstr_debug(jstr tab);
/* retourne le résultat de la concaténation de t1 et t2 */
jstr jstr_concat(jstr t1, jstr t2);
/* 
	ajoute à la fin de T1 des copies des caractères de T2, 
	en respectant l'oredre de ces derniers.
	Le contenu de T2 n'est pas modifié 
*/
void D_jstr_concat(jstr t1, jstr t2);

/* retourne la plus petite valeur contenue dans tab */
char jstr_get_min(jstr tab);
/* retourne l'index de la plus petite valeur contenue dans tab */
int jstr_get_index_of_min(jstr tab);
/*
	retourne l'index de la plus petite valeur contenue dans tab
	entre la case numéro n et la fin du tableau
*/
int jstr_get_index_of_min_from(jstr tab, int n);
/* retourne la plus grande valeur contenue dans tab */
char jstr_get_max(jstr tab);
/* retourne l'index de la plus grande valeur contenue dans tab */
int jstr_get_index_of_max(jstr tab);
/*
	retourne l'index de la plus grande valeur contenue dans tab
	entre la case numéro n et la fin du tableau
*/
int jstr_get_index_of_max_from(jstr tab, int n);
/* Tri par sélection du minimum */
void jstr_sort1(jstr tab);

int jstr_sum(jstr tab);
float jstr_average(jstr tab);
float jstr_median(jstr tab);
jstr jstr_clone(jstr tab);

int jstr_equal_substr(jstr j1, int s1, int e1, jstr j2, int s2);
int jstr_equal(jstr j1, jstr j2);
intarray jstr_find_substr_indices(jstr j, jstr sub);
intarray jstr_find_proper_substr_indices(jstr j, jstr sub);
int jstr_compare(jstr j1, jstr j2);

void jstr_swap(jstr j1, jstr j2);

#endif