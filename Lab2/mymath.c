#include "mymath.h"
#include <math.h>

int maxvalue(int bits) {
    return (int) pow((double) BINARY_RADIX, (double) bits) - 1;
}

int numbits(int value) {
    return (int) ( log(value) / log(BINARY_RADIX) ) + 1;
}