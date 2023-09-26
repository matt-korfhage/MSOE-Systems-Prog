#include <stdio.h>
#include "mymath.h"

#define MAX_VAL_ARGS_LEN 3
#define NUM_BITS_ARGS_LEN 4

int maxValueArgs[] = {8, 16, 32};
int numBitsArgs[] = {7, 8, 15, 16};

int main(int argc, char* argv[])
{
    for(int i = 0; i < MAX_VAL_ARGS_LEN; ++i) {
        printf("Max value of %d bits is %d \n", maxValueArgs[i], maxvalue(maxValueArgs[i]));
    }

    for(int i = 0; i < NUM_BITS_ARGS_LEN; ++i) {
        printf("Minimum num bits to represent %d is %d \n", numBitsArgs[i], numbits(numBitsArgs[i]));
    }
}