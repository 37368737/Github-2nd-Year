#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "prac1.h"

void insertion_sort(int array[],int x);
void selection_sort(int array[],int x);
void bubble_sort(int array[],int x);

int cmpfunc(const void *p, const void *q);

int main(int argc, const char * argv[]) {

    // Define the time structures to keep track of start and end time
    struct timeval start, end;

    char file_name[] = "Execution_times" ; // Put your own filename here for the algorithm(s) evaluated

    // Define input arrays
    int *array_10;//To define array using function initialise pointer of type int
    int x = 100000;
    array_10 = gen_random_int_array(x);   // Call function with intended length, returns pointer to array_integer

    char type_sort;
    printf("Type of sorting method Q, I, S or B: ");
    scanf("%c",&type_sort);

    if (type_sort == 'Q'){
    // Call to start wall clock before executing sorting algorithm
    gettimeofday(&start, NULL);

    // Replace your sorting algorithm here to time it. Remove sleep and usleep - only used to simulate time taken by sorting algorith.

    //Run sorting algorithm - qsort - see example in SU4 lecture...
    qsort(array_10,x,sizeof(int),cmpfunc);

    // Call to stop wall clock after executing sorting algorithm
    gettimeofday(&end, NULL);
    }

    else if(type_sort == 'I'){
     // Call to start wall clock before executing sorting algorithm
    gettimeofday(&start, NULL);

    // Memcopy for next sorting algorithm...

    // Run algorithm
    insertion_sort(array_10,x);

    // Call to stop wall clock after executing sorting algorithm
    gettimeofday(&end, NULL);
    }

    else if(type_sort == 'S'){
     // Call to start wall clock before executing sorting algorithm
    gettimeofday(&start, NULL);

    // Memcopy for next sorting algorithm...

    // Run algorithm
    selection_sort(array_10,x);

    // Call to stop wall clock after executing sorting algorithm
    gettimeofday(&end, NULL);
    }

    else if(type_sort == 'B'){
     // Call to start wall clock before executing sorting algorithm
    gettimeofday(&start, NULL);

    // Memcopy for next sorting algorithm...

    // Run algorithm
    bubble_sort(array_10,x);

    // Call to stop wall clock after executing sorting algorithm
    gettimeofday(&end, NULL);
    }
    //Call get_wall_time to get elapesed time inseconds. Write to screen
    printf("Wall_clock elapsed time is %0.3f seconds\n",get_wall_time(start,end));

    free(array_10) ;   // NB remember to free your array variables after use! very NB

    append_file(file_name,x,get_wall_time(start,end)) ; // Call to write result of run to file

    return 0;
}
void insertion_sort(int array[],int x)
{
    //Your code here
    for(int i = 1; i < x; i++)
{
        int count = array[i], k = i - 1;
        while (k >= 0 && array[k] > count)
    {
            array[k + 1] = array[k]; k = k - 1;
    }
            array[k+1] = count;

}
}
void selection_sort(int array[],int x)
{
    //Your code here
    for (int i = 0; i < (x - 1); i++) {
      int k = i;
      for (int j = i + 1; j < x; j++) {
         if (array[k] > array[j])
            k = j;
      }
      if (k != i) {
         int swap = array[i];
         array[i] = array[k];
         array[k] = swap;
      }
   }
}
void bubble_sort(int array[],int x)
{
    //Your code here, test with different input cases
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int i = 0; i< x; i++){
            if(array[i]>array[i+1]){
                sorted = false;
                int swap = array[i+1];
                array[i+1] = array[i];
                array[i] = swap;
            }
        }
    }
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


