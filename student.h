#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_STUDENTS 45
#define NAME_LENGTH 32
#define ID_LENGTH 32

// 课程成绩结构体
typedef struct course {
    float ics;    // 计算机系统
    float pdp;    // 程序设计实践  
    float ds;     // 数据结构
    float dl;     // 数字逻辑
} COURSE;

// 学生信息结构体
typedef struct student {
    char stu_id[ID_LENGTH];     // 学号
    char stu_name[NAME_LENGTH]; // 姓名
    COURSE score;               // 各科成绩
} STUDENT;

// 全局学生数组和计数
extern STUDENT students[MAX_STUDENTS];
extern int student_count;

// 错误处理宏
#define HANDLE_ERROR(msg) do { \
    printf("Error %d: %s - %s\n", errno, strerror(errno), msg); \
} while(0)

void init_students();

#endif // STUDENT_H
