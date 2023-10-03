#ifndef MINIMATCMD_H
#define MINIMATCMD_H

#include "vector.h"

#define MAX_NUM_OPERANDS 2
#define DATA_CREATE_SYMBOL '='
#define ADD_SYMBOL '+'
#define SUB_SYMBOL '-'
#define DOTPROD_SYMBOL '*'
#define XPROD_SYMBOL 'x'
#define SCALARMUL_SYMBOL '*'
#define EXIT_SYMBOL "exit"


typedef enum {

    DATA_CREATE,
    ADD,
    SUB,
    DOTPROD,
    XPROD,
    SCALARMUL,
    CLEAR,
    CMD_ERROR

} minimatcmdType;

typedef struct {
    minimatcmdType operation;
    vector operands[MAX_NUM_OPERANDS];
    double scalar;

} minimatcmd;


#endif /* end of minimatcmd.h */