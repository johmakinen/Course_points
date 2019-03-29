#ifndef PROJEKTI_H
#define PROJEKTI_H

typedef struct {

    char *students; //array, where x amount of students

}Course;

typedef struct {

    char[21] name; //"Mallikas Mikko"'\0' name formatted as "lastName firstName"
    char[7] studentId;  // "123456"'\0' "studentId"
    int points[7]; // 1,4,2,7,3,6,'\0' points in every exercise round


}Student;


#endif // projekti.h
