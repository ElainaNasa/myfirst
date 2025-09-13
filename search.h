#ifndef SEARCH_H
#define SEARCH_H

#include "student.h"

/**
 * @brief 按姓名搜索学生
 * @param name 要搜索的姓名
 * @return 找到的学生索引，未找到返回-1
 */
int search_by_name(const char *name);

/**
 * @brief 按学号搜索学生
 * @param id 要搜索的学号
 * @return 找到的学生索引，未找到返回-1
 */
int search_by_id(const char *id);

#endif // SEARCH_H
