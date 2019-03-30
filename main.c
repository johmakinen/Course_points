#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projekti.h"

int main()
{

    Course *arr = malloc(sizeof(Course));
    arr -> students = malloc(sizeof(Student));
    arr->students[0].studentName[0] = '\0';
    arr -> numStudents = 0;
    int done = 0;

    while(!done){

        char buffer[32];

        if(fgets(buffer, 32, stdin) == NULL){
            fprintf(stderr, "Invalid input\n");
        }

        char token = buffer[0];
        buffer[31] = '\n';
        char id[7];
        char name[21];
        char fileName[21];
        int round,points;
        switch(token){
        case 'A':

            sscanf(buffer+2,"%6s %20[^\n]s",id,name);
            id[6] = '\0';
            name[20] = '\0';
            addStudent(id,name,arr);
            break;

        case 'U':

            sscanf(buffer+2,"%s %d %d",id,&round,&points);
            id[6] = '\0';
            updatePoints(id,round,points,arr);
            break;

        case 'L':
            printStudents(arr);
            break;

        case 'W':

            sscanf(buffer+2,"%20s",fileName);
            fileName[20] = '\0';
            writeToFile(fileName,arr);
            break;
        case 'O':

            sscanf(buffer+2,"%20s",fileName);
            fileName[20] = '\0';
            readFromFile(fileName,arr);
            break;
        case 'Q':

            done = 1;
            free(arr -> students);
            free(arr);
            break;

        }
    }

    return 0;
}
