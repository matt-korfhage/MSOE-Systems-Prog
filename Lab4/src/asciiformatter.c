/**
 * @file asciiformatter.c
 * @brief This file is the library for printing ASCII tables based on
 * a specific amount of columns or based on the input of a character
 * token, printing out the multiple representations of the token.
 * 
 * Course: CPE2600
 * Section: 011
 * Assignment: Lab 4 - Printing to the Console
 * Name: Matthew Korfhage
 */


#include "asciiformatter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>


static const char *controlMnemonics[] = {
    "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL", "BS", "TAB", "LF", "VT", "FF", "CR", "SO", "SI",
    "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN", "EM", "SUB", "ESC", "FS", "GS", "RS", "US"
};

/**
 * @brief Converts non-printable ASCII characters to their mnemonic values
 * @param token Non-printable ASCII character to get mnemonic from
 * @param mnemonic output buffer for mnemonic string to be stored
 */
static void getMnemonicPrintable( char token, char * mnemonic ) {

    // Check if token is a non-printable ASCII character. If yes store mnemonic.
    if ( ( uint8_t ) token >= NONPRINT_LOWER && ( uint8_t ) token < NONPRINT_UPPER ) {

        strcpy(mnemonic, controlMnemonics[( uint8_t ) token] );

    } else if (token == DEL) {

        // Del is special case here
        strcpy(mnemonic, "DEL");

    } 
}

/**
 * @brief Converts non-printable ASCII characters to their binary values
 * @param token Non-printable ASCII character to get binary of
 * @param mnemonic output buffer for binary string to be stored
 */
static void getBinaryRep( char token, char binaryRep[BITS_IN_BYTE] ) {

    // Extract binary rep by grabbing each bitwise section of number
    for( int i = 0; i < BITS_IN_BYTE; ++i ) {

        volatile bool bit = ( bool ) ( token & ( 0x1 << (BITS_IN_BYTE - 1 - i) ) );

        sprintf(&binaryRep[i], "%s", bit ? "1" : "0");

    }

}

/**
 * @brief Prints a standard ASCII table with decimal, hex, and mnemonic symbols
 * @param numCols number of columns in the table to print
 */
void printASCIITableCols( int numCols ) {
    
    // Write headers for tables with columns
    for( int i = 0; i < numCols; ++i ) {
        printf("%*s %*s %*s", TABLE_TOKEN_WIDTH, "Dec", TABLE_TOKEN_WIDTH, "Hex", TABLE_TOKEN_WIDTH, "Sym");
    }

    // This here for if uneven table with leftover values
    int leftoverSymbols = NUM_ASCII_CHARACTERS % numCols;

    // Print each row
    for( int i = 0; i < NUM_ASCII_CHARACTERS / numCols; ++i ) {
        
        printf("\n"); 

        // Print all the columns in each row
        for( int j = 0; j < numCols; ++j ) {

            volatile char toPrint = ( char ) ( j * ( NUM_ASCII_CHARACTERS / numCols ) + i );

            volatile char mnemonic[3] = {0};

            getMnemonicPrintable(toPrint, mnemonic);

            // Print representation of each type of ASCII character
            if( mnemonic[0] == 0 ) {
                printf("%*d %#*x %*c", TABLE_TOKEN_WIDTH, toPrint, \
                TABLE_TOKEN_WIDTH, toPrint, TABLE_TOKEN_WIDTH, toPrint);
            } else {
                printf("%*d %#*x %*s", TABLE_TOKEN_WIDTH, toPrint, \
                TABLE_TOKEN_WIDTH, toPrint, TABLE_TOKEN_WIDTH, mnemonic);
            }

        }

    }

    printf("\n");

    // Grab leftover symbols that didnt fit in table and print them in last column
    for(int i = leftoverSymbols; i >= 0; --i) {
            
        volatile char toPrint = NUM_ASCII_CHARACTERS - i;

        volatile char mnemonic[3] = {0};

        getMnemonicPrintable(toPrint, mnemonic);

        if( mnemonic[0] == 0 ) {
            printf("%*d %#*x %*c", TABLE_TOKEN_WIDTH, toPrint, \
            TABLE_TOKEN_WIDTH, toPrint, TABLE_TOKEN_WIDTH, toPrint);
        } else {
            printf("%*d %#*x %*s", TABLE_TOKEN_WIDTH, toPrint, \
            TABLE_TOKEN_WIDTH, toPrint, TABLE_TOKEN_WIDTH, mnemonic);
        }
    }

    printf("\n");
    
}

/**
 * @brief Prints decimal, hex, and binary rep of character to std output
 * @param token character to print
 */
void printRadixes( char token ) {

    char binaryRep[BITS_IN_BYTE];
    getBinaryRep(token, binaryRep);
    
    printf("%d %#x %s \n", ( int ) token, ( int ) token, binaryRep);
    
}
