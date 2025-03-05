//include <stdio.h> int main() { printf("🎭 Behold! The grand performance of Deadlock Detection begins! 🎭\n"); return 0; }
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

int procFinished = 0;

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

int isSafe(int procIndex, int* work, int* matrixA, int* matrixS, int resources){
    for (int i = 0; i < resources; i++)
    {
        if(getV(matrixS, procIndex, i, resources) - getV(matrixA, procIndex, i, resources) > work[i]){
            return false;
        }
        
    }
    for (int i = 0; i < resources; i++)
    {
        work[i] += getV(matrixA, procIndex, i, resources);
    }
    procFinished++;
    return procFinished;    
}



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

    printf("---MatrixA ---\n");
    for(int i = 0; i < procN; i++){
        for(int j = 0; j < resourcesN; j++){
            printf("%d ", MatrixA[i][j]);
        }
        printf("\n");
    }
    printf("---MatrixS ---\n");
    for(int i = 0; i < procN; i++){
        for(int j = 0; j < resourcesN; j++){
            printf("%d ", MatrixS[i][j]);
        }
        printf("\n");
    }

    printf("---Priority ---\n");
    printf("[ ");
    for(int i = 0; i < procN; i++){
        printf("%d ", priority[i]);
    }
    printf("]\n");

    printf("---Total Resources ---\n");
    printf("[ ");
    for(int i = 0; i < resourcesN; i++){
        printf("%d ", ArrT[i]);
    }
    printf("]\n");

    printf("---Available Resources ---\n");
    printf("[ ");
    for(int i = 0; i < resourcesN; i++){
        printf("%d ", ArrA[i]);
    }
    printf("]\n");
    
    for (int i = 0; i < procN; i++)
    {
        finish[i] = isSafe(i, &ArrA[0], &MatrixA[0][0], &MatrixS[0][0], resourcesN);
    }

    printf("---Finish Proccess ---\n");
    printf("[ ");
    for(int i = 0; i < procN; i++){
        printf("%d ", finish[i]);
    }
    printf("]\n");

    free(MatrixS);
    free(MatrixA);
    free(priority);    
    free(ArrT);
    free(ArrA);
    return 0;
};
