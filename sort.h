#ifndef SORT_H
#define SORT_H

#include "student.h"

// 排序选项枚举
typedef enum {
    SORT_BY_ICS,  // 按计算机系统成绩排序
    SORT_BY_PDP,  // 按程序设计实践成绩排序
    SORT_BY_DS,   // 按数据结构成绩排序
    SORT_BY_DL    // 按数字逻辑成绩排序
} SORT_OPTION;

/**
 * @brief 按指定科目成绩降序排序学生数组
 * @param option 排序选项
 */
void sort_students_by_course(SORT_OPTION option);

#endif // SORT_H
