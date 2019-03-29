#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projekti.h"

 int addStudent(const char *studentId, const char *name,Course *addToThis)
 {
    int size = addToThis -> numStudents;
    addToThis = realloc(addToThis,sizeof(Student)*(size+1)); // add one more place to the array

    for(int i = 0; i<6;i++){ //add 0 points to the student as starting condition
        addToThis -> students[size].points[i] = 0;
    }
        strcpy(addToThis -> students[size].studentName,name);
        strcpy(addToThis -> students[size].studentId,studentId);


        addToThis -> students[size+1].studentName[0] = '0';  //last student gets char 0 as name
        addToThis -> numStudents = size+1;


    return 0;
 }

