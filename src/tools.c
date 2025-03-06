#include "tools.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

void printStatus(int* finish, int procN, int* terminated, bool deadLock) {
    if(!deadLock){
        printf("No se detectó interbloqueo\n");
    }
    printf("Procesos ejecutados:\n");
    for (int i = 0; i < procN; ++i) {
        int n = 0;
        for (int j = 0; j < procN; j++)
        {
            if(finish[n] > finish[j]){ //Takes the earliest executed process
                n = j;
            }
        }
        //Prints terminated or finalized if there was deadlock involved or not
        if (terminated[n] == 1)
        {
            printf("P%d Terminado\n", n);
        }
        else
        {
            printf("P%d Finalizado\n", n);
        }
        finish[n] = procN+1; //Set the value beyond the highest possible value
        
    }
}

int c_to_i(char c)
{
    return c - '0';
}

int getV(int *matrix, int i, int j, int n)
{
    return matrix[(i * n) + j];
}
void setV(int *matrix, int i, int j, int n, int v)
{
    matrix[(i * n) + j] = v;
}