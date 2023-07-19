#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "prac1.h"

int cmpfunc(const void *p, const void *q);

int main(int argc, const char * argv[]) {

    // Define the time structures to keep track of start and end time
    struct timeval start, end;

    char file_name[] = "37368737_sort" ; // Put your own filename here for the algorithm(s) evaluated

    // Define input arrays
    int *array_10; //To define array using function initialise pointer of type int
    array_10 = gen_random_int_array(10);   // Call function with intended length, returns pointer to array_integer

    // Print out array as one would normally do - sanity check. Comment out once happy.
    for (int i = 0; i < 10; i++ ) {
     printf( "array_10[%d] : %d\n", i, array_10[i]);
    }

    // Call to start wall clock before executing sorting algorithm
    gettimeofday(&start, NULL);

    // Replace your sorting algorithm here to time it. Remove sleep and usleep - only used to simulate time taken by sorting algorith.

    //Run sorting algorithm - qsort - see example in SU4 lecture...
    qsort(array_10,10,sizeof(int),cmpfunc);

    // Call to stop wall clock after executing sorting algorithm
    gettimeofday(&end, NULL);

    //Call get_wall_time to get elapesed time inseconds. Write to screen
    printf("Wall_clock elapsed time is %0.3f seconds\n",get_wall_time(start,end));

    free(array_10) ;   // NB remember to free your array variables after use! very NB

    append_file(file_name,10,get_wall_time(start,end)) ; // Call to write result of run to file

    return 0;
}

int cmpfunc(const void *p, const void *q)
{
    int x = *(const int *)p;
    int y = *(const int *)q;

    /* Avoid return x - y, which can cause undefined behaviour
       because of signed integer overflow. */
    if (x < y)
        return -1;  // Return -1 if you want ascending, 1 if you want descending order.
    else if (x > y)
        return 1;   // Return 1 if you want ascending, -1 if you want descending order.

    return 0;
}


