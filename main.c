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
        char *id = malloc(sizeof(char)*7);
        strncpy(id, buffer + 2, 6); //get id
        id = id+'\0';
        char name[21];
        strncpy(name,buffer+9,20); //get full name
        name[20] = '\0';
        switch(token){
        case 'A':

            addStudent(id,name,arr);
            break;

        case 'Q':
            done = 1;
            break;
        }
    }


}
