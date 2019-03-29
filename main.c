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
        char token = buffer[0];
        char id[7];
        char name[21];
        int round,points;
        switch(token){
        case 'A':

            sscanf(buffer+2,"%s %[^\n]s",id,name);
            //printf("id: %s, name: %s ok",id,name);
            id[6] = '\0';
            name[strlen(name)] = '\0';
            //printf("id: %s, name: %s ok",id,name);
            addStudent(id,name,arr);

            break;

        case 'U':

            sscanf(buffer+2,"%s %d %d",id,&round,&points);  //U 234567 1 7

            updatePoints(id,round,points,arr);
            break;
        case 'L':
            printStudents(arr);
            break;

        case 'Q':

            done = 1;
            //vapauta muistit
            break;
        }
    }

    return 0;
}
