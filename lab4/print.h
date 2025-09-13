#ifndef PRINT_H
#define PRINT_H

#include "student.h"

/**
 * @brief 打印单个学生信息
 * @param stu 学生指针
 */
void print_student(const STUDENT *stu);

/**
 * @brief 打印所有学生信息
 */
void print_all_students();

/**
 * @brief 打印表头
 */
void print_header();

#endif // PRINT_H
