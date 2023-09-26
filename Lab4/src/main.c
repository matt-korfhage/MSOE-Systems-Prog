/**
 * @file main.c
 * @brief This file is the main entry point for program execution. It parses command line input
 * and prints a series of ASCII tables / ASCII representation based on the input from
 * the commands line.
 * 
 * Course: CPE2600
 * Section: 011
 * Assignment: Lab 4 - Printing to the Console
 * Name: Matthew Korfhage
 * 
 * Algorithm:
 *  - Retrieve the token from the command line arguments
 *    - Ensure the token is valid
 *  - Based on input options choose between printing radixes of token or printing table
 *  - Print specified ouput to console
 *  -

 *  -
 */

#include "asciiformatter.h"
#include "inputparsingoptions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Parses program input from command console
 * @param numTokens The number of inputs
 * @param tokenArray Buffer where inputs are held
 * @return Parser result with packaged info to feed to switch statement
 * @return PARSE_ERROR if input is invalid.
 */
static PARSER_COMMAND_PKG parseInput( int numTokens, char *tokenArray[] ) {

    PARSER_COMMAND_PKG result;
    result.parseResult = PARSE_ERROR;

    if( numTokens == 1 ) { // Default case no args
        result.parseResult = PRINT_TABLE_DEFAULT;
        result.numTableColsToPrint = DEFAULT_NUMBER_OF_TABLE_COLS;
    } else if( strcmp( tokenArray[1], "-c" ) == 0 && numTokens == 3) { // -c option
        result.numTableColsToPrint = atoi( tokenArray[2] );
        result.parseResult = result.numTableColsToPrint <= MAX_NUM_TABLE_COLS ? PRINT_TABLE_VARIABLE : PARSE_ERROR;
    } else if ( numTokens == 2) { // Random char input
        result.parseResult = PRINT_CHAR_RADIXES;
        result.numToPrintForRadixes = *tokenArray[1];
    }

    return result;
}

/**
 * @brief Prints error message from parser
 */
static void printParsingArgsError( void ) {
    puts(PARSING_ERROR_TERMINAL_MSG);
}


int main( int argc, char *argv[] ) {

    PARSER_COMMAND_PKG parseData = parseInput(argc, argv);

    // State machine based on parse result
    switch( parseData.parseResult ) {
        
        case PRINT_TABLE_DEFAULT:
            puts("Default input");
            printASCIITableCols(DEFAULT_NUMBER_OF_TABLE_COLS);
            break;

        case PRINT_TABLE_VARIABLE:
            printf("Print variable table with %d cols \n", parseData.numTableColsToPrint);
            printASCIITableCols(parseData.numTableColsToPrint);
            break;

        case PRINT_CHAR_RADIXES:
            printf("Print all radixes of char: %c \n", parseData.numToPrintForRadixes);
            printRadixes(parseData.numToPrintForRadixes);
            break;
        
        case PARSE_ERROR:
            // Program execution shouldn't reach this point 
            printParsingArgsError();
            return -1;
            
    }

    return 0;
}