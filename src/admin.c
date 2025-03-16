#include "admin.h"
#include "tools.h"

#include <stdio.h>
#include <stdbool.h>

//Returns at what place the process finished and if not returns -1
int isSafe(int procIndex, int* work, int* matrixA, int* matrixS, int resources, int procFinished){
    bool safe = true;
    for (int i = 0; i < resources; i++)
    {
        //printf("S: %d, A: %d, W: %d\n",getV(matrixS, procIndex, i, resources),getV(matrixA, procIndex, i, resources),work[i]);
        if(getV(matrixS, procIndex, i, resources) - getV(matrixA, procIndex, i, resources) > work[i]){
            safe = false;
            break;
        }
    }
    if (safe)
    {
        refillResources(procIndex, matrixA, work, resources);
        procFinished++;
        return procFinished;    
    }
    return -1;
}

void refillResources(int procIndex, int*matrixA, int* work, int resources){
    for (int i = 0; i < resources; i++)
    {
        work[i] += getV(matrixA, procIndex, i, resources);
    }
}

