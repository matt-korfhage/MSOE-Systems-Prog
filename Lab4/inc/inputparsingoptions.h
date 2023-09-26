#ifndef INPUTPARSINGOPTIONS_H
#define INPUTPARSINGOPTIONS_H

#define DEFAULT_NUMBER_OF_TABLE_COLS 4
#define PARSING_ERROR_TERMINAL_MSG "Couldn't parse input from token. Check your input options! \n"
#define MAX_INPUT_LENGTH 500
#define MAX_APPEND_AMOUNT 10

/**
 * @brief Different results from parser to generate a result based on command lne input
 */
typedef enum {

    PRINT_TABLE_DEFAULT,
    PRINT_TABLE_VARIABLE,
    PRINT_CHAR_RADIXES,
    PARSE_ERROR,

} PARSER_RESULT;

/**
 * @brief Struct that holds all possible data values and parsing results
 * @property parseResult - the result of the parsing process
 * @property numTableColsToPrint - number of columns in the ASCII table to print
 * @property badToken - the most recently parsed input taken that threw an error
 */
typedef struct {
    
    PARSER_RESULT parseResult;
    int numTableColsToPrint;
    char numToPrintForRadixes;
    char * badToken;

} PARSER_COMMAND_PKG;

#endif /* end of inputparsingoptions.h */