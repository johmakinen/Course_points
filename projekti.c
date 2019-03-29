#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projekti.h"

 void addStudent(const char *studentId, const char *name, Course *arr)
 {
    int size = arr -> numStudents;
    arr = realloc(arr,sizeof(Student)*(size+1)); // add one more place to the array

    for(int i = 0; i<6;i++){ //add 0 points to the student as starting condition
        arr -> students[size].points[i] = 0;
    }
        strcpy(arr -> students[size].studentName,name);
        strcpy(arr -> students[size].studentId,studentId);


        arr -> students[size+1].studentName[0] = '0';  //last student gets char 0 as name
        arr -> numStudents = size+1;



 }

 void addPoints(const char *studentId, int round, int points, Course *arr)
 {

    int size = arr -> numStudents;
    int i = 0;  //index of the student with the correct id
    int found = 0;
    while(!found && i < size){
        if(arr->students[i].studentId == studentId){  //found the right student
            found = 1;
            arr->students[i].points[round-1] = points; //add the round points for the student
        }
        i++;
    }


// void printStudents(Course *arr)
// {
//
//
//
//
// }



 }

