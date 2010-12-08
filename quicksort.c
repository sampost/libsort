/*
 * quicksort.c - first-pass implementation of a quicksort
 */

#include "sort.h"
#include <stdlib.h>
#include <string.h>

/* in-place quicksort inspired by psuedo-code on Wikipedia */
int quicksort(void * list, size_t left, size_t right, size_t esize, compare_func comp)
{
    size_t pivot;
    char * tmp, * leftpos, *rightpos, *pivotpos;

    if(((signed long long)right - (signed long long)left) <= 0)
        return TRUE; /* done */

    tmp = malloc(esize);
    if(!tmp)
        return FALSE;

    pivot = (left + right) / 2;

    leftpos = (unsigned char*)list + (left*esize);
    rightpos = (unsigned char*)list + (right*esize);
    pivotpos = (unsigned char*)list + (pivot*esize);

    while(leftpos <= pivotpos && rightpos >= pivotpos)
    {
        while(comp(leftpos, pivotpos) < 0 && leftpos <= pivotpos)
            leftpos += esize;
        while(comp(rightpos, pivotpos) > 0 && rightpos >= pivotpos)
            rightpos -= esize;

        // swap left with right
        memcpy(tmp, leftpos, esize);
        memcpy(leftpos, rightpos, esize);
        memcpy(rightpos, tmp, esize);

        leftpos += esize;
        rightpos -= esize;

        if(leftpos - esize == pivotpos)
            pivotpos = rightpos = rightpos + esize;
        else if(rightpos+esize == pivotpos)
            pivotpos = leftpos = leftpos - esize;
    }
    pivot = (pivotpos - (char*)list)/esize;
    quicksort(list, left, pivot - 1, esize, comp);
    quicksort(list, pivot + 1, right, esize, comp);

    free(tmp);

    return TRUE;
}
