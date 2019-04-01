#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projekti.h"



 void addStudent(char *studentId, char *name, Course *arr)
 {
    int size = arr -> numStudents;
    int curr = 0;
    while(curr < size){  //check if trying to add a student with ID that is already in the course
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

        printf("Added student successfully!\n");



 }

 void updatePoints(char *studentId, int round, int points, Course *arr)
 {
     if(round < 1){
        printf("There are no non-positive valued exercise rounds\n");
        return;
        }

    if(round > 6){
        printf("There are only six exercise rounds\n");
        return;
    }
//    if(points < 0){
//        printf("Exercise points for a round can't be negative\n");
//        return;
//        }

    if(points > 32766){
        printf("Too large of a number, try something smaller\n");
        return;
    }

    int i = 0;  //index of the student with the correct id
    int found = 0;
    int size = arr->numStudents;
    while(!found && i<size){
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
        return;
    }
    printf("Updated points successfully!\n");


 }

 int compareNum(const void* a, const void* b)
{
    //compare function for qsort when printing the students. Sort by points, if equal points, sort by studentId
     const Student *aa = a;
     const Student *bb = b;
    if(aa->totalPoints == bb->totalPoints){
        return strcmp(aa->studentId,bb->studentId);
    }

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
    //sort array by total points or id
    qsort(arr->students, size, sizeof(Student), compareNum);
    int i = 0;
    printf("| StudentID | Name of the student || Points by round ||\n");
    printf("------------------------------------------------------------------------\n");
    while(i<size){
        printf("| %s | %s ",arr -> students[i].studentId,arr -> students[i].studentName);//id and name

        int c = 0;
        while(c < 20-strlen(arr -> students[i].studentName)){
                printf(" ");
                c++;
        }
        printf("||");
        for(int j = 0;j<6;j++){
            printf(" %d |",arr -> students[i].points[j]); //print points for each round
        }
        printf("| Total points: %d |\n",arr -> students[i].totalPoints);
        i++;
    }
    printf("Number of students in the list: %d\n",arr->numStudents);

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
        int t;
        while(i<arr->numStudents){
            t = fwrite(&(arr->students[i]),sizeof(Student),1,f);
            if(t == 0){
                printf("Error writing the file");
                fclose(f);
                return;
            }
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


    Student *students = malloc(sizeof(Student));  //initialise temporary array for students
    int i = 0;
    while(fread(&students[i],sizeof(Student),1,f)){  // read students from the file to the temporary array

            students = realloc(students,(i+2)*sizeof(Student));
            i++;
        }

    arr ->students = realloc(arr->students,sizeof(Student)*i);  //alloc more (or less) space to the current array
    int k = 0;
    while(k<i){
        memcpy(&(arr->students[k]),&students[k],sizeof(Student));  //copy the temporary student array into the current array
        k++;
    }
    arr ->numStudents = i;
    free(students);
    fclose(f);

    printf("Opened file successfully!\n");


}







