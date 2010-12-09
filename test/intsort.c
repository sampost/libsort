/*
 * intsort - a trivial sorting program which sorts a randomly generated array
 *
 * TODO - read in data from data file(s)
 *
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sort.h"

/* printtime - display the difference between
 * two timestamps in sec, usec */
void printtime(struct timeval * start, struct timeval * end)
{
    unsigned long long    diff_us;

    diff_us =
        (((unsigned long long)end->tv_sec)*1000000 + end->tv_usec) -
        (((unsigned long long)start->tv_sec)*1000000 + start->tv_usec);

    printf("%llu s, %06llu us\n", diff_us/1000000, diff_us%1000000);
}

int main(int argc, char ** argv)
{
    int * numbers;
    int   len, i;
    char * algo = NULL;
    struct timeval start, end;

    if(argc == 3)
    {
        algo = argv[2];
        printf("Limiting algorithm to %s\n", algo);
    }

    srand(time(NULL));
    if(argc >= 2)
        len = atoi(argv[1]);
    else
    {
        /* if unspecified, choose how long the list should be randomly.
         * cap it at 100K elements for runtime's sake */
        len = rand() % 100000;
    }

    printf("Generating array of %d random int's\n", len);
    numbers = malloc(sizeof(int) * len);
    if(!numbers)
        return 1;

    for(i = 0; i < len; i++)
        numbers[i] = rand();

    if(algo == NULL || strcmp(algo, "bubble") == 0)
    {
        printf("Sorting bubblesort, int asc: ");
        fflush(stdout);
        gettimeofday(&start, NULL);
        bubblesort(numbers, len, sizeof(int), int_compare_asc);
        gettimeofday(&end, NULL);
        printtime(&start, &end);

        /* verify the list is sorted ascending */
        for(i = 0; i < len-1; i++)
            if(numbers[i] > numbers[i+1])
                printf("Failure! n[%d] > n[%d] (%d, %d)\n",
                        i, i+1, numbers[i], numbers[i+1]);

        printf("Sorting bubblesort, int desc: ");
        fflush(stdout);
        gettimeofday(&start, NULL);
        bubblesort(numbers, len, sizeof(int), int_compare_desc);
        gettimeofday(&end, NULL);
        printtime(&start, &end);

        /* verify the list is sorted descending */
        for(i = 0; i < len-1; i++)
            if(numbers[i] < numbers[i+1])
                printf("Failure! n[%d] < n[%d] (%d, %d)\n",
                        i, i+1, numbers[i], numbers[i+1]);
    }


    if(algo == NULL || strcmp(algo, "merge") == 0)
    {
        printf("Sorting mergesort, int asc: ");
        fflush(stdout);
        gettimeofday(&start, NULL);
        mergesort(numbers, len, sizeof(int), int_compare_asc);
        gettimeofday(&end, NULL);
        printtime(&start, &end);


        /* verify the list is sorted ascending */
        for(i = 0; i < len-1; i++)
            if(numbers[i] > numbers[i+1])
                printf("Failure! n[%d] > n[%d] (%d, %d)\n",
                        i, i+1, numbers[i], numbers[i+1]);

        printf("Sorting mergesort, int desc: ");
        fflush(stdout);
        gettimeofday(&start, NULL);
        mergesort(numbers, len, sizeof(int), int_compare_desc);
        gettimeofday(&end, NULL);
        printtime(&start, &end);

        /* verify the list is sorted descending */
        for(i = 0; i < len-1; i++)
            if(numbers[i] < numbers[i+1])
                printf("Failure! n[%d] < n[%d] (%d, %d)\n",
                        i, i+1, numbers[i], numbers[i+1]);
    }

    if(algo == NULL || strcmp(algo, "mone") == 0)
    {
        printf("Sorting mergesort_onemalloc, int asc: ");
        fflush(stdout);
        gettimeofday(&start, NULL);
        mergesort_onemalloc(numbers, len, sizeof(int), int_compare_asc, NULL);
        gettimeofday(&end, NULL);
        printtime(&start, &end);


        /* verify the list is sorted ascending */
        for(i = 0; i < len-1; i++)
            if(numbers[i] > numbers[i+1])
                printf("Failure! n[%d] > n[%d] (%d, %d)\n",
                        i, i+1, numbers[i], numbers[i+1]);

        printf("Sorting mergesort_onemalloc, int desc: ");
        fflush(stdout);
        gettimeofday(&start, NULL);
        mergesort_onemalloc(numbers, len, sizeof(int), int_compare_desc, NULL);
        gettimeofday(&end, NULL);
        printtime(&start, &end);

        /* verify the list is sorted descending */
        for(i = 0; i < len-1; i++)
            if(numbers[i] < numbers[i+1])
                printf("Failure! n[%d] < n[%d] (%d, %d)\n",
                        i, i+1, numbers[i], numbers[i+1]);
    }

    if(algo == NULL || strcmp(algo, "quick") == 0)
    {
        printf("Sorting quicksort, int asc: ");
        fflush(stdout);
        gettimeofday(&start, NULL);
        quicksort(numbers, 0, len-1, sizeof(int), int_compare_asc);
        gettimeofday(&end, NULL);
        printtime(&start, &end);


        /* verify the list is sorted ascending */
        for(i = 0; i < len-1; i++)
            if(numbers[i] > numbers[i+1])
                printf("Failure! n[%d] > n[%d] (%d, %d)\n",
                       i, i+1, numbers[i], numbers[i+1]);

        printf("Sorting quicksort, int desc: ");
        fflush(stdout);
        gettimeofday(&start, NULL);
        quicksort(numbers, 0, len-1, sizeof(int), int_compare_desc);
        gettimeofday(&end, NULL);
        printtime(&start, &end);

        /* verify the list is sorted descending */
        for(i = 0; i < len-1; i++)
            if(numbers[i] < numbers[i+1])
                printf("Failure! n[%d] < n[%d] (%d, %d)\n",
                       i, i+1, numbers[i], numbers[i+1]);
    }

    if(algo == NULL || strcmp(algo, "qone") == 0)
    {
        printf("Sorting quicksort_onemalloc, int asc: ");
        fflush(stdout);
        gettimeofday(&start, NULL);
        quicksort_onemalloc(numbers, 0, len-1, sizeof(int), int_compare_asc, NULL);
        gettimeofday(&end, NULL);
        printtime(&start, &end);


        /* verify the list is sorted ascending */
        for(i = 0; i < len-1; i++)
            if(numbers[i] > numbers[i+1])
                printf("Failure! n[%d] > n[%d] (%d, %d)\n",
                       i, i+1, numbers[i], numbers[i+1]);

        printf("Sorting quicksort_onemalloc, int desc: ");
        fflush(stdout);
        gettimeofday(&start, NULL);
        quicksort_onemalloc(numbers, 0, len-1, sizeof(int), int_compare_desc, NULL);
        gettimeofday(&end, NULL);
        printtime(&start, &end);

        /* verify the list is sorted descending */
        for(i = 0; i < len-1; i++)
            if(numbers[i] < numbers[i+1])
                printf("Failure! n[%d] < n[%d] (%d, %d)\n",
                       i, i+1, numbers[i], numbers[i+1]);
    }

    free(numbers);
    return 0;
}
