#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void insertion_sort(int array[],int array_length);
void selection_sort(int array[],int array_length);
void bubble_sort(int array[],int array_length);

int cmpfunc(const void *p, const void *q);

int main(void)
{
    //variable declarations
    int array_length = 5;
    int input_array[5], array_qsort[5], array_ins_sort[5], array_sel_sort[5], array_bub_sort[5] ;

    //Read in 5 integers from keybord
    for (int i=0; i<= array_length-1; i++) {
        printf("Enter number %d\n",i+1);
        scanf("%d", &input_array[i]);
    }
    //Display unsorted array
    printf("***Unsorted array received from keyboard*** \n");
    for (int i=0; i<= array_length-1; i++) {
        printf("Array[%d] = %d\n",i+1,input_array[i]);
    }
    //Memcopy unsorted array. Recall arrays are passed by reference in c...
    memcpy(array_qsort,input_array,sizeof(input_array));

    //Run sorting algorithm - qsort - see example in SU4 lecture...
    qsort(array_qsort,array_length,sizeof(int),cmpfunc);

    //Display sorted array
    printf("***Quicksort output :sorted array*** \n");
    for (int i=0; i<= array_length-1; i++) {
        printf("Array[%d] = %d\n",i+1,array_qsort[i]);
    }

    // Memcopy for next sorting algorithm...
    memcpy(array_ins_sort,input_array,sizeof(input_array)); //INSERTION SORT
    // Run algorithm
    insertion_sort(array_ins_sort,array_length);
    // Display sorted results...
    printf("***Insertion sort output:sorted array*** \n");
    for (int i=0; i<= array_length-1; i++) {
        printf("Array[%d] = %d\n",i+1,array_ins_sort[i]);
    }

    // Memcopy for next sorting algorithm...
    memcpy(array_sel_sort,input_array,sizeof(input_array)); //SELECTION SORT
    // Run algorithm
    selection_sort(array_sel_sort,array_length);
    // Display sorted results...
    printf("***Selection sort output:sorted array*** \n");
    for (int i=0; i< array_length; i++) {
        printf("Array[%d] = %d\n",i+1,array_sel_sort[i]);
    }

    // Memcopy for next sorting algorithm...
    memcpy(array_bub_sort,input_array,sizeof(input_array)); //BUBBLE SORT
    // Run algorithm
    bubble_sort(array_bub_sort,array_length);
    // Display sorted results...
    printf("***Bubble sort output:sorted array*** \n");
    for (int i=0; i< array_length; i++) {
        printf("Array[%d] = %d\n",i+1,array_bub_sort[i+1]);
    }
    return 0;
}
void insertion_sort(int array[],int array_length)
{
    //Your code here
    for(int i = 1; i < array_length; i++)
{
        int count = array[i], k = i - 1;
        while (k >= 0 && array[k] > count)
    {
            array[k + 1] = array[k]; k = k - 1;
    }
            array[k+1] = count;

}
}
void selection_sort(int array[],int array_length)
{
    //Your code here
    for (int i = 0; i < (array_length - 1); i++) {
      int k = i;
      for (int j = i + 1; j < array_length; j++) {
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
void bubble_sort(int array[],int array_length)
{
    //Your code here, test with different input cases
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int i = 0; i< array_length; i++){
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
