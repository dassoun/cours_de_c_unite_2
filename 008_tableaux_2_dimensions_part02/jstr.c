#include <stdio.h>
#include <stdlib.h>

#include "jstr.h"
#include "tools.h"
#include "intarray.h"

/* Corps des fonctions manipulant des jstr */
jstr jstr_create(int len)
{
	jstr tab = tools_malloc(sizeof(S_jstr));
	
	tab->len = len;
	tab->alloc = len;

	jstr_create_aux(tab);

	return tab;
}

jstr empty_jstr_create(int alloc)
{
	jstr tab = tools_malloc(sizeof(S_jstr));

	tab->len = 0;
	tab->alloc = alloc;
	
	jstr_create_aux(tab);

	return tab;
}

jstr standard_empty_jstr_create(void)
{
	return empty_jstr_create(jstr_DEFAULT_ALLOC);
}

void jstr_create_aux(jstr tab)
{
	if (tab->alloc <= 0)
	{
		tab->alloc = 4;

		printf("jstr_create_aux : taille allouée <= 0.\n");
		printf("Nous allouons %d à la place.\n", tab->alloc);
	}
	
	tab->data = tools_malloc(tab->alloc * sizeof(char));

	int i;

	for(i=0; i<tab->alloc; i++)
		tab->data[i] = 0;
}

void jstr_destroy(jstr tab)
{
	tools_free(tab->data, sizeof(char) * tab->alloc);
	tools_free(tab, sizeof(S_jstr));
}

void regular_jstr_destroy(jstr* ttab)
{
	if (ttab == NULL)
	{	
		printf("regular_jstr_destroy : ttab est un pointeur null.\n");
		return;
	}

	jstr tab = *ttab;
	if (tab == NULL)
		return;
	jstr_destroy(tab);
	*ttab = NULL;
}

