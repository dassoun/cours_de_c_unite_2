#include <stdio.h>
#include <stdlib.h>

#include "jstr.h"
#include "tools.h"
#include "stringarray.h"

/* Corps des fonctions manipulant des stringarray */
stringarray stringarray_create(int len)
{
	stringarray tab = tools_malloc(sizeof(S_stringarray));
	
	tab->len = len;
	tab->alloc = len;

	stringarray_create_aux(tab);

	return tab;
}

stringarray empty_stringarray_create(int alloc)
{
	stringarray tab = tools_malloc(sizeof(S_stringarray));

	tab->len = 0;
	tab->alloc = alloc;
	
	stringarray_create_aux(tab);

	return tab;
}

stringarray standard_empty_stringarray_create(void)
{
	return empty_stringarray_create(stringarray_DEFAULT_ALLOC);
}

void stringarray_create_aux(stringarray tab)
{
	if (tab->alloc <= 0)
	{
		tab->alloc = 4;

		printf("stringarray_create_aux : taille allouée <= 0.\n");
		printf("Nous allouons %d à la place.\n", tab->alloc);
	}
	
	tab->data = tools_malloc(tab->alloc * sizeof(jstr));

	int i;

	for(i=0; i<tab->alloc; i++)
		tab->data[i] = NULL;
}

void stringarray_destroy(stringarray tab)
{
	tools_free(tab->data, sizeof(jstr) * tab->alloc);
	tools_free(tab, sizeof(S_stringarray));
}

void stringarray_destroy_using_jstr_destroy(stringarray tab)
{
	int i;

	for (i=0; i<tab->len; i++)
		regular_jstr_destroy(&(tab->data[i]));

	stringarray_destroy(tab);
}

jstr stringarray_get(stringarray tab, int index)
{
	if ((index < 0) || (index >= tab->len))
	{
		printf("stringarray_get : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);

		return NULL;
	}

	return tab->data[index];
}

void stringarray_set(stringarray tab, int index, jstr value)
{
	if ((index < 0) || (index >= tab->len))
	{
		printf("stringarray_set : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);

		return;
	}

	regular_jstr_destroy(&(tab->data[index]));

	tab->data[index] = value;
}

int stringarray_length(stringarray tab)
{
	return tab->len;
}

int stringarray_search(stringarray tab, jstr value)
{
	int trouve = 0;
	int i = 0;

	while (!trouve && i < tab->len)
	{
		if (jstr_equal(tab->data[i], value))
			trouve = 1;
		i++;
	}

	return trouve;
}

int stringarray_nb_occurences(stringarray tab, jstr value)
{	
	int i;
	int nb = 0;

	for (i=0; i<tab->len; i++)
	{
		if (jstr_equal(tab->data[i], value))
			nb++;
	}

	return nb;
}

void stringarray_debug_with_delimiter(stringarray tab, char* delimiter)
{
	int i;
	for (i=0; i<=tab->len-1; i++)
	{
		jstr_debug(tab->data[i]);
		printf(delimiter);
	}
}

void stringarray_debug(stringarray tab)
{
	stringarray_debug_with_delimiter(tab, "\n");
}

void ext_stringarray_debug(stringarray tab)
{
	printf("Tab : alloc = %d; len = %d.\n", tab->alloc, tab->len);
	stringarray_debug(tab);
}

stringarray stringarray_concat(stringarray t1, stringarray t2)
{
	return stringarray_concat_aux(t1, t2, 0);
}

stringarray stringarray_concat_using_jstr_clone(stringarray t1, stringarray t2)
{
	return stringarray_concat_aux(t1, t2, 1);
}

stringarray stringarray_concat_aux(stringarray t1, stringarray t2, int clone)
{
	int n = t1->len + t2->len;

	stringarray tab = stringarray_create(n);

	int i;
	for(i=0; i<t1->len; i++)
	{
		if (clone)
			tab->data[i] = jstr_clone(t1->data[i]);
		else 
			tab->data[i] = t1->data[i];
	}
	for(i=0; i<t2->len; i++)
	{
		if (clone)
			tab->data[t1->len+i] = jstr_clone(t2->data[i]);
		else
			tab->data[t1->len+i] = t2->data[i];
	}

	return tab;
}
/*
	Ajoute à la fin de t1 des clones des jstr de t2,
	en respectant l'ordre de ces derniers.
	Le contenu de t2 n'est pas modifié.
*/
void D_stringarray_concat(stringarray t1, stringarray t2)
{
	int i;
	for (i=0; i<t2->len; i++)
		stringarray_add(t1, jstr_clone(t2->data[i]));
}

jstr stringarray_get_min(stringarray tab)
{
	int index_min = stringarray_get_index_of_min(tab);

	return tab->data[index_min];
}

int stringarray_get_index_of_min(stringarray tab)
{
	int indexMin = stringarray_get_index_of_min_from(tab, 0);

	return indexMin;
}

int stringarray_get_index_of_min_from(stringarray tab, int n)
{
	if ((n < 0) || (n >= tab->len))
	{
		printf("stringarray_get_index_of_min_from : L'index %d est invalide\n", n);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);

		return 0;
	}

	int i;
	jstr min = tab->data[n];
	int indexMin = n;

	for(i=n+1; i<tab->len; i++)
	{
		if (jstr_compare(tab->data[i], min) == -1)
		{
			min = tab->data[i];
			indexMin = i;
		}
	}

	return indexMin;
}

jstr stringarray_get_max(stringarray tab)
{
	int index_max = stringarray_get_index_of_max(tab);

	return tab->data[index_max];
}

int stringarray_get_index_of_max(stringarray tab)
{
	int indexMax = stringarray_get_index_of_max_from(tab, 0);

	return indexMax;
}

int stringarray_get_index_of_max_from(stringarray tab, int n)
{
	if ((n < 0) || (n >= tab->len))
	{
		printf("stringarray_get_index_of_max_from : L'index %d est invalide\n", n);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);

		return 0;
	}

	int i;
	jstr max = tab->data[n];
	int indexMax = n;

	for(i=n+1; i<tab->len; i++)
	{
		if (jstr_compare(tab->data[i], max) == 1)
		{
			max = tab->data[i];
			indexMax = i;
		}
	}

	return indexMax;
}

