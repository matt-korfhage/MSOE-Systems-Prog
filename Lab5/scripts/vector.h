#ifndef VECTOR_H
#define VECTOR_H

// Only want to represent vectors in three dimensions at most
#define MAX_VECTOR_DIMENSION 3
// Length of a name of a vector at maximum is 50
#define MAX_VECTOR_NAME_LEN 50

typedef struct {
    
    char vecName[MAX_VECTOR_NAME_LEN]; // name of vector
    double magnitudes[MAX_VECTOR_DIMENSION]; // magnitudes as floating point

} vector;

#endif /* vector.h */