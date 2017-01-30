#include <stdlib.h>
#include <stdio.h>

#include "tools.h"
#include "charray2D.h"

/* j = numéro de ligne et i = numéro de colonne */
/* y = numéro de ligne et x = numéro de colonne */

/* fonctions privées */
char** charray_alloc(int w, int h)
{
	char** A = tools_malloc(sizeof(char*) * h);
	int i;
	for (i=0; i<h; i++)
		A[i] = tools_malloc(sizeof(char) * w);

	return A;
}
/*  */

charray charray_create(int w, int h, char bg)
{
	charray A = tools_malloc(sizeof(S_charray));
	A->w = w;
	A->h = h;
	A->bg = bg;
	A->data = charray_alloc(w, h);
	charray_fill(A, bg);

	return A;
}

void charray_destroy(charray* AA)
{
	charray A = *AA;

	int j;

	for (j=0; j<A->h; j++)
		tools_free(A->data[j], (sizeof(char) * A->w));

	tools_free(A->data,  (sizeof(char*) * A->h));

	tools_free(A, sizeof(S_charray));

	*AA = NULL;
}

void charray_debug(charray A)
{
	int j, i;

	for (j=0; j<A->h; j++)
	{
		for (i=0; i<A->w; i++)
			fprintf(stderr, "%c ", A->data[j][i]);

		fprintf(stderr, "\n");
	}
}

void charray_fill(charray A, char bg)
{
	int j, i; /* j = numéro de ligne et i = numéro de colonne */
	for (j=0; j<A->h; j++)
	{
		for (i=0; i<A->w; i++)
			A->data[j][i] = bg;
	}
}

char charray_get(charray A, int x, int y)
{
	if ((x < 0) || (x >= A->w) || (y < 0) || (y >= A->h))
	{
		fprintf(stderr, "charray_get : (%d ; %d) is out of bounds.\n", x, y);
		return A->bg;
	}

	return A->data[y][x];
}

void charray_set(charray A, int x, int y, char value)
{
	if ((x < 0) || (x >= A->w) || (y < 0) || (y >= A->h))
	{
		fprintf(stderr, "charray_get : (%d ; %d) is out of bounds.\n", x, y);
		return;
	}

	A->data[y][x] = value;
}