void stringarray_sort1(stringarray tab)
{
	int i;
	int indiceMin;
	int tmp;

	for (i=0; i<tab->len-1; i++)
	{
		indiceMin = stringarray_get_index_of_min_from(tab, i);

		jstr tmp = tab->data[i];
		tab->data[i] = tab->data[indiceMin];
		tab->data[indiceMin] = tmp;
	}
}

stringarray stringarray_clone_aux(stringarray tab, int clone)
{
	int i;

	stringarray copy = stringarray_create(tab->len);

	for (i=0; i<tab->len; i++)
	{
		if (clone)
			stringarray_set(copy, i, jstr_clone(tab->data[i]));
		else
			stringarray_set(copy, i, stringarray_get(tab, i));
	}

	return copy;
}

stringarray stringarray_clone(stringarray tab)
{
	return stringarray_clone_aux(tab, 0);
}

stringarray stringarray_clone_using_jstr_clone(stringarray tab)
{
	return stringarray_clone_aux(tab, 1);
}

void unsorted_stringarray_delete(stringarray tab, int index)
{
	if ((index < 0) || (index >= tab->len))
	{
		printf("unsorted_stringarray_delete : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);

		return;
	}

	regular_jstr_destroy(&(tab->data[index]));

	tab->data[index] = tab->data[tab->len - 1];

	tab->len--;
}

void stringarray_delete(stringarray tab, int index)
{
	int i;

	if ((index < 0) || (index >= tab->len))
	{
		printf("stringarray_delete : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);

		return;
	}

	regular_jstr_destroy(&(tab->data[index]));

	for (i=index+1; i<tab->len; i++)
		tab->data[i-1] = tab->data[i];

	tab->len--;
}

/*
	première version : ne prend pas encore en compte
	les situations où il faut réallouer data
*/
void stringarray_add(stringarray tab, jstr value)
{
	ext_stringarray_set(tab, tab->len, value);
}

void ext_stringarray_set(stringarray tab, int index, jstr value)
{
	if (index < 0)
	{
		printf("ext_stringarray_set : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont supérieures à 0\n");

		return;
	}

	if (index <= (tab->len - 1))
	{
		tab->data[index] = value;
	}
	else
	{
		if (index >= tab->alloc)
			stringarray_resize(tab, (index * 2) + 1);

		int i;

		for(i=tab->len; i<index; i++)
			tab->data[i] = empty_jstr_create(1);

		if (tab->data[index] != NULL)
			regular_jstr_destroy(&(tab->data[index]));

		tab->data[index] = value;

		tab->len = index + 1;
	}
}

void stringarray_resize(stringarray tab, int newalloc)
{
	jstr* newdata = tools_malloc(sizeof(jstr) * newalloc);

	int i;
	for (i=0; i<tab->len; i++)
		newdata[i] = tab->data[i];

	for (i=tab->len; i < newalloc; i++)
		newdata[i] = NULL;

	tools_free(tab->data, sizeof(jstr) * tab->alloc);

	tab->data = newdata;
	tab->alloc = newalloc;
}

int stringarray_equal(stringarray j1, stringarray j2)
{
	if (j1->len != j2->len)
		return 0;

	int i;

	for (i=0; i<j1->len; i++)
	{
		if (!(jstr_equal(j1->data[i], j2->data[i])))
			return 0;
	}

	return 1;
}
