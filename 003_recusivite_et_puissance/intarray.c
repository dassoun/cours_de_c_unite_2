#include <stdio.h>
#include <stdlib.h>

#include "intarray.h"
#include "tools.h"

/* Corps des fonctions manipulant des intarray */
intarray intarray_create(int len)
{
	intarray tab = tools_malloc(sizeof(S_intarray));
	
	tab->len = len;
	tab->alloc = len;

	intarray_create_aux(tab);

	return tab;
}

intarray empty_intarray_create(int alloc)
{
	intarray tab = tools_malloc(sizeof(S_intarray));

	tab->len = 0;
	tab->alloc = alloc;
	
	intarray_create_aux(tab);

	return tab;
}

intarray standard_empty_intarray_create(void)
{
	return empty_intarray_create(INTARRAY_DEFAULT_ALLOC);
}

void intarray_create_aux(intarray tab)
{
	if (tab->alloc <= 0)
	{
		tab->alloc = 4;

		printf("intarray_create_aux : taille allouée <= 0.\n");
		printf("Nous allouons %d à la place.\n", tab->alloc);
	}
	
	tab->data = tools_malloc(tab->alloc * sizeof(int));

	int i;

	for(i=0; i<tab->alloc; i++)
		tab->data[i] = 0;
}

void intarray_destroy(intarray tab)
{
	tools_free(tab->data, sizeof(int) * tab->alloc);
	tools_free(tab, sizeof(S_intarray));
}

int intarray_get(intarray tab, int index)
{
	if ((index < 0) || (index >= tab->len))
	{
		printf("intarray_get : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);
		return -1;
	}

	return tab->data[index];
}

void intarray_set(intarray tab, int index, int value)
{
	if ((index < 0) || (index >= tab->len))
	{
		printf("intarray_set : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);

		return;
	}

	tab->data[index] = value;
}

int intarray_length(intarray tab)
{
	return tab->len;
}

void intarray_print_positive_values(intarray tab)
{
	int i;
	printf("[");
	for (i=0; i<tab->len-1; i++)
	{
		if (tab->data[i] >= 0)
			printf("%d ", tab->data[i]);
	}
	if (tab->data[tab->len-1] >= 0)
			printf("%d", tab->data[tab->len-1]);
	printf("]");
}


int intarray_search(intarray tab, int n)
{
	int trouve = 0;
	int i = 0;

	while (!trouve && i < tab->len)
	{
		if (tab->data[i] == n)
			trouve = 1;
		i++;
	}

	return trouve;
}

int intarray_nb_occurences(intarray tab, int n)
{	
	int i;
	int nb = 0;

	for (i=0; i<tab->len; i++)
	{
		if (tab->data[i] == n)
			nb++;
	}

	return nb;
}

void intarray_debug(intarray tab)
{
	int i;
	printf("[");
	for (i=0; i<tab->len-1; i++)
		printf("%d ", tab->data[i]);
	if (tab->len > 0)
		printf("%d", tab->data[tab->len-1]);
	printf("]");
}

void ext_intarray_debug(intarray tab)
{
	printf("Tab : alloc = %d; len = %d.\n", tab->alloc, tab->len);
	intarray_debug(tab);
}

intarray intarray_concat(intarray t1, intarray t2)
{
	int n = t1->len + t2->len;

	intarray tab = intarray_create(n);

	int i;
	for(i=0; i<t1->len; i++)
	{
		tab->data[i] = t1->data[i];
	}
	for(i=0; i<t2->len; i++)
	{
		tab->data[t1->len+i] = t2->data[i];
	}

	return tab;
}

int intarray_get_min(intarray tab)
{
	int index_min = intarray_get_index_of_min(tab);

	return tab->data[index_min];
}

int intarray_get_index_of_min(intarray tab)
{
	int indexMin = intarray_get_index_of_min_from(tab, 0);

	return indexMin;
}

int intarray_get_index_of_min_from(intarray tab, int n)
{
	if ((n < 0) || (n >= tab->len))
	{
		printf("intarray_get_index_of_min_from : L'index %d est invalide\n", n);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);

		return 0;
	}

	int i;
	int min = tab->data[n];
	int indexMin = n;

	for(i=n+1; i<tab->len; i++)
	{
		if (tab->data[i] < min)
		{
			min = tab->data[i];
			indexMin = i;
		}
	}

	return indexMin;
}

int intarray_get_max(intarray tab)
{
	int index_max = intarray_get_index_of_max(tab);

	return tab->data[index_max];
}

int intarray_get_index_of_max(intarray tab)
{
	int indexMax = intarray_get_index_of_max_from(tab, 0);

	return indexMax;
}

int intarray_get_index_of_max_from(intarray tab, int n)
{
	if ((n < 0) || (n >= tab->len))
	{
		printf("intarray_get_index_of_max_from : L'index %d est invalide\n", n);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);

		return 0;
	}

	int i;
	int max = tab->data[n];
	int indexMax = n;

	for(i=n+1; i<tab->len; i++)
	{
		if (tab->data[i] > max)
		{
			max = tab->data[i];
			indexMax = i;
		}
	}

	return indexMax;
}

