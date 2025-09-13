#include "print.h"
#include "student.h"
#include "mySQL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_header() {
    printf("%-20s %-15s %8s %8s %8s %8s %8s %8s\n", 
           "ID", "Name", "iCS", "PDP", "DS", "DL", "Total", "Average");
    printf("--------------------------------------------------------------------------------\n");
}

void print_student(const STUDENT *stu) {
    float total = stu->score.ics + stu->score.pdp + stu->score.ds + stu->score.dl; 
    float average = total / 4.0f;  
    printf("%-20s %-15s %8.1f %8.1f %8.1f %8.1f %8.1f %8.1f\n", 
           stu->stu_id,
           stu->stu_name,
           stu->score.ics,
           stu->score.pdp,
           stu->score.ds,
           stu->score.dl,
           total,
           average);
}

void print_all_students() {
    if (student_count == 0) {
        printf("No students found.\n");
        return;
    }
    
    print_header();
    for (int i = 0; i < student_count; i++) {
        print_student(&students[i]);
    }
    printf("\n");
}

// ====== 新增函数：MYSQL_RES 查询结果打印 ======
void print_students_from_query(MYSQL_RES *res) {
    if (!res) {
        printf("No data to display.\n");
        return;
    }

    MYSQL_ROW row;
    int count = 0;

    // 遍历结果集，将每行数据存入 students 数组
    while ((row = mysql_fetch_row(res)) != NULL && count < MAX_STUDENTS) {
        strncpy(students[count].stu_id, row[0], ID_LENGTH);
        strncpy(students[count].stu_name, row[1], NAME_LENGTH);
        students[count].score.ics = atof(row[2]);
        students[count].score.pdp = atof(row[3]);
        students[count].score.ds  = atof(row[4]);
        students[count].score.dl  = atof(row[5]);
        count++;
    }

    student_count = count;

    // 使用已有打印函数显示学生信息
    print_all_students();

    // 释放结果集
    dbFreeResult(res);
}
