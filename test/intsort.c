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

/* verify the list is sorted (asc or desc) */
int verify_sort(int * numbers, int len, short asc)
{
    int i;

    for(i = 0; i < len-1; i++)
    {
        if(asc && (numbers[i] > numbers[i+1]))
           printf("Failure! n[%d] > n[%d] (%d, %d)\n",
                  i, i+1, numbers[i], numbers[i+1]);
        if(!asc && (numbers[i] < numbers[i+1]))
           printf("Failure! n[%d] < n[%d] (%d, %d)\n",
                  i, i+1, numbers[i], numbers[i+1]);
    }
}

/* simplify the running of sort algorithms in main by
 * pulling common code into a helper function */
int do_int_sort(int * numbers, int len, char * name, void * func,
                compare_func comp)
{
    struct timeval start, end;
    printf("Sorting %s, int %s: ", name,
           (comp == &int_compare_asc? "asc" : "desc"));
    fflush(stdout);

    /* if C had closures / lambda functions, this would
     * be much cleaner/cooler code... */
    if(func == &bubblesort)
    {
        gettimeofday(&start, NULL);
        bubblesort(numbers, len, sizeof(int), comp);
        gettimeofday(&end, NULL);
    }
    else if(func == &mergesort)
    {
        gettimeofday(&start, NULL);
        mergesort(numbers, len, sizeof(int), comp);
        gettimeofday(&end, NULL);
    }
    else if(func == &mergesort_onemalloc)
    {
        gettimeofday(&start, NULL);
        mergesort_onemalloc(numbers, len, sizeof(int), comp, NULL);
        gettimeofday(&end, NULL);
    }
    else if(func == &quicksort)
    {
        gettimeofday(&start, NULL);
        quicksort(numbers, 0, len-1, sizeof(int), comp);
        gettimeofday(&end, NULL);
    }
    else if(func == &quicksort_onemalloc)
    {
        gettimeofday(&start, NULL);
        quicksort_onemalloc(numbers, 0, len-1, sizeof(int), comp, NULL);
        gettimeofday(&end, NULL);
    }
    printtime(&start, &end);
}

/* main - generate a list of random numbers
 * and sort it a bunch of times. Display timings
 * for each algorithm. */
int main(int argc, char ** argv)
{
    int * numbers;
    int   len, i;
    char * algo = NULL;

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
        /* sort ASC, verify the list is sorted ascending */
        do_int_sort(numbers, len, "bubblesort",
                    &bubblesort, int_compare_asc);
        verify_sort(numbers, len, 1);

        /* sort DESC, verify the list is sorted descending */
        do_int_sort(numbers, len, "bubblesort",
                    &bubblesort, int_compare_desc);
        verify_sort(numbers, len, 0);
    }


    if(algo == NULL || strcmp(algo, "merge") == 0)
    {
        /* sort ASC, verify the list is sorted ascending */
        do_int_sort(numbers, len, "mergesort",
                    &mergesort, int_compare_asc);
        verify_sort(numbers, len, 1);

        /* sort DESC, verify the list is sorted descending */
        do_int_sort(numbers, len, "mergesort",
                    &mergesort, int_compare_desc);
        verify_sort(numbers, len, 0);
    }

    if(algo == NULL || strcmp(algo, "mone") == 0)
    {
        /* sort ASC, verify the list is sorted ascending */
        do_int_sort(numbers, len, "mergesort_onemalloc",
                    &mergesort_onemalloc, int_compare_asc);
        verify_sort(numbers, len, 1);

        /* sort DESC, verify the list is sorted descending */
        do_int_sort(numbers, len, "mergesort_onemalloc",
                    &mergesort_onemalloc, int_compare_desc);
        verify_sort(numbers, len, 0);
    }

    if(algo == NULL || strcmp(algo, "quick") == 0)
    {
        /* sort ASC, verify the list is sorted ascending */
        do_int_sort(numbers, len, "quicksort",
                    &quicksort, int_compare_asc);
        verify_sort(numbers, len, 1);

        /* verify the list is sorted descending */
        do_int_sort(numbers, len, "quicksort",
                    &quicksort, int_compare_desc);
        verify_sort(numbers, len, 0);
    }

    if(algo == NULL || strcmp(algo, "qone") == 0)
    {
        /* sort ASC, verify the list is sorted ascending */
        do_int_sort(numbers, len, "quicksort_onemalloc",
                    &quicksort_onemalloc, int_compare_asc);
        verify_sort(numbers, len, 1);

        /* verify the list is sorted descending */
        do_int_sort(numbers, len, "quicksort_onemalloc",
                    &quicksort_onemalloc, int_compare_desc);
        verify_sort(numbers, len, 0);
    }

    free(numbers);
    return 0;
}
