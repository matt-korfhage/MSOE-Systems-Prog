#ifndef MINIMATCMD_H
#define MINIMATCMD_H

#include "vector.h"

#define MAX_NUM_OPERANDS 2
#define DATA_CREATE_REGEX 
#define ADD_REGEX
#define SUB_REGEX
#define FOTPROD_REGEX
#define XPROD_REGEX
#define SCALARMUL_REGEX


typedef enum {

    DATA_CREATE,
    ADD,
    SUB,
    DOTPROD,
    XPROD,
    SCALARMUL

} minimatcmdType;

typedef struct {
    minimatcmdType operation;
    vector operands[MAX_NUM_OPERANDS];

} minimatcmd;


#endif /* end of minimatcmd.h */