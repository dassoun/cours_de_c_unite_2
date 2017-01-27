/*
 * Cours de Jacques-Olivier Lapeyre
 * Unité 2
 * Cours 3
 * Récursivité et puissance alexandrine
 * https://www.youtube.com/watch?v=8yP5uMJTVZY
 */
#include <stdio.h>
#include <stdlib.h>

#include "tools.h"

int main(int argc, char *argv[]) 
{	
	float a;

    tools_memory_init();

    a = puiss_iter(2.0, 24);
    printf("iterative\n");
    printf("a = %f\n", a);
    printf("\n");

	a = puiss_rec(2.0, 24);
	printf("récursive\n");
    printf("a = %f\n", a);
    printf("\n");

    a = puiss_alex(2.0, 24);
    printf("alexendrine\n");
    printf("a = %f\n", a);
    printf("\n");    

    tools_memory_check_at_end_of_app();
    
    return (EXIT_SUCCESS);
}