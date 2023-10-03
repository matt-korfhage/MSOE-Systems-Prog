#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <regex.h>
#include "minimatcmd.h"


#define INPUT_BUFFER_SIZE 500

static minimatcmd minimatProcessCmd( char * cmdInput ) {
    // first use regex to parse input string for validity
}

static bool minimatRuntimeGrabInput( void ) {

    char inputBuffer[INPUT_BUFFER_SIZE];

    // Grab console input
    scanf("%s", inputBuffer);

    // Load arguments from input
    return minimatProcessCmd(inputBuffer);

}

static void minimatRuntimeExecute( void ) {
    
    bool exit;

    do {
        
    } while( !exit )

}

int main ( void ) {

    // Start the minimat runtime
    minimatRuntimeExecute();

}