//
//  prac1.c
//  
//
//  Created by Melvin Ferreira on 2022/03/30.
// Ideas used in this codebase is based on readings from the following websites and books:
// Skiena 3rd ed.
// Horton - Beginning C
// https://linuxhint.com/gettimeofday_c_language/
// https://www.tutorialspoint.com/c_standard_library/c_function_strcat.htm
// https://www.tutorialspoint.com/cprogramming/c_return_arrays_from_function.htm


#include "prac1.h"

int * gen_random_int_array(int array_length) {
    
    int limit = array_length * 10 ; // Ensures numbers limits are larger than array itself
    int *chosen = calloc(array_length, sizeof(int)); // Allocate and initialise array values to 0. Calloc for run-time initilaisiastion (length not known before the fact.)
    
    srand( (unsigned) time(NULL)) ; // Use clock time as seed
  
    for (int i = 0; i < array_length; ++i) {
      chosen[i] = rand() % limit;
   //   printf( "chosen[%d] = %d\n", i, chosen[i]);
    }

    return chosen;
}

float get_wall_time(struct timeval start,struct timeval end) {
    float milli = 0.0f ;
    float seconds = (end.tv_sec - start.tv_sec);
    float micros = (end.tv_usec) - (start.tv_usec);
    milli = micros / 1e6 ;
    //long milli = (end.tv_usec - start.tv_usec) / 1000 ;
    return seconds + milli; // Returns time elapsed in seconds
}

void append_file(const char *str, int length, float wall_time)
{
    FILE *Output ;
    char file_name[100] ;
    strcpy(file_name, str) ; // Copy string from main program into filename
    //Variables for timestamp on filename
    struct timeval tv;
    time_t t;
    struct tm *info;
    char suffix[64];
     
    gettimeofday(&tv, NULL);
     t = tv.tv_sec;
    info = localtime(&t); // To get time to be formatted on filename.
    strftime (suffix, sizeof suffix, "_%d_%b.csv", info);
    strcat(file_name, suffix); // Concatenate to filename
    //printf("%s\n",file_name);
    printf("**File I/O** \n") ;
    Output = fopen(file_name,"a") ;
    if (Output == NULL)
        printf("Error!!!, can't open file for writing to \n") ;
    else {
        printf("Appending the following results to %s:\n",file_name) ;
        printf("%d,%0.3f\n",length,wall_time) ;
        fprintf(Output,"%d,%0.3f\n",length,wall_time) ;
        fclose(Output) ;
    }
}


