#include "search.h"
#include <string.h>
#include <stdio.h>

/**
 * @brief 按姓名搜索学生
 * @param name 要搜索的姓名
 * @return 找到的学生索引，未找到返回-1
 */
int search_by_name(const char *name) {
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].stu_name, name) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief 按学号搜索学生
 * @param id 要搜索的学号
 * @return 找到的学生索引，未找到返回-1
 */
int search_by_id(const char *id) {
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].stu_id, id) == 0) {
            return i;
        }
    }
    return -1;
}
