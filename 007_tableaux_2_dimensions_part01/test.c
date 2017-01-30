/*
 * Cours de Jacques-Olivier Lapeyre
 * Unité 2
 * Cours 7
 * Tableaux à 2 dimensions - Partie 1
 * https://www.youtube.com/watch?v=QTkRyNwfuvI
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include "tools.h"
#include "intarray.h"
#include "charray2D.h"

int main(int argc, char *argv[]) 
{	
    tools_memory_init();

   	charray toto = charray_create(20, 10, '.');

   	charray_set(toto, 15, 10, '*');
   	charray_set(toto, 15, 4, '*');

	fprintf(stderr, "\n%c\n", charray_get(toto, 15, 10));
   	fprintf(stderr, "\n%c\n", charray_get(toto, 15, 4));  	

   	{
   		int x, y;

   		for (y=4; y<=8; y++)
   		{
   			for (x=2; x<=14; x++)
   				charray_set(toto, x, y, '#');
   		}
   	}

   	charray_debug(toto);

   	charray_destroy(&toto);

    tools_memory_check_at_end_of_app();
    
    return (EXIT_SUCCESS);
}