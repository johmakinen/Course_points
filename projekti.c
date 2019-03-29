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
        arr -> students[size].totalPoints = 0;
    }


        strcpy(arr -> students[size].studentName,name);
//        printf("tämä\n");
//        printf("name: %s",arr -> students[size].studentName);
        strcpy(arr -> students[size].studentId,studentId);


        arr -> students[size+1].studentName[0] = '0'; //last student gets char 0 as name
        arr -> students[size+1].totalPoints = -1;
        arr -> numStudents = size+1;



 }

 void updatePoints(const char *studentId, int round, int points, Course *arr)
 {

    int size = arr -> numStudents;
    int i = 0;  //index of the student with the correct id
    int found = 0;
    while(!found && i < size){
        if(arr->students[i].studentId == studentId){  //found the right student
            found = 1;
            arr->students[i].points[round-1] = points;//add the round points for the student
            int j, sum = 0;
                for (j=0; j<6; j++){ //calculate new total points:
                    sum = sum + arr->students[j].points[j];
                }
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
        printf("%s %s ",arr -> students[i].studentId,arr -> students[i].studentName); //id and name
        for(int j = 0;i<6;j++){
            printf("%d",arr -> students[i].points[j]); //print points for each round
        }
        printf(" Total points: %d\n",arr -> students[i].totalPoints);
    }




 }

