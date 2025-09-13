#include "print.h"
#include <stdio.h>

/**
 * @brief 打印表头
 */
void print_header() {
    printf("%-20s %-15s %8s %8s %8s %8s %8s %8s\n", 
           "ID", "Name", "iCS", "PDP", "DS", "DL", "Total", "Average");
    printf("--------------------------------------------------------------------------------\n");
}

/**
 * @brief 打印单个学生信息
 * @param stu 学生指针
 */
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

/**
 * @brief 打印所有学生信息
 */
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
