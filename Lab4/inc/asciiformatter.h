#ifndef ASCIIFORMATTER_H
#define ASCIIFORMATTER_H

#define NUM_ASCII_CHARACTERS 0x7F
#define TABLE_TOKEN_WIDTH    0x05
#define BITS_IN_BYTE         0x08
#define DEL                  127
#define NONPRINT_LOWER       0
#define NONPRINT_UPPER       32
#define MAX_NUM_TABLE_COLS   8

void printASCIITableCols( int numCols );

void printRadixes( char token );

#endif /* end of asciiformatter.h */