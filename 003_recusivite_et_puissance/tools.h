#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <stdio.h>
#include <stdlib.h>

int GLOBAL_ALLOC_MEMORY;

/* regstr = regular str = string with an ending '\0' */
typedef char* regstr;

int string_to_int(char* str);
/*
	ok vaut 1 si pas de caractères autre aue '0'-'9'
	ok vaut 0 sinon
*/
int safe_string_to_int(char* str, int* ok);
void int_swap(int* n, int* m);
void char_swap(char* n, char* m);

float puiss_iter(float a, int b);
float puiss_rec(float a, int b);
float puiss_alex(float a, int b);

void tools_memory_init(void);
void* tools_malloc(int alloc);
void tools_free(void* ptr, int alloc);
void tools_memory_check_at_end_of_app(void);

#endif