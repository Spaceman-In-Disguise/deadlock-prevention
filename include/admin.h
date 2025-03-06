#ifndef ADMIN_C
#define ADMIN_C

extern int isSafe(int procIndex, int* work, int* matrixA, int* matrixS, int resources, int procFinished);

extern void refillResources(int procIndex, int*matrixA, int* work, int resources);

#endif 