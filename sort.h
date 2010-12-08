/*
 * sort.h - types, definitions of the
 * various sorting algorithms and APIs
 * in this library. should be included
 * by users of this library.
 */

#ifndef __LIBSORT_H
#define __LIBSORT_H

#include <stddef.h>

/************* type definitions and macros ************/
#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif

/* comparison function - user-supplied function which can be
 * used to customize sort results to the specific data type
 * or for a specific direction.
 * 
 * RETURN VALUES:
 *     negative return: a < b
 *     zero return: a == b
 *     positive return: a > b
 *
 * NOTE: several standard functions
 * are provided with this libary, see below for details */
typedef int (*compare_func)(const void * first, const void * second);

/* sort function - API-supplied functions for sorting lists. Requires
 * the user to specify a comparison function.
 *  return value: TRUE on success, FALSE on failure */
typedef int (*sort_func)(void * list, size_t nelem, size_t elem_size,
                         compare_func comp);

/************* public APIs & supplied functions ************/

int int_compare_asc(const void * first, const void * second);
int int_compare_desc(const void * first, const void * second);
int char_compare_asc(const void * first, const void * second);
int char_compare_desc(const void * first, const void * second);

/* libary-defined sort routines: note that externs (while klugey) are
 * used here to reduce header dependencies, so their use is probably OK */
extern int bubblesort(void * list, size_t nelem, size_t elem_size, compare_func comp);
extern int mergesort(void * list, size_t nelem, size_t elem_size, compare_func comp);
extern int mergesort_onemalloc(void * list, size_t nelem, size_t elem_size, compare_func comp, char * templist);
extern int quicksort(void * list, size_t left, size_t right, size_t esize, compare_func comp);

#endif /* __LIBSORT_H */
