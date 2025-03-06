#ifndef TOOLS_C
#define TOOLS_C
#include <stdbool.h>

extern void printStatus(int* finish, int procN, int* terminated, bool deadLock);
extern int c_to_i(char c);
extern int getV(int *matrix, int i, int j, int n);
extern void setV(int *matrix, int i, int j, int n, int v);
#endif 
