/*
 * bubblesort.c - naive implementation of a bubblesort
 */

#include "sort.h"
#include <stdlib.h>
#include <string.h>

int bubblesort(void * list, size_t nelem, size_t elem_size, compare_func comp)
{
    int remain, new_remain, i;
    char * cur_memloc, * swapmem;

    swapmem = malloc(elem_size);
    if(!swapmem)
        return FALSE;
   
    /* we haven't sorted anything yet */
    remain = nelem;

    /* attempting the 'optimized' bubble sort listed on Wikipedia,
     * where all elements after the last swap are sorted and don't need
     * to be checked again */
    do
    {
        new_remain = 0;
        for(i = 0; i < remain - 1; i++)
        {
            cur_memloc = list + (i*elem_size);
            /* compare item i, i+1 and swap if needed */
            if(comp(cur_memloc, cur_memloc + elem_size) > 0)
            {
                /* swap memory locations */
                memcpy(swapmem, cur_memloc, elem_size);
                memcpy(cur_memloc, cur_memloc + elem_size, elem_size);
                memcpy(cur_memloc + elem_size, swapmem, elem_size);

                new_remain = i + 1;
            }
        }

        remain = new_remain;
    } while(remain > 1);

    return TRUE;
}
