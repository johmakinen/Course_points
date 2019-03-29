#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projekti.h"

int main()
{

    Course *arr = malloc(sizeof(Student));
    arr -> numStudents = 0;
    int done = 0;

    while(!done){
        char buffer[32];
        fgets(buffer,32,stdin);
        char token = buffer[0];  //command char
        char id[7];
        switch(token){
        case 'A':
            strncpy(id, buffer + 2, 6); //get id
            id[6] = '\0';
            char name[21];
            strncpy(name,buffer+9,20); //get full name
            name[20] = '\0';
            addStudent(id,name,arr);

            break;

        case 'U':
            strncpy(id, buffer + 2, 6); //get id
            id[6] = '\0';
            int round = buffer[9];
            int points = buffer[11];

            addPoints(id,round,points,arr);

        case 'Q':

            done = 1;
            //vapauta muistit
            break;
        }
    }


}
