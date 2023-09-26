#ifndef INPUTPARSINGOPTIONS_H
#define INPUTPARSINGOPTIONS_H

#define DEFAULT_NUMBER_OF_TABLE_COLS 4
#define PARSING_ERROR_TERMINAL_MSG "Couldn't parse input from token. Check your input options! \n"
#define MAX_INPUT_LENGTH 500
#define MAX_APPEND_AMOUNT 10

typedef enum {

    PRINT_TABLE_DEFAULT,
    PRINT_TABLE_VARIABLE,
    PRINT_CHAR_RADIXES,
    PARSE_ERROR,

} PARSER_RESULT;

typedef struct {
    
    PARSER_RESULT parseResult;
    int numTableColsToPrint;
    char numToPrintForRadixes;
    char * badToken;

} PARSER_COMMAND_PKG;

#endif /* end of inputparsingoptions.h */