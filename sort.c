/*
 * sort.c - implementation of the generic
 * element comparison functions, etc
 */

#include "sort.h"

int int_compare_asc(const void * first, const void * second)
{
    int a = *(int*)first;
    int b = *(int*)second;
    if(a == b) return 0;
    return (a < b ? -1 : 1);
}

int int_compare_desc(const void * first, const void * second)
{
    int a = *(int*)first;
    int b = *(int*)second;
    if(a == b) return 0;
    return (a > b ? -1 : 1);
}

int char_compare_asc(const void * first, const void * second)
{
    char a = *(char*)first;
    char b = *(char*)second;
    if(a == b) return 0;
    return (a < b ? -1 : 1);
}

int char_compare_desc(const void * first, const void * second)
{
    char a = *(char*)first;
    char b = *(char*)second;
    if(a == b) return 0;
    return (a > b ? -1 : 1);
}
