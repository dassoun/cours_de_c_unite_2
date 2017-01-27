/*
 * Cours de Jacques-Olivier Lapeyre
 * Unité 2
 * Cours 5
 * Complexité algorithmique - suite
 * https://www.youtube.com/watch?v=7ud0zFW15-8
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "tools.h"
#include "intarray.h"

int main(int argc, char *argv[]) 
{	
    int n = 1000;
    int cpt = 0;
    int i;
    int ok;

    if (argc >= 2)
    {
        int v = safe_string_to_int(argv[1], &ok);

        if (ok == 1)
            n = v;
    }

    if (n < 0)
    {
        printf("%d est négatif. Nous cherchons les diviseurs de %d.\n", n, -n);
        n = -n;
    }

    printf("\n\nVersion naïve : \n", cpt, n);

    /*
    *   Version Naïve
    */
    for (i=1; i<=n; i++)
    {
        if (n % i == 0)
        {
            cpt++;
            fprintf(stderr, "%d ", i);
        }
    }

    printf("\n\nVersion améliorée : \n", cpt, n);

    /*
    *   Version améliorée
    */

    intarray divs = standard_empty_intarray_create();

    for (i=1; i<=sqrt(n) + 1; i++)
    {
        if (n % i == 0)
        {
            intarray_add(divs, i);
            intarray_add(divs, (n / i));
        }
    }

    intarray_sort1(divs);

    intarray_debug(divs);

    printf("\n%d diviseurs de %d trouvés.\n\n", divs->len, n);

    intarray_destroy(divs);

    tools_memory_check_at_end_of_app();
    
    return (EXIT_SUCCESS);
}