#include "analysis.h"
#include "speak.h"
#include "mySQL.h"
#include <stdio.h>
#include <stdlib.h>

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

// MySQL版成绩统计分析
void analyze_course_grades_mysql() {
    char msg[256];
    DBConfig config;
    DBConnection db;

    initDBConfig(&config, "localhost", "student", "11111111", "testdb", 3306);

    if (!dbConnect(&db, &config)) {
        printf("Failed to connect to database.\n");
        return;
    }

    // 获取总学生数
    MYSQL_RES* res_total = dbQuery(&db, "SELECT COUNT(*) FROM students;");
    int total_students = 0;
    if (res_total) {
        MYSQL_ROW row = mysql_fetch_row(res_total);
        if (row && row[0]) total_students = atoi(row[0]);
        dbFreeResult(res_total);
    }

    if (total_students == 0) {
        printf("No students in database to analyze.\n");
        snprintf(msg, sizeof(msg), "No students in database to analyze.");
        speak(msg);
        dbClose(&db);
        return;
    }

    const char* courses[] = {"ics", "pdp", "ds", "dl"};
    const char* course_names[] = {"Computer Systems (iCS)", "Programming Practice (PDP)",
                                  "Data Structures (DS)", "Digital Logic (DL)"};

    for (int c = 0; c < 4; c++) {
        // 查询当前课程所有成绩
        char query[128];
        snprintf(query, sizeof(query), "SELECT %s FROM students;", courses[c]);
        MYSQL_RES* res = dbQuery(&db, query);
        if (!res) continue;

        int counts[5] = {0}; // 五个等级计数
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res)) != NULL) {
            float score = row[0] ? atof(row[0]) : 0;
            counts[get_grade_level(score)]++;
        }
        dbFreeResult(res);

        // 打印分析结果
        printf("%s:\n", course_names[c]);
        printf("----------------------------------------\n");
        snprintf(msg, sizeof(msg), "%s statistics:", course_names[c]);
        speak(msg);

        for (int level = 0; level < 5; level++) {
            float percentage = (float)counts[level] / total_students * 100;
            printf("%-20s: %2d students (%5.1f%%)\n", get_grade_name(level), counts[level], percentage);

            snprintf(msg, sizeof(msg), "%s: %d students %.1f percent",
                     get_grade_name(level), counts[level], percentage);
            speak(msg);
        }
        printf("\n");
    }

    dbClose(&db);
}

// 保留原函数名作为别名，兼容现有 main.c 菜单调用
void analyze_course_grades() {
    analyze_course_grades_mysql();
}
