//include <stdio.h> int main() { printf("🎭 Behold! The grand performance of Deadlock Detection begins! 🎭\n"); return 0; }
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#include "tools.h"
#include "admin.h"
int procFinished = 0;
bool deadLock = false;
bool safeAll = false;

int main(int argc, char *argv[])
{
    //Read File from argv[3]
    FILE *file;
    file = fopen(argv[3], "r");
    if (file == NULL)
    {
        printf("Error: File not found\n");
        return 1;
    }
    char line[256];
    
    //First line of the file - Total Resources
    fgets(line, sizeof(line), file);
    int resourcesN = c_to_i(line[0]);
    int (*ArrT) = malloc(sizeof(int[resourcesN]));
    int (*ArrA) = malloc(sizeof(int[resourcesN]));
    for (int i = 0; i < resourcesN; i++)
    {
        ArrT[i] = 0;
        ArrA[i] = 0;
    }

    //Second line of the file - Vector Total REsources
    int count = 0, i = 0;
    fgets(line, sizeof(line), file);
    while (count <= resourcesN){
        if(isdigit(line[i])) { //Checks if the character is a digit
            ArrT[count] =  ArrT[count] * 10 + c_to_i(line[i]); //Concatenates numbers if they are more than 1 digit
        }
        else{count++;} //Increments the count to move to the next index of the array if the character is not a digit
        i++;
    }
    //Third line of the file - Vector Available Resources
    count = 0, i = 0;
    fgets(line, sizeof(line), file);
    while (count <= resourcesN){
        if(isdigit(line[i])) { //Checks if the character is a digit
            ArrA[count] =  ArrA[count] * 10 + c_to_i(line[i]); //Concatenates numbers if they are more than 1 digit
        }
        else{count++;} //Increments the count to move to the next index of the array if the character is not a digit
        i++;
    }
    //Fourth line of the file - Total Processes
    fgets(line, sizeof(line), file);
    int procN = c_to_i(line[0]);

    int (*priority) = malloc(sizeof(int[resourcesN]));
    int (*finish) = malloc(sizeof(int[resourcesN]));
    int (*MatrixS)[resourcesN] = malloc(sizeof(int[procN][resourcesN]));
    int (*MatrixA)[resourcesN] = malloc(sizeof(int[procN][resourcesN]));
    for (int i = 0; i < procN; i++)
    {
        priority[i] = 0;
        finish[i] = 0;
        for (int j = 0; j < resourcesN; j++)
        {
            MatrixS[i][j] = 0;
            MatrixA[i][j] = 0;
        }
    }
    //procN's Lines of code
    for(int procIndex = 0; procIndex < procN; procIndex++){
        fgets(line, sizeof(line), file);
        count = 0, i = 0;
        while(count <= resourcesN*2+2){ //Takes in account the Available and Neccesary Resources plus the priority of the process and the bars in between all of them
            if(isdigit(line[i])) { //Checks if the character is a digit
                if(count <= resourcesN)
                {
                    MatrixA[procIndex][count] =  MatrixA[procIndex][count] * 10 + c_to_i(line[i]); //Concatenates numbers if they are more than 1 digit
                }
                else if(count > resourcesN && count <= resourcesN*2)
                {
                    MatrixS[procIndex][count-resourcesN-1] =  MatrixS[procIndex][count-resourcesN-1] * 10 + c_to_i(line[i]); //Concatenates numbers if they are more than 1 digit
                }
                else if(count > resourcesN*2)
                {
                    priority[procIndex] =  priority[procIndex] * 10 + c_to_i(line[i]); //Concatenates numbers if they are more than 1 digit
                }                
            }
            
            else{count++;} //Increments the count to move to the next index of the array if the character is not a digit
            i++;
        }
    }
    fclose(file);
    
    int (*terminated) = malloc(sizeof(int[procN]));
    for (int i = 0; i < procN; i++)
    {
        terminated[i] = 0;
    }

    int (*locked) = malloc(sizeof(int[procN]));
    while (safeAll == false)
    {
        bool hasChangedState = false;
        safeAll = true;
        /*Iterates through all the processes and checks
        if they are safe*/
        for (int i = 0; i < procN; i++)
        {   
            //Only Evaluate Unfinished Processes
            if(finish[i] <= 0){
                int s = isSafe(i, &ArrA[0], &MatrixA[0][0], &MatrixS[0][0], resourcesN, procFinished);
                //printf("S: %d\n", s);
                if(s>=1)
                {
                    procFinished = s;
                    hasChangedState = true;
                }
                else if (safeAll) {safeAll = false;}
                finish[i] = s;
            }

            
        }
        if(hasChangedState == false && !safeAll){
            //DEADLOCKED OCURRED
            printf("Interbloqueo detectado\n");
            printf("Procesos involucrados");
            int procCount = 0;
            for(int i = 0; i < procN; i++){
                if(finish[i] == -1){
                    locked[procCount] = i;
                    procCount++;
                    printf(" P%d", i);
                }
            }
            printf("\nRecursos disponibles");
            for(int i = 0; i < resourcesN; i++){
                printf(" %d", ArrA[i]);
            }
            printf("\n");
            if(procCount <= 1)
            {
                terminated[locked[0]] = 1;
                procFinished++;
                finish[locked[0]] = procFinished;
            }
            else
            {
                int choice;
                printf("a. Aleatorio\n");
                printf("p. Aborta el proceso con la prioridad mas baja\n");
                printf("n.Ingresa el numero de proceso a terminar\n");
                char option;
                scanf(" %c", &option);
                if (option == 'a') {
                    choice = rand() % procCount;
                    terminated[locked[choice]] = 1;
                    procFinished++;
                    finish[locked[choice]] = procFinished;
                    refillResources(choice, &MatrixA[0][0], &ArrA[0], resourcesN);
                } else if (option == 'p') {
                    int lowestPriority = 11;
                    int lowestPriorityIndex = 0;
                    for (int i = 0; i < procCount; i++) {
                        if (priority[locked[i]] < lowestPriority) {
                            lowestPriority = priority[locked[i]];
                            lowestPriorityIndex = locked[i];
                        }
                    }
                    terminated[lowestPriorityIndex] = 1;
                    procFinished++;
                    finish[lowestPriorityIndex] = procFinished;
                    refillResources(lowestPriorityIndex, &MatrixA[0][0], &ArrA[0], resourcesN);

                
                } else if (isdigit(option)) {
                    choice = option - '0';
                    if (choice >= 0 && choice < procN) {
                        terminated[choice] = 1;
                        procFinished++;
                        finish[choice] = procFinished;
                        refillResources(choice, &MatrixA[0][0], &ArrA[0], resourcesN);
                    } else {
                        printf("Numero de proceso invalido.\n");
                    }
                } else {
                    printf("Opción Inválida.\n");
                }
            }
        }
        
    }
    
    printStatus(&finish[0], procN, &terminated[0], deadLock);
    
    free(locked);
    free(MatrixS);
    free(MatrixA);
    free(priority);    
    free(ArrT);
    free(ArrA);
    return 0;
};
