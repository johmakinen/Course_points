#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projekti.h"



 void addStudent(char *studentId, char *name, Course *arr)
 {
    int size = arr -> numStudents;
    int curr = 0;
    while(curr < size){
        int equal = strcmp(arr->students[curr].studentId,studentId);
        if(!equal){
            printf("Sorry, can't add a student with an already existing studentID\n");
            return;
        }
        curr++;
    }

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
     if(round < 0){
        printf("There are no negative valued exercise rounds\n");
        return;
        }
    if(points < 0){
        printf("Exercise points for a round can't be negative\n");
        return;
        }

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
     int size = arr->numStudents;
     if(size < 1){
        printf("There are no students in this course\n");
        return;
     }
    //sort array by total points
    qsort(arr, arr->numStudents, sizeof(Student), compareNum);
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



void writeToFile(char *filename,Course *arr)
{
    FILE *f;
        f = fopen(filename,"wb");
        if(!f){
            fprintf(stderr, "Opening file failed\n");
            return;
        }
        int i = 0;
        while(i<arr->numStudents){
            fwrite(&(arr->students[i]),sizeof(Student),1,f);
            i++;
        }
        fclose(f);

        printf("Wrote file successfully!\n");


}

void readFromFile(char *filename, Course *arr)
{

    FILE *f;
    f = fopen(filename, "rb");

    if(!f){
        fprintf(stderr, "Opening file failed\n");
        return;
    }


    Course *temp = malloc(sizeof(Course));
    temp -> students = malloc(sizeof(Student));
    temp->numStudents = 0;
    int i = 0;
    while(i<arr->numStudents){
        temp->students = realloc(temp->students,sizeof(Student)*(i+1));
        fread(&(temp->students[i]),sizeof(Student),1,f);
        i++;
        }

    arr ->students = realloc(arr->students,sizeof(Student)*i);
    memcpy(arr->students,temp->students,i);
    arr ->numStudents = i;
    free(temp->students);
    free(temp);

    fclose(f);

    printf("Opened file successfully!\n");

}







