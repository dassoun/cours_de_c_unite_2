#ifndef __CHARRAY2D_H__
#define __CHARRAY2D_H__

#include <stdlib.h>
#include <stdio.h>

#include "tools.h"

/* j = numéro de ligne et i = numéro de colonne */
/* y = numéro de ligne et x = numéro de colonne */

/*
	méthode 1 : char** 			; "adressage" lent		; plus simple
	méthode 2 : char*			; "adressage" rapide	; plus compliqué à utiliser
	méthode 3 : char* / char**	; "adressage" rapide	; plus simple à utiliser
*/

typedef struct _charray S_charray;
typedef struct _charray* charray;

struct _charray {
	int w; /* width */
	int h; /* height */
	char bg;
	/* char* data; */
	char** data;
};

charray charray_create(int w, int h, char bg); /* bg = background */
void charray_destroy(charray* A);

void charray_debug(charray A);

void charray_fill(charray A, char bg);

char charray_get(charray A, int x, int y);
void charray_set(charray A, int x, int y, char value);

#endif