char jstr_get(jstr tab, int index)
{
	if ((index < 0) || (index >= tab->len))
	{
		printf("jstr_get : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);
		return -1;
	}

	return tab->data[index];
}

void jstr_set(jstr tab, int index, char value)
{
	if ((index < 0) || (index >= tab->len))
	{
		printf("jstr_set : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);

		return;
	}

	tab->data[index] = value;
}

int jstr_length(jstr tab)
{
	return tab->len;
}

void jstr_print_positive_values(jstr tab)
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


int jstr_search(jstr tab, char n)
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

int jstr_nb_occurences(jstr tab, char n)
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

void jstr_debug(jstr tab)
{
	int i;
	for (i=0; i<=tab->len-1; i++)
		printf("%c", tab->data[i]);
}

void ext_jstr_debug(jstr tab)
{
	printf("Tab : alloc = %d; len = %d.\n", tab->alloc, tab->len);
	jstr_debug(tab);
}

jstr jstr_concat(jstr t1, jstr t2)
{
	int n = t1->len + t2->len;

	jstr tab = jstr_create(n);

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

void D_jstr_concat(jstr t1, jstr t2)
{
	int i;
	for (i=0; i<t2->len; i++)
		jstr_add(t1, t2->data[i]);
}

char jstr_get_min(jstr tab)
{
	int index_min = jstr_get_index_of_min(tab);

	return tab->data[index_min];
}

int jstr_get_index_of_min(jstr tab)
{
	int indexMin = jstr_get_index_of_min_from(tab, 0);

	return indexMin;
}

int jstr_get_index_of_min_from(jstr tab, int n)
{
	if ((n < 0) || (n >= tab->len))
	{
		printf("jstr_get_index_of_min_from : L'index %d est invalide\n", n);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);

		return 0;
	}

	int i;
	char min = tab->data[n];
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

char jstr_get_max(jstr tab)
{
	int index_max = jstr_get_index_of_max(tab);

	return tab->data[index_max];
}

int jstr_get_index_of_max(jstr tab)
{
	int indexMax = jstr_get_index_of_max_from(tab, 0);

	return indexMax;
}

int jstr_get_index_of_max_from(jstr tab, int n)
{
	if ((n < 0) || (n >= tab->len))
	{
		printf("jstr_get_index_of_max_from : L'index %d est invalide\n", n);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);

		return 0;
	}

	int i;
	char max = tab->data[n];
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

void jstr_sort1(jstr tab)
{
	int i;
	int indiceMin;
	int tmp;

	for (i=0; i<tab->len-1; i++)
	{
		indiceMin = jstr_get_index_of_min_from(tab, i);

		char_swap(tab->data + i, tab->data + indiceMin);
	}
}

int jstr_sum(jstr tab)
{
	int i;
	int res = 0;

	if (tab->len <= 0)
		printf("jstr_sum : tableau de longueur négative ou nulle.\n");
	
	for (i=0; i<tab->len; i++)
	{
		res += ((int) tab->data[i]);
	}

	return res;
}

float jstr_average(jstr tab)
{
	float res = 0.0;

	if (tab->len <= 0)
	{
		printf("jstr_average : tableau de longueur négative ou nulle.\n");
		return -1.0;
	}
	
	if (tab->len > 0)
	{
		res = (float) jstr_sum(tab) / tab->len;
	}
	
	return res;
}

float jstr_median(jstr tab)
{
	if (tab->len <= 0)
	{
		printf("jstr_average : tableau de longueur négative ou nulle.\n");
		return -1.0;
	}
	
	float res; 

	jstr copy = jstr_clone(tab);

	jstr_sort1(copy);

	if (copy->len % 2 > 0)
	{	
		res = copy->data[((copy->len - 1) / 2)];
	} else {
		int indiceInf = (int) (copy->len - 1) / 2;
		int indiceSup = (int) (copy->len / 2);

		res = (float) (copy->data[indiceInf] + copy->data[indiceSup]) / 2;
	}

	jstr_destroy(copy);

	return res;
}

jstr jstr_clone(jstr tab)
{
	int i;

	jstr copy = jstr_create(tab->len);

	for (i=0; i<tab->len; i++)
	{
		jstr_set(copy, i, jstr_get(tab, i));
	}

	return copy;
}

void unsorted_jstr_delete(jstr tab, int index)
{
	if ((index < 0) || (index >= tab->len))
	{
		printf("unsorted_jstr_delete : L'index %d est invalide\n", index);
		printf("Les valeurs valides sont entre 0 et %d\n", tab->len-1);

		return;
	}

	tab->data[index] = tab->data[tab->len - 1];

	tab->len--;
}

void jstr_delete(jstr tab, int index)
{
	if ((index < 0) || (index >= tab->len))
	{
		printf("jstr_delete : L'index %d est invalide\n", index);
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
void jstr_add(jstr tab, char value)
{
	ext_jstr_set(tab, tab->len, value);
}

void ext_jstr_set(jstr tab, int index, char value)
{
	if (index < 0)
	{
		printf("ext_jstr_set : L'index %d est invalide\n", index);
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
			jstr_resize(tab, (index * 2) + 1);

		int i;

		for(i=tab->len; i<index; i++)
			tab->data[i] = 0;
		tab->data[index] = value;

		tab->len = index + 1;
	}
}

void jstr_resize(jstr tab, int newalloc)
{
	char* newdata = tools_malloc(sizeof(char) * newalloc);

	int i;
	for (i=0; i<tab->len; i++)
		newdata[i] = tab->data[i];

	tools_free(tab->data, sizeof(char) * tab->alloc);

	tab->data = newdata;
	tab->alloc = newalloc;
}

jstr regstr_to_jstr(regstr str)
{
	int i;
	
	jstr tab = standard_empty_jstr_create();
	for (i=0; str[i]!='\0'; i++)
		jstr_add(tab, str[i]);

	return tab;
}

char* jstr_to_regstr(jstr tab)
{
	char* str = tools_malloc(sizeof(char) * (tab->len + 1));
	int i;

	for (i=0; i<tab->len; i++)
		str[i] = tab->data[i];
	str[tab->len] = '\0';

	return str;
}

int jstr_equal_substr(jstr j1, int s1, int e1, jstr j2, int s2)
{
	int len = e1 - s1 + 1;
	int e2 = s2 + len - 1;

	if (s1 > e1)
	{
		int_swap(&s1, &e1);
		printf("jstr_equal_substr : s1 était supérieur à e1. Les deux ont été échangés.\n");
	}

	if ((s1 < 0) || (s2 < 0) || (s1 >= j1->len) || (e1 >= j1->len) || (s2 >= j2->len))
	{
		printf("jstr_equal_substr : out of bounds. s1 = %d; e1 = %d;\n", s1, e2);
		printf("s2 = %d; j1->len = %d; j2->len = %d\n", s2, j1->len, j2->len);

		return 0;
	}

	if (e2 >= j2->len)
		return 0;

	int i;

	for (i=0; i<len; i++)
	{
		if (j1->data[i + s1] != j2->data[i + s2])
			return 0;
	}

	return 1;
}

int jstr_equal(jstr j1, jstr j2)
{
	if (j1 == j2)
		return 1;
	else if (j1->len != j2->len)
		return 0;

	return jstr_equal_substr(j1, 0, (j1->len - 1), j2, 0);
}

intarray jstr_find_substr_indices(jstr j, jstr sub)
{
	intarray tab = standard_empty_intarray_create();
	int i;

	for (i=0; i<=(j->len - sub->len); i++)
	{
		if (jstr_equal_substr(j, i, ((i + sub->len) - 1), sub, 0))
			intarray_add(tab, i);
	}

	return tab;
}

intarray jstr_find_proper_substr_indices(jstr j, jstr sub)
{
	intarray tab = standard_empty_intarray_create();
	int i = 0;

	while (i <= (j->len - sub->len))
	{
		if (jstr_equal_substr(j, i, ((i + sub->len) - 1), sub, 0))
		{
			intarray_add(tab, i);
			i += sub->len;
		}
		else
			i++;
	}

	return tab;
}

/*
	Retourne 1 si j1 > j2
	Retourne 0 si j1 = j2
	Retourne -1 si j1 < j2
*/
int jstr_compare(jstr j1, jstr j2)
{
	int i = 0;

	while ((j1->data[i] == j2->data[i]) && (i<(j1->len)) && (i<(j2->len)))
		i++;

	if ((i == (j1->len)) && (i == (j2->len)))
		return 0;

	if ((i == (j1->len)) || (j1->data[i] < j2->data[i]))
		return -1;

	if ((i == (j2->len)) || (j1->data[i] > j2->data[i]))
		return 1;
}

void jstr_swap(jstr j1, jstr j2)
{
	jstr tmp = j1;
	j1 = j2;
	j2 = tmp;
}