#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "prac1.h"

void insertion_sort(int array[], int array_length);
void selection_sort(int array[], int array_length);
void bubble_sort(int array[], int array_length);


int cmpfunc(const void *p, const void *q);

int main(int argc, const char * argv[]) {

    // Define the time structures to keep track of start and end time
    struct timeval start, end;

    char file_name[] = "Wallclock_times" ; // Put your own filename here for the algorithm(s) evaluated

    // Define input arrays
    int *array_10;//To define array using function initialise pointer of type int
    int x = 10000;
    array_10 = gen_random_int_array(x);   // Call function with intended length, returns pointer to array_integer

    char type_sort;
    printf("Choose your type of sorting method Q, I, S or B: ");
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
void insertion_sort(int array[], int array_length)
{
    int i, j;
	int swap;

	for(i = 1; i < 5; i++){

		swap = array[i];
		j = i - 1;

		while( (swap < array[j]) && (j >= 0)){

			// swap
			array[j + 1] = array[j];
			j = j - 1;
		}

		array[j + 1] = swap;
	}
	return;
}



void selection_sort(int array[], int array_length)
{
    int n, position, swap;
    for (int i = 0; i <= array_length-1; i++)
    {
        position = i;
        for (int j = i + 1; j < array_length; j++)
        {
            if (array[position] > array[j])
                position = j;
        }
        if (position != i)
        {
            swap = array[i];
            array[i] = array[position];
            array[position] = swap;
        }
    }
}
void bubble_sort(int array[], int array_length)
{
    int swap;

    for (int i = 0; i < array_length - 1; i++)
    {
        for (int j = 0; j < array_length - 1 - i; j++)
        {
            if (array[j] > array[j+1])
            {
                swap = array[j];
                array[j] = array[j+1];
                array[j+1] = swap;
            }
        }
    }
}

int cmpfunc(const void *p, const void *q)
{
    int x = *(const int *)p;
    int y = *(const int *)q;


    if (x < y)
        return -1;  // Return -1 if you want ascending, 1 if you want descending order.
    else if (x > y)
        return 1;   // Return 1 if you want ascending, -1 if you want descending order.

    return 0;
}
