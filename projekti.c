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
        f = fopen(filename,"wb+");
        if(!f){
            fprintf(stderr, "Opening file failed\n");
            return;
        }
        char space = ' ';
        //char line[] = "\n";
        int i = 0;
        while(i<arr->numStudents){
            fwrite(arr->students[i].studentId,sizeof(char)*7,1,f); //id
            fwrite(&space,sizeof(char),1, f);
            fwrite(arr->students[i].studentName,sizeof(char)*21,1,f); //name
            fwrite(&space,sizeof(char),1, f);

            for(int j = 0;j<6;j++){
                fwrite(&(arr->students[i].points[j]),sizeof(int),1,f);
                fwrite(&space,sizeof(char),1, f); //points with space between them for easier reading later
            }
            fwrite(&(arr->students[i].totalPoints),sizeof(int),1,f); //total points

            i++;
        }

    fclose(f);
}

void readFromFile(char *filename, Course *arr)
{

    FILE *f;
    f = fopen(filename, "rb");

    if(!f){
        fprintf(stderr, "Opening file failed\n");
        return;
    }
    free(arr -> students);  //delete old data
    free(arr);

    arr = malloc(sizeof(Course));
    arr->students = malloc(sizeof(Student));  //restart coursearray
    arr->numStudents = 0;
    char *space = malloc(2*sizeof(char));
    int i = 0;
    char buffer[7];

    while (fread(buffer,sizeof(char)*7,1,f) == 1) {
        arr->students = realloc(arr->students,sizeof(Student)*(i+1));
        strcpy(arr->students[i].studentId,buffer);
        fread(space,sizeof(char),1,f);
        fread(arr->students[i].studentName,sizeof(char)*21,1,f);
        fread(space,sizeof(char),1,f);


        for(int j = 0;j<6;j++){
                fread(&(arr->students[i].points[j]),sizeof(int),1,f);
                fread(&space,sizeof(char),1, f);//points with space between them for easier reading later
            }

        fwrite(&(arr->students[i].totalPoints),sizeof(int),1,f);
        i++;
    }
    i--;
    arr->numStudents = i;
    fclose(f);


}



//  void writeToFile(char *file, Course *arr)
//  {
//    char *name = strcat(file,".txt");  //force outputfile to be txt
//
//    FILE *f = fopen(name,"w");
//    if (!f) { //did the file opening succeed?
//        fprintf(stderr, "Opening file failed\n");
//        return;
//    }
//
//    qsort(arr, arr->numStudents, sizeof(Student), compareNum);
//
//    int size = arr->numStudents;
//    int i = 0;
//    while(i < size){
//        fputs(arr -> students[i].studentId, f);
//        fputs(" ",f);
//        fputs(arr -> students[i].studentName, f);
//        fputs(" ",f);
//
//        for(int j = 0;j<6;j++){
//            fprintf(f,"%d",arr -> students[i].points[j]);
//             fputs(" ",f);
//        }
//
//        fputs(" Total points: ", f);
//        fprintf(f,"%d",arr -> students[i].totalPoints);
//        fputc('\n',f);
//        i++;
//    }
//
//    fclose(f);
//
//  }


// void readFromFile(char *file)
// {
//    int lines = line_count(name);
//
//
//
//
//
//
// }




