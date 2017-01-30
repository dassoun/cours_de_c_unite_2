#include <stdlib.h>
#include <stdio.h>

#include "tools.h"
#include "charray2D.h"

/* j = numéro de ligne et i = numéro de colonne */
/* y = numéro de ligne et x = numéro de colonne */

/* fonctions privées */
void charray_alloc(charray A, int w, int h)
{
	A->data = tools_malloc(sizeof(char*) * w * h);

	int j;

	A->pixel = tools_malloc(sizeof(char*) * h);

	for (j=0; j<h; j++)
		A->pixel[j] = A->data + j * A->w * sizeof(char);
}
/*  */

charray charray_create(int w, int h, char bg)
{
	charray A = tools_malloc(sizeof(S_charray));
	A->w = w;
	A->h = h;
	A->bg = bg;
	charray_alloc(A, w, h);

	charray_fill(A, bg);

	return A;
}

void charray_destroy(charray* AA)
{
	charray A = *AA;

	int j;

	tools_free(A->pixel, (sizeof(char*) * A->h));

	tools_free(A->data,  (sizeof(char*) * A->w * A->h));

	tools_free(A, sizeof(S_charray));

	*AA = NULL;
}

void charray_debug(charray A)
{
	char* ptr = A->data;
	int j, i;

	for (j=0; j<A->h; j++)
	{
		for (i=0; i<A->w; i++)
		{
			fprintf(stderr, "%c ", *ptr);
			ptr++;
		}

		fprintf(stderr, "\n");
	}
}

void charray_fill(charray A, char bg)
{
	char* ptr = A->data;
	int j, i; /* j = numéro de ligne et i = numéro de colonne */
	for (j=0; j<A->h; j++)
	{
		for (i=0; i<A->w; i++)
		{
			*ptr = bg;
			ptr++;
		}
	}
}

char charray_get(charray A, int x, int y)
{
	if ((x < 0) || (x >= A->w) || (y < 0) || (y >= A->h))
	{
		fprintf(stderr, "charray_get : (%d ; %d) is out of bounds.\n", x, y);
		return A->bg;
	}

	return A->pixel[y][x];
	/*return A->data[(y * A->w) + x];*/
}

void charray_set(charray A, int x, int y, char value)
{
	if ((x < 0) || (x >= A->w) || (y < 0) || (y >= A->h))
	{
		fprintf(stderr, "charray_get : (%d ; %d) is out of bounds.\n", x, y);
		return;
	}

	A->pixel[y][x] = value;
	/*A->data[(y * A->w)] = value;*/
}