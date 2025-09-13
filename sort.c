#include "sort.h"
#include <string.h>

// 比较函数 - 按计算机系统成绩
int compare_ics(const void *a, const void *b) {
    const STUDENT *stu1 = (const STUDENT *)a;
    const STUDENT *stu2 = (const STUDENT *)b;
    if (stu2->score.ics > stu1->score.ics) return 1;
    if (stu2->score.ics < stu1->score.ics) return -1;
    return 0;
}

// 比较函数 - 按程序设计实践成绩
int compare_pdp(const void *a, const void *b) {
    const STUDENT *stu1 = (const STUDENT *)a;
    const STUDENT *stu2 = (const STUDENT *)b;
    if (stu2->score.pdp > stu1->score.pdp) return 1;
    if (stu2->score.pdp < stu1->score.pdp) return -1;
    return 0;
}

// 比较函数 - 按数据结构成绩
int compare_ds(const void *a, const void *b) {
    const STUDENT *stu1 = (const STUDENT *)a;
    const STUDENT *stu2 = (const STUDENT *)b;
    if (stu2->score.ds > stu1->score.ds) return 1;
    if (stu2->score.ds < stu1->score.ds) return -1;
    return 0;
}

// 比较函数 - 按数字逻辑成绩
int compare_dl(const void *a, const void *b) {
    const STUDENT *stu1 = (const STUDENT *)a;
    const STUDENT *stu2 = (const STUDENT *)b;
    if (stu2->score.dl > stu1->score.dl) return 1;
    if (stu2->score.dl < stu1->score.dl) return -1;
    return 0;
}

/**
 * @brief 按指定科目成绩降序排序学生数组
 * @param option 排序选项
 */
void sort_students_by_course(SORT_OPTION option) {
    switch (option) {
        case SORT_BY_ICS:
            qsort(students, student_count, sizeof(STUDENT), compare_ics);
            break;
        case SORT_BY_PDP:
            qsort(students, student_count, sizeof(STUDENT), compare_pdp);
            break;
        case SORT_BY_DS:
            qsort(students, student_count, sizeof(STUDENT), compare_ds);
            break;
        case SORT_BY_DL:
            qsort(students, student_count, sizeof(STUDENT), compare_dl);
            break;
    }
}
