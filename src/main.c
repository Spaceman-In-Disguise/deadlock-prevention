//include <stdio.h> int main() { printf("🎭 Behold! The grand performance of Deadlock Detection begins! 🎭\n"); return 0; }
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int c_to_i(char c)
{
    return c - '0';
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
    int (*MatrixS)[resourcesN] = malloc(sizeof(int[procN][resourcesN]));
    int (*MatrixA)[resourcesN] = malloc(sizeof(int[procN][resourcesN]));
    for (int i = 0; i < procN; i++)
    {
        priority[i] = 0;
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


    

    free(MatrixS);
    free(MatrixA);
    free(ArrT);
    free(ArrA);
    return 0;
};
