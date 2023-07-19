//
//  prac1.h
//
//
//  Created by Melvin Ferreira on 2022/03/30.
//

#ifndef prac1_h
#define prac1_h

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>       // For seed in rand
#include <sys/time.h>   // for gettimeofday()
#include <unistd.h>     // for sleep()

// Returns the wall time from the computer in seconds. As input the start and end time to compute, the time elapsed is needed. start and end are both of type “struct timeval.”
float get_wall_time(struct timeval start,struct timeval end);

// Dynamically creates and initialises a random integer array. Returns a pointer to the array. As input, the array length required is needed.
int * gen_random_int_array(int array_length) ;

// Call to write the sorting algorithms statistics to a .csv file.
// char * accepts a string - the filename without extensions, the integer length (n), and the wall_time. Wall_time can be obtained with get_wall_time
void append_file(const char *, int length, float wall_time) ;

#endif /* prac1_h */


