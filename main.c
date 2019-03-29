#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main()
{

    Course arr = malloc(sizeof(Student));

    int done = 0;

    while(!done){
        char buffer[32];
        fgets(buffer,32,stdin);
        char token = buffer[0];  //command char
        char *id = malloc(sizeof(char)*7);
        strncpy(id, buffer + 2, 6); //get id
        id = id+'\0';
        char *name[20];
        strncpy(name,buffer+9,20); //get full name

        switch(token){
        case 'A':

            addStudent(id,name);


        }
    }


}
