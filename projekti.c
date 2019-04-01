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

    arr ->students = realloc(arr->students,sizeof(Student)*(size+2)); // add one more place to the array

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

        int *p = arr->students[i].points;

        printf("| %-6s | %-20s || %d | %d | %d | %d | %d | %d || Total points: %d |\n",
               arr->students[i].studentId,arr->students[i].studentName
               ,p[0],p[1],p[2],p[3],p[4],p[5],arr->students[i].totalPoints);
        i++;
    }

    printf("Number of students in the list: %d\n",arr->numStudents);

 }



void writeToFile(char *filename,Course *arr)
{
    FILE *f;
        f = fopen(filename,"w");
        if(!f){
            fprintf(stderr, "Opening file failed\n");
            return;
        }
        int i = 0;
        while(i<arr->numStudents){

             fprintf(f, "%-6s %-20s %d %d %d %d %d %d %d\n",arr->students[i].studentId,arr->students[i].studentName
                     ,arr->students[i].points[0],arr->students[i].points[1]
                     ,arr->students[i].points[2],arr->students[i].points[3]
                     ,arr->students[i].points[4],arr->students[i].points[5]
                     ,arr->students[i].totalPoints);

            i++;

        }

        fclose(f);

        printf("Wrote file successfully!\n");


}

void readFromFile(char *filename, Course *arr)
{

    FILE *f;
    f = fopen(filename, "r");

    if(!f){
        fprintf(stderr, "Opening file failed\n");
        return;
    }


    Student *students = malloc(sizeof(Student));//initialise temporary array for students
    char get[100];
    int i = 0;

    while(fgets(get, 100, f)){  // read students from the file to the temporary array
            char first[21];
            char last[21];
            students = realloc(students,(i+2)*sizeof(Student));
            sscanf(get, "%s %s %s %d %d %d %d %d %d %d",students[i].studentId,last,first,&students[i].points[0]
                     ,&students[i].points[1],&students[i].points[2],&students[i].points[3],&students[i].points[4]
                     ,&students[i].points[5],&students[i].totalPoints);
            strcat(last," ");
            strncat(last,first,21);
            strcpy(students[i].studentName,last);
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



int main()
{

    Course *arr = malloc(sizeof(Course));
    Student *stud = malloc(sizeof(Student));
    arr -> students = stud;   //initialise course with size of one student
    arr -> numStudents = 0;
    int done = 0;

    while(!done){

        char buffer[32];
        char token;
        if(fgets(buffer, 32, stdin) == NULL){  // get line from stdin, raise errors
            fprintf(stderr, "End of file reached\n");
            token = 'Q';
        }else{
            token = buffer[0];
        }

         //initialise places for id, name, filename, token, round and points
        buffer[31] = '\n';
        char id[7];
        char name[21];
        char fileName[21];
        int round,points;
        switch(token){ //add student to the course
        case 'A':

            sscanf(buffer+2,"%6s %20[^\n]s",id,name);
            addStudent(id,name,arr);
            break;

        case 'U': //update student's points for a specific round

            sscanf(buffer+2,"%s %d %d",id,&round,&points);
            updatePoints(id,round,points,arr);
            break;

        case 'L': //print all the students in this course
            printStudents(arr);
            break;

        case 'W':  //write the course points into a file

            sscanf(buffer+2,"%20s",fileName);
            writeToFile(fileName,arr);
            break;

        case 'O':  //open course points from a file

            sscanf(buffer+2,"%20s",fileName);
            readFromFile(fileName,arr);
            break;

        case 'Q':  //quit and free memory

            done = 1;
            free(arr -> students);
            free(arr);
            break;

        default:
            printf("Invalid input\n");
            break;

        }
    }

    return 0;
}