void intarray_sort1(intarray tab)
{
	int i;
	int indiceMin;
	int tmp;

	for (i=0; i<tab->len-1; i++)
	{
		indiceMin = intarray_get_index_of_min_from(tab, i);

		int_swap(tab->data + i, tab->data + indiceMin);
	}
}

int intarray_sum(intarray tab)
{
	int i;
	int res = 0;

	if (tab->len <= 0)
		printf("intarray_sum : tableau de longueur négative ou nulle.\n");
	
	for (i=0; i<tab->len; i++)
	{
		res += tab->data[i];
	}

	return res;
}

float intarray_average(intarray tab)
{
	float res = 0.0;

	if (tab->len <= 0)
	{
		printf("intarray_average : tableau de longueur négative ou nulle.\n");
		return -1.0;
	}
	
	if (tab->len > 0)
	{
		res = (float) intarray_sum(tab) / tab->len;
	}
	
	return res;
}

float intarray_median(intarray tab)
{
	if (tab->len <= 0)
	{
		printf("intarray_average : tableau de longueur négative ou nulle.\n");
		return -1.0;
	}
	
	float res; 

	intarray copy = intarray_clone(tab);

	intarray_sort1(copy);

	if (copy->len % 2 > 0)
	{	
		res = copy->data[((copy->len - 1) / 2)];
	} else {
		int indiceInf = (copy->len - 1) / 2;
		int indiceSup = (copy->len / 2);

		res = (float) (copy->data[indiceInf] + copy->data[indiceSup]) / 2;
	}

	intarray_destroy(copy);

	return res;
}

intarray intarray_clone(intarray tab)
{
	int i;

	intarray copy = intarray_create(tab->len);

	for (i=0; i<tab->len; i++)
	{
		intarray_set(copy, i, intarray_get(tab, i));
	}

	return copy;
}

void unsorted_intarray_delete(intarray tab, int index)
{
	if ((index < 0) || (index >= tab->len))
	{
		printf("unsorted_intarray_delete : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);

		return;
	}

	tab->data[index] = tab->data[tab->len - 1];

	tab->len--;
}

void intarray_delete(intarray tab, int index)
{
	if ((index < 0) || (index >= tab->len))
	{
		printf("intarray_delete : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);

		return;
	}

	int i;

	for (i=index+1; i<tab->len; i++)
		tab->data[i-1] = tab->data[i];

	tab->len--;
}

/*
	première version : ne prend pas encore en compte
	les situations où il faut réallouer data
*/
void intarray_add(intarray tab, int value)
{
	ext_intarray_set(tab, tab->len, value);
}

void ext_intarray_set(intarray tab, int index, int value)
{
	if (index < 0)
	{
		printf("ext_intarray_set : L'index %d est invalide\n", index);
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
			intarray_resize(tab, (index * 2) + 1);

		int i;

		for(i=tab->len; i<index; i++)
			tab->data[i] = 0;
		tab->data[index] = value;

		tab->len = index + 1;
	}
}

void intarray_resize(intarray tab, int newalloc)
{
	int* newdata = tools_malloc(sizeof(int) * newalloc);

	int i;
	for (i=0; i<tab->len; i++)
		newdata[i] = tab->data[i];

	tools_free(tab->data, sizeof(int) * tab->alloc);

	tab->data = newdata;
	tab->alloc = newalloc;
}