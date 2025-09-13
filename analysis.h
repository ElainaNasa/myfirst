#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "mySQL.h"
#include "student.h"
#include <mysql/mysql.h>

// 成绩等级枚举
typedef enum {
    GRADE_EXCELLENT,  // 90-100
    GRADE_GOOD,       // 80-89
    GRADE_MEDIUM,     // 70-79
    GRADE_PASS,       // 60-69
    GRADE_FAIL        // 0-59
} GRADE_LEVEL;

// 函数声明
GRADE_LEVEL get_grade_level(float score);
const char* get_grade_name(GRADE_LEVEL level);

void analyze_course_grades_mysql();  // MySQL版成绩分析
void analyze_course_grades();        // 通用接口（调用MySQL版）

#endif // ANALYSIS_H
