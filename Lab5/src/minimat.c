/**
 * @file minimat.c
 * @brief Runs the minimat runtime and parser
 * 
 * Course: CPE2600
 * Section: 011
 * Assignment: Lab 5 - Vector Lab
 * Name: Matt Korfhage
 * 
 * Algorithm:
 *  - Retrieve command arguments in loop
 *    - Parse arguments and enumerate them based on operation
 *  - Execute command using vector library
 *  - Print the results to console
 */

#include "minimatcmd.h"
#include "termcolors.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#define INPUT_BUFFER_SIZE 100


static vector createVectorFromConsole(char * head) {
    vector result;
    
    volatile char * token;
    token = strtok(head, " ");
    strcpy(result.vecName, (char *) token); // Copy over name

    int dimensionCounter = 0; // Counter for number of vector dimensions

    token = strtok(NULL, " "); // Parse equals sign
    token = strtok(NULL, " "); // Parse first floating point token

    char vectorName[50];

    // If assigning to other vector then short circuit
    sscanf((char *)token, "%s", vectorName);
    vector toLookFor;
    strcpy(toLookFor.vecName, vectorName);

    if( grabVector(&toLookFor) ) { // Look for if vector exists
        
        // assign properties of vector to result (copy all but name)
        copyVectorKeepName(&toLookFor, &result);

        return result;
    }

    while( token != NULL ) {

        if(sscanf(( char * )token, "%lf", &result.magnitudes[dimensionCounter]) == 1) {
            ++dimensionCounter;
        } else {
            break;
        }

        token = strtok(NULL, " "); // parse next floating point token
    }

    // Fill in number of dimensions the vector is
    result.vecSize = dimensionCounter;

    return result;
}


static minimatcmd gatherOperandsOperation(char * head, char operation) {
    minimatcmd cmd;
    
    char * token = strtok(head, " ");

    // Copy name of first operand vector
    strcpy((char *) &cmd.operands[0].vecName, token);
    token = strtok(NULL, " ");

    // Check for formatting
    if( *token != operation ) {
        cmd.operation = CMD_ERROR;
        return cmd;
    }

    // Copy name of second operand vector
    token = strtok(NULL, " ");
    strcpy((char *)&cmd.operands[1].vecName, token);

    if( sscanf(cmd.operands[1].vecName, "%lf", &cmd.scalar) == 1 ) {
        cmd.operation = SCALARMUL;
    } else {
        cmd.operation = DOTPROD;
    }

    return cmd;
}


static minimatcmd minimatProcessCmd( char * cmdInput ) {

    minimatcmd cmd;
    cmd.operation = CMD_ERROR;

    // Vector creation
    char *equal_sign = strchr(cmdInput, DATA_CREATE_SYMBOL);
    if( equal_sign != NULL ) {
        cmd.operands[0] = createVectorFromConsole(cmdInput);
        cmd.operation = DATA_CREATE;
        return cmd;
    }

    // Vector addition
    char *add_sign = strchr(cmdInput, ADD_SYMBOL);
    if( add_sign != NULL ) {
        cmd = gatherOperandsOperation(cmdInput, ADD_SYMBOL);
        cmd.operation = ADD;
        return cmd;
    }

    // Vector subtraction
    char *sub_sign = strchr(cmdInput, SUB_SYMBOL);
    if( sub_sign != NULL ) {
        cmd = gatherOperandsOperation(cmdInput, SUB_SYMBOL);
        cmd.operation = SUB;
        return cmd;
    }

    // Vector multiplication
    char *mul_sign = strchr(cmdInput, DOTPROD_SYMBOL);
    if( mul_sign != NULL ) {
        cmd = gatherOperandsOperation(cmdInput, DOTPROD_SYMBOL);
        return cmd;
    }

    // Vector cross product
    char * crossprod_sign = strchr(cmdInput, XPROD_SYMBOL);
    if( crossprod_sign != NULL ) {
        cmd = gatherOperandsOperation(cmdInput, XPROD_SYMBOL);
        cmd.operation = XPROD;
        return cmd;
    }

    // Clear vector table
    if( strcmp(cmdInput, "clear") == 0 ) {
        cmd.operation = CLEAR;
        return cmd;
    }

    return cmd;
}


static void minimatExecuteCmd( minimatcmd cmd ) {

    volatile vector ans; // result vector

    // based on the operation of the command call the function
    switch(cmd.operation) {

        case DATA_CREATE:
            addVectorToMemoryList(cmd.operands[0]);
            printVector(cmd.operands[0]);
            break;

        case ADD:
            ans = add(cmd.operands[0], cmd.operands[1]);
            addVectorToMemoryList(ans);
            printVector(ans);
            break;

        case SUB:
            ans = sub(cmd.operands[0], cmd.operands[1]);
            addVectorToMemoryList(ans);
            printVector(ans);
            break;

        case DOTPROD:
            ans = dotprod(cmd.operands[0], cmd.operands[1]);
            addVectorToMemoryList(ans);
            printVector(ans);
            break;

        case SCALARMUL:
            ans = scalarmul(cmd.operands[0], cmd.scalar);
            addVectorToMemoryList(ans);
            printVector(ans);
            break;

        case XPROD:
            ans = xprod(cmd.operands[0], cmd.operands[1]);
            addVectorToMemoryList(ans);
            printVector(ans);
            break;

        case CLEAR:
            clearVectors();
            puts(ANSI_COLOR_GREEN "Vector memory has been cleared" ANSI_COLOR_RESET);
            break;

        default:
            puts(ANSI_COLOR_RED "ERROR: That command is not supported" ANSI_COLOR_RESET);
            break;
    }

}


bool minimatExecutionLoop( void ) {
    
    char inputBuffer[INPUT_BUFFER_SIZE];

    // grab entire line of input from console
    fgets(inputBuffer, sizeof(inputBuffer), stdin);

    // remove trailing newline character to prevent bugs
    inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

    // if exit command issued then exit control loop
    if( strcmp(inputBuffer, EXIT_SYMBOL) == 0 ) {
        return false;
    }

    // get command details from console input
    minimatcmd cmd = minimatProcessCmd(&inputBuffer[0]);

    // Execute command based on details
    minimatExecuteCmd(cmd);

    return true;
}


int main ( void ) {

    while ( minimatExecutionLoop() ) { /* Nothing here */ }
    
    puts(ANSI_COLOR_CYAN "Exiting..." ANSI_COLOR_RESET);

    return 0;
}