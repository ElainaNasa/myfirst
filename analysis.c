#include "analysis.h"
#include <stdio.h>

// 获取成绩等级
GRADE_LEVEL get_grade_level(float score) {
    if (score >= 90) return GRADE_EXCELLENT;
    if (score >= 80) return GRADE_GOOD;
    if (score >= 70) return GRADE_MEDIUM;
    if (score >= 60) return GRADE_PASS;
    return GRADE_FAIL;
}

// 获取等级名称
const char* get_grade_name(GRADE_LEVEL level) {
    switch (level) {
        case GRADE_EXCELLENT: return "Excellent (90-100)";
        case GRADE_GOOD:      return "Good (80-89)";
        case GRADE_MEDIUM:    return "Medium (70-79)";
        case GRADE_PASS:      return "Pass (60-69)";
        case GRADE_FAIL:      return "Fail (0-59)";
        default:              return "Unknown";
    }
}

/**
 * @brief 对每门课程进行成绩统计分析
 */
void analyze_course_grades() {
    char msg[256];

    if (student_count == 0) {
        printf("No students to analyze.\n");

        snprintf(msg, sizeof(msg),"No students to analyze");
        speak(msg);
        msg[0] = '\0';

        return;
    }

    // 初始化计数器
    int ics_counts[5] = {0};
    int pdp_counts[5] = {0};
    int ds_counts[5] = {0};
    int dl_counts[5] = {0};

    // 统计各科目成绩等级
    for (int i = 0; i < student_count; i++) {
        ics_counts[get_grade_level(students[i].score.ics)]++;
        pdp_counts[get_grade_level(students[i].score.pdp)]++;
        ds_counts[get_grade_level(students[i].score.ds)]++;
        dl_counts[get_grade_level(students[i].score.dl)]++;
    }

    // 打印统计结果
    printf("\nGrade Statistics Analysis:\n");
    printf("==========================\n\n");
    
    snprintf(msg, sizeof(msg),"Grade Statistics Analysis");
    speak(msg);
    msg[0] = '\0';

    const char* courses[] = {"Computer Systems (iCS)", "Programming Practice (PDP)", 
                            "Data Structures (DS)", "Digital Logic (DL)"};
    int *counts[] = {ics_counts, pdp_counts, ds_counts, dl_counts};

    for (int course = 0; course < 4; course++) {
        printf("%s:\n", courses[course]);
        printf("----------------------------------------\n");
        
        for (int level = 0; level < 5; level++) {
            int count = counts[course][level];
            float percentage = (float)count / student_count * 100;
            
            printf("%-20s: %2d students (%5.1f%%)\n", 
                   get_grade_name(level), count, percentage);

            snprintf(msg, sizeof(msg),"%s: %d students %.1f percent", get_grade_name(level), count, percentage);
            speak(msg);
            msg[0] = '\0';
            
        }
        printf("\n");
    }
}
