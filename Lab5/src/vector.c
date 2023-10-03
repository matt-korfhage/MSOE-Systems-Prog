/**
 * @file vector.c
 * @brief Library for creating and running operations on vectors
 * 
 * Course: CPE2600
 * Section: 011
 * Assignment: Lab 5 - Vectors
 * Name: Matt Korfhage
 */


#include "vector.h"
#include "termcolors.h"
#include <string.h>
#include <stdio.h>

static vector storedVectors[MAX_VECTORS];
static int headIndex = 0;


bool grabVector(vector *a) {
    
    bool successfulRetreiveOfVecA = false;

    for(int i = 0; i < MAX_VECTORS; ++i) {
        
        char * tableVecName = storedVectors[i].vecName;

        if( strcmp(tableVecName, a->vecName ) == 0 ) {
            *a = storedVectors[i];
            successfulRetreiveOfVecA = true;
        }

    }

    return successfulRetreiveOfVecA;
}


bool grabVectors(vector *a, vector *b) {
    return grabVector(a) && grabVector(b);
}


void copyVectorKeepName( vector *src, vector *dst ) {

    // Copy size
    dst->vecSize = src->vecSize;

    // Copy magnitudes
    for(int i = 0; i < src->vecSize; ++i) {
        dst->magnitudes[i] = src->magnitudes[i];
    }

} 


void printVector( vector toPrint ) {

    printf(ANSI_COLOR_BLUE);

    switch(toPrint.vecSize) {
        case 3:
            printf("\t%s = %f %f %f\n", toPrint.vecName, \
            toPrint.magnitudes[0], \
            toPrint.magnitudes[1], \
            toPrint.magnitudes[2]);
            break;

        case 2:
            printf("\t%s = %f %f\n", toPrint.vecName, \
            toPrint.magnitudes[0], \
            toPrint.magnitudes[1]); \
            break;

        case 1:
            printf("\t%s = %f\n", toPrint.vecName, \
            toPrint.magnitudes[0]); \
            break;
    }

    printf(ANSI_COLOR_RESET);
}


void clearVectors( void ) {
    
    for( int i = 0; i < MAX_VECTORS; ++i ) {
        volatile vector emptyVector = {0};

        storedVectors[i] = emptyVector;
    }

}


void addVectorToMemoryList( vector toAdd ) {

    bool vectorReplaced = false;

    for(int i = 0; i < MAX_VECTORS; ++i) {
        
        // if the vector stored has the same name replace it
        if( strcmp(storedVectors[i].vecName, toAdd.vecName) == 0 ) {
            storedVectors[i] = toAdd;
            vectorReplaced = true;
            break;
        }

    }

    if( ! vectorReplaced ) {
        storedVectors[headIndex++] = toAdd;
    }
}


vector add(vector a, vector b) {

    // Check vectors exist in memory and retrieve them
    if( ! grabVectors(&a, &b) ) {
        puts(ANSI_COLOR_RED "Vectors do not exist!" ANSI_COLOR_RESET);
        return a;
    }

    // Check dimensons
    if( ! SAME_DIMENSIONS(a, b) ) {
        puts(ANSI_COLOR_RED "Vectors do not have same dimension!" ANSI_COLOR_RESET);
        return a;
    }
    
    vector result;

    for(int i = 0; i < a.vecSize; ++i) {
        result.magnitudes[i] = a.magnitudes[i] + b.magnitudes[i];
    }
    
    strcpy(result.vecName, "ans");
    result.vecSize = a.vecSize;

    return result;
}


vector sub(vector a, vector b) {

    // Check vectors exist in memory and retrieve them
    if( ! grabVectors(&a, &b) ) {
        puts(ANSI_COLOR_RED "Vectors do not exist!" ANSI_COLOR_RESET);
        return a;
    }

    if( ! SAME_DIMENSIONS(a, b) ) {
        puts(ANSI_COLOR_RED "Vectors do not have same dimension!" ANSI_COLOR_RESET);
        return a;
    }
    
    vector result;

    for(int i = 0; i < a.vecSize; ++i) {
        result.magnitudes[i] = a.magnitudes[i] - b.magnitudes[i];
    }
    
    strcpy(result.vecName, "ans");
    result.vecSize = a.vecSize;

    return result;
}


vector dotprod(vector a, vector b) {
    
    if( ! grabVectors(&a, &b) ) {
        puts(ANSI_COLOR_RED "Vectors do not exist!" ANSI_COLOR_RESET);
        return a;
    }

    if( ! SAME_DIMENSIONS(a, b) ) {
        puts(ANSI_COLOR_RED "Vectors do not have same dimension!" ANSI_COLOR_RESET);
        return a;
    }
    
    double sum = 0.0f;

    for(int i = 0; i < a.vecSize; ++i) {
        sum += a.magnitudes[i] * b.magnitudes[i];
    }

    vector ans;
    strcpy(ans.vecName, "ans");
    ans.vecSize = 1;
    ans.magnitudes[0] = sum;

    return ans;
}


vector scalarmul(vector a, double b) {

    if( ! grabVector(&a) ) {
        puts("Vector does not exist!");
        return a;
    }

    for(int i = 0; i < a.vecSize; ++i) {
        a.magnitudes[i] *= b;
    }

    return a;
}


vector xprod(vector a, vector b) {

    if( ! grabVectors(&a, &b) ) {
        puts(ANSI_COLOR_RED "Vectors do not exist!" ANSI_COLOR_RESET);
        return a;
    }


    if( ! SAME_DIMENSIONS(a, b) || a.vecSize != 3) {
        puts(ANSI_COLOR_RED "Vectors do not have proper dimension!" ANSI_COLOR_RESET);
        return a;
    }

    vector c;

    c.magnitudes[0] = a.magnitudes[1]*b.magnitudes[2] - 
                      a.magnitudes[2]*b.magnitudes[1];

    c.magnitudes[1] = a.magnitudes[2]*b.magnitudes[0] -
                      a.magnitudes[0]*b.magnitudes[2];

    c.magnitudes[2] = a.magnitudes[0]*b.magnitudes[1] -
                      a.magnitudes[1]*b.magnitudes[0];

    strcpy(c.vecName, "ans");

    c.vecSize = 3;

    return c;
}