/*
 * mergesort.c - first-pass implementation of a merge sort
 */

#include "sort.h"
#include <stdlib.h>
#include <string.h>

int merge(void * left, size_t leftsize, void * right, size_t rightsize,
          size_t elem_size, compare_func comp)
{
    char * templist, * temploc, * leftloc, * rightloc;
    size_t tempsize, totalsize;

    /* allocate a temporary list for merging into */
    templist = malloc((leftsize + rightsize) * elem_size);
    if(!templist)
        return FALSE;

    leftloc = left;
    rightloc = right;
    temploc = templist;
    tempsize = 0;
    totalsize = leftsize + rightsize;

    while(tempsize < totalsize)
    {
        /* if both lists have remaining item(s), compare next 
         * elements/decide which list to pull an item from */
        if(leftsize && rightsize)
        {
            if(comp(leftloc, rightloc) < 0)
            {
                memcpy(temploc, leftloc, elem_size);
                leftloc += elem_size;
                leftsize--;
            }
            else
            {
                memcpy(temploc, rightloc, elem_size);
                rightloc += elem_size;
                rightsize--;
            }
        }
        else if(leftsize)
        {
            memcpy(temploc, leftloc, elem_size);
            leftloc += elem_size;
            leftsize--;
        }
        else if(rightsize)
        {
            memcpy(temploc, rightloc, elem_size);
            rightloc += elem_size;
            rightsize--;
        }

        temploc += elem_size;
        tempsize++;
    }

    /* copy from the temporary list to the original list(s) - note
     * this assumes the two lists are virtually contiguous in RAM */
    memcpy(left, templist, elem_size * totalsize);

    free(templist);

    return TRUE;
}



int mergesort(void * list, size_t nelem, size_t elem_size, compare_func comp)
{
    void * left, * right;
    size_t middle, leftsize, rightsize;

    /* basis case: list of size zero or one is a sorted list. */
    if(nelem <= 1)
        return TRUE;

    middle = nelem >> 1;
    left  = list;
    leftsize = middle;
    right = list + (middle * elem_size);
    rightsize = nelem - leftsize;

    /* sort the left and right lists */
    if(!mergesort(left,  leftsize, elem_size, comp))
        return FALSE;
    if(!mergesort(right, rightsize, elem_size, comp))
        return FALSE;

    /* merge the two sorted lists into one larger sorted list */
    if(!merge(left, leftsize, right, rightsize, elem_size, comp))
        return FALSE;

    return TRUE;
}


int merge_nomalloc(void * left, size_t leftsize, void * right, size_t rightsize,
                   size_t elem_size, compare_func comp, char * templist)
{
    char * temploc, * leftloc, * rightloc;
    size_t tempsize, totalsize;


    leftloc = left;
    rightloc = right;
    temploc = templist;
    tempsize = 0;
    totalsize = leftsize + rightsize;

    while(tempsize < totalsize)
    {
        /* if both lists have remaining item(s), compare next
         * elements/decide which list to pull an item from */
        if(leftsize && rightsize)
        {
            if(comp(leftloc, rightloc) < 0)
            {
                memcpy(temploc, leftloc, elem_size);
                leftloc += elem_size;
                leftsize--;
            }
            else
            {
                memcpy(temploc, rightloc, elem_size);
                rightloc += elem_size;
                rightsize--;
            }
        }
        else if(leftsize)
        {
            memcpy(temploc, leftloc, elem_size);
            leftloc += elem_size;
            leftsize--;
        }
        else if(rightsize)
        {
            memcpy(temploc, rightloc, elem_size);
            rightloc += elem_size;
            rightsize--;
        }

        temploc += elem_size;
        tempsize++;
    }

    /* copy from the temporary list to the original list(s) - note
     * this assumes the two lists are virtually contiguous in RAM */
    memcpy(left, templist, elem_size * totalsize);

    return TRUE;
}


/* mergesort with reduced number of mallocs (one) */
int mergesort_onemalloc(void * list, size_t nelem, size_t elem_size,
                        compare_func comp, char * templist)
{
    void * left, * right;
    size_t middle, leftsize, rightsize;
    unsigned int do_free = FALSE;

    /* allocate a temporary list for merging into */
    if(!templist)
    {
        do_free = TRUE;
        templist = malloc(nelem * elem_size);
        if(!templist)
            return FALSE;
    }

    /* basis case: list of size zero or one is a sorted list. */
    if(nelem <= 1)
        return TRUE;

    middle = nelem >> 1;
    left  = list;
    leftsize = middle;
    right = list + (middle * elem_size);
    rightsize = nelem - leftsize;

    /* sort the left and right lists */
    if(!mergesort_onemalloc(left,  leftsize, elem_size, comp, templist))
        goto free_fail;
    if(!mergesort_onemalloc(right, rightsize, elem_size, comp, templist))
        goto free_fail;

    /* merge the two sorted lists into one larger sorted list */
    if(!merge_nomalloc(left, leftsize, right, rightsize, elem_size, comp, templist))
        goto free_fail;

    if(do_free)
        free(templist);

    return TRUE;

free_fail:
    if(do_free)
        free(templist);

    return FALSE;
}
