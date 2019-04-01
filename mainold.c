#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projekti.h"

int main()
{

    Course *arr = malloc(sizeof(Course));       //initialise course
    arr -> students = malloc(sizeof(Student));   //initialise course with size of one student
    arr -> numStudents = 0;
    int done = 0;

    while(!done){

        char buffer[32];

        if(fgets(buffer, 32, stdin) == NULL){  // get line from stdin, raise errors
            fprintf(stderr, "Invalid input\n");
        }

        char token = buffer[0]; //initialise places for id, name, filename, token, round and points
        buffer[31] = '\n';
        char id[7];
        char name[21];
        char fileName[21];
        int round,points;
        switch(token){ //add student to the course
        case 'A':

            sscanf(buffer+2,"%6s %20[^\n]s",id,name);
            id[6] = '\0';
            name[20] = '\0';
            addStudent(id,name,arr);
            break;

        case 'U': //update student's points for a specific round

            sscanf(buffer+2,"%s %d %d",id,&round,&points);
            id[6] = '\0';
            updatePoints(id,round,points,arr);
            break;

        case 'L': //print all the students in this course
            printStudents(arr);
            break;

        case 'W':  //write the course points into a file

            sscanf(buffer+2,"%20s",fileName);
            fileName[20] = '\0';
            writeToFile(fileName,arr);
            break;

        case 'O':  //open course points from a file

            sscanf(buffer+2,"%20s",fileName);
            fileName[20] = '\0';
            readFromFile(fileName,arr);
            break;

        case 'Q':  //quit and free memory

            done = 1;
            free(arr -> students);
            free(arr);
            break;

        }
    }

    return 0;
}
