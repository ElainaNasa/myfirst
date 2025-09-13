#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "student.h"

// 成绩等级枚举
typedef enum {
    GRADE_EXCELLENT,  // 优秀 (90-100)
    GRADE_GOOD,       // 良好 (80-89)
    GRADE_MEDIUM,     // 中等 (70-79)
    GRADE_PASS,       // 及格 (60-69)
    GRADE_FAIL        // 不及格 (0-59)
} GRADE_LEVEL;

/**
 * @brief 对每门课程进行成绩统计分析
 */
void analyze_course_grades();

#endif // ANALYSIS_H
