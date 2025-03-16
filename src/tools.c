#include "tools.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

void printStatus(int* finish, int procN, int* terminated, bool deadLock) {
    if(!deadLock){
        printf("Es un estado seguro\n");
    }
    else{
        printf("Hubo un estado inseguro\n");
    }
    printf("Estado de los procesos:\n");
    for (int i = 0; i < procN; i++) {
        printf("P%d: %s\n", i, terminated[i] ? "Terminado" : "Finalizado");
    }
    printf("Orden de asignación de recursos:\n");
    for (int i = 0; i < procN; ++i) {
        int n = 0;
        for (int j = 0; j < procN; j++)
        {
            if(finish[n] > finish[j]){ 
                //Takes the earliest executed process
                n = j;
            }
        }
        printf("P%d%s%s", i, terminated[i] ? "" : " Terminado", i == procN - 1 ? "\n" : ", ");
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