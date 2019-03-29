#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projekti.h"

 void addStudent(char *studentId, char *name, Course *arr)
 {
    int size = arr -> numStudents;
    arr ->students = realloc(arr->students,sizeof(Student)*(size+1)); // add one more place to the array

    for(int i = 0; i<6;i++){ //add 0 points to the student as starting condition
        arr -> students[size].points[i] = 0;

    }
        arr -> students[size].totalPoints = 0;

        strcpy(arr -> students[size].studentName,name);
        strcpy(arr -> students[size].studentId,studentId);
        arr -> numStudents = size+1;



 }

 void updatePoints(char *studentId, int round, int points, Course *arr)
 {

    int size = arr -> numStudents;
    int i = 0;  //index of the student with the correct id
    int found = 0;
    while(!found && i < size){
        int equal = strcmp(arr->students[i].studentId,studentId);
        if(equal == 0){  //found the right student
            found = 1;
            arr->students[i].points[round-1] = points;//add the round points for the student
            int j, sum = 0;
                for (j=0; j<6; j++){ //calculate new total points:
                    sum = sum + arr->students[i].points[j];
                }
                printf("total: %d \n",sum);
            arr -> students[i].totalPoints = sum;
        }
        i++;
    }




    if(!found){
        printf("Student with ID: %s not found\n",studentId);
    }


 }

 int compareNum(const void* a, const void* b)
{
     const Student *aa = a;
     const Student *bb = b;

    if(aa->totalPoints > bb->totalPoints){
        return -1;
    }else{
    return 1;
    }

    return 0;
}

  void printStudents(Course *arr)
 {
    //sort array by total points
    qsort(arr, arr->numStudents, sizeof(Student), compareNum);
    int size = arr->numStudents;
    int i = 0;
    while(i < size){
        printf("| %s | %s | ",arr -> students[i].studentId,arr -> students[i].studentName);//id and name
        printf("Exercise points by round: |");
        for(int j = 0;j<6;j++){
            printf(" %d |",arr -> students[i].points[j]); //print points for each round
        }
        printf(" Total points: %d |\n",arr -> students[i].totalPoints);
        i++;
    }




 }

