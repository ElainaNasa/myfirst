#ifndef PRINT_H
#define PRINT_H

#include "student.h"
#include "mySQL.h"
#include <mysql/mysql.h>
#include <stdio.h>

// 打印表头
void print_header();

// 打印单个学生
void print_student(const STUDENT *stu);

// 打印所有学生（全局数组）
void print_all_students();

// ====== 新增函数：根据查询结果打印 ======
/**
 * @brief 将 MYSQL_RES 查询结果加载到 students 数组，并打印
 * @param res MySQL 查询结果集
 */
void print_students_from_query(MYSQL_RES *res);

#endif // PRINT_H
