#ifndef PROJEKTI_H
#define PROJEKTI_H


struct student_st;
struct course_st;
typedef struct  student_st{

    char studentName[21]; //"Mallikas Mikko"'\0' name formatted as "lastName firstName"
    char studentId[7];  // "123456"'\0' "studentId"
    int points[6]; // 1,4,2,7,3,6 points in every exercise round
    int totalPoints;

}Student;

typedef struct course_st{

    Student *students; //array, where numStudents amount of students
    int numStudents;
}Course;

void addStudent(char *studentId,char *name, Course *arr);
void updatePoints(char *studentId, int round, int points, Course *arr);
void printStudents(Course *arr);
int compareNum(const void* a, const void* b);
void printStudents(Course *arr);
void writeToFile(char *file, Course *arr);
void readFromFile(char *file, Course *arr);


#endif // projekti.h
