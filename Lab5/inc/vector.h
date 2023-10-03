#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

// Only want to represent vectors in three dimensions at most
#define MAX_VECTOR_DIMENSION 3
// Length of a name of a vector at maximum is 50
#define MAX_VECTOR_NAME_LEN 50
#define MAX_VECTORS 10

#define SAME_DIMENSIONS(a, b) ( a.vecSize == b.vecSize )

typedef struct {

    char vecName[MAX_VECTOR_NAME_LEN]; // name of vector
    double magnitudes[MAX_VECTOR_DIMENSION]; // magnitudes as floating point
    int vecSize; // Size of vector (how many dimensions)

} vector;

vector add(vector a, vector b);

vector sub(vector a, vector b);

vector dotprod(vector a, vector b);

vector scalarmul(vector a, double b);

vector xprod(vector a, vector b);

void addVectorToMemoryList( vector toAdd );

void clearVectors( void );

void printVector( vector toPrint );

bool grabVector(vector *a);

void copyVectorKeepName( vector *src, vector *dst );

#endif /* vector.h */