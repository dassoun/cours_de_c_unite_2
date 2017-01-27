/*
 * Cours de Jacques-Olivier Lapeyre
 * Unité 2
 * Cours 6
 * Tri et complexité quadratique
 * https://www.youtube.com/watch?v=VPs9hNGeC0Q
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include "tools.h"
#include "intarray.h"

int main(int argc, char *argv[]) 
{	
    tools_memory_init();

    intarray A = intarray_create_random(1000, 0, 1000000);

    intarray_sort1(A);
    //intarray_debug(A);

    intarray_destroy(A);

    tools_memory_check_at_end_of_app();
    
    return (EXIT_SUCCESS);
}