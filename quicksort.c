/*
 * quicksort.c - first-pass implementation of a quicksort
 */

#include "sort.h"
#include <stdlib.h>
#include <string.h>

/* in-place quicksort inspired by psuedo-code on Wikipedia */
int quicksort(void * list, size_t nelem, size_t esize, compare_func comp)
{
    size_t pivot;
    char * tmp, * leftpos, *rightpos, *pivotpos;

    tmp = malloc(esize);
    if(!tmp)
        return FALSE;

    if((nelem) > 0)
        pivot = (nelem) / 2;

    leftpos = (unsigned char*)list + (0*esize);
    rightpos = (unsigned char*)list + ((nelem-1)*esize);
    pivotpos = (unsigned char*)list + (pivot*esize);

    while(leftpos <= pivotpos && rightpos >= pivotpos)
    {
        while(comp(leftpos, pivotpos) < 0 && leftpos <= pivotpos)
        {
            leftpos += esize;
            while(comp(rightpos, pivotpos) > 0 && rightpos >= pivotpos)
            {
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
        }
    }

    free(tmp);

    return TRUE;
}
