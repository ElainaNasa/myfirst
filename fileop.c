#include "fileop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * @brief 保存学生数据到文本文件
 * @param filename 文件名
 * @return 成功返回0，失败返回-1
 */
int save_to_text_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        HANDLE_ERROR("Failed to open text file for writing");
        return -1;
    }

    // 写入表头
    fprintf(file, "%-20s %-15s %8s %8s %8s %8s\n", 
            "ID", "name", "iCS", "PDP", "DS", "DL");

    // 写入学生数据
    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%-20s %-15s %8.1f %8.1f %8.1f %8.1f\n",
                students[i].stu_id,
                students[i].stu_name,
                students[i].score.ics,
                students[i].score.pdp,
                students[i].score.ds,
                students[i].score.dl);
    }

    fclose(file);
    return 0;
}

/**
 * @brief 从文本文件加载学生数据
 * @param filename 文件名
 * @return 成功返回0，失败返回-1
 */
int load_from_text_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        HANDLE_ERROR("Failed to open text file for reading");
        return -1;
    }

    // 跳过表头
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        fclose(file);
        return -1;
    }

    // 读取学生数据
    student_count = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL && student_count < MAX_STUDENTS) {
        STUDENT *stu = &students[student_count];
        
        if (sscanf(buffer, "%s %s %f %f %f %f",
                   stu->stu_id, stu->stu_name,
                   &stu->score.ics, &stu->score.pdp,
                   &stu->score.ds, &stu->score.dl) == 6) {
            student_count++;
        }
    }

    fclose(file);
    return 0;
}

/**
 * @brief 保存学生数据到二进制文件
 * @param filename 文件名
 * @return 成功返回0，失败返回-1
 */
int save_to_binary_file(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        HANDLE_ERROR("Failed to open binary file for writing");
        return -1;
    }

    // 先写入学生数量
    if (fwrite(&student_count, sizeof(int), 1, file) != 1) {
        fclose(file);
        HANDLE_ERROR("Failed to write student count");
        return -1;
    }

    // 写入所有学生数据
    if (fwrite(students, sizeof(STUDENT), student_count, file) != student_count) {
        fclose(file);
        HANDLE_ERROR("Failed to write student data");
        return -1;
    }

    fclose(file);
    return 0;
}

/**
 * @brief 从二进制文件加载学生数据
 * @param filename 文件名
 * @return 成功返回0，失败返回-1
 */
int load_from_binary_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        HANDLE_ERROR("Failed to open binary file for reading");
        return -1;
    }

    // 读取学生数量
    int count;
    if (fread(&count, sizeof(int), 1, file) != 1) {
        fclose(file);
        HANDLE_ERROR("Failed to read student count");
        return -1;
    }

    // 确保不超过最大容量
    if (count > MAX_STUDENTS) {
        fclose(file);
        printf("Error: File contains too many students (%d > %d)\n", count, MAX_STUDENTS);
        return -1;
    }

    // 读取学生数据
    if (fread(students, sizeof(STUDENT), count, file) != count) {
        fclose(file);
        HANDLE_ERROR("Failed to read student data");
        return -1;
    }

    student_count = count;
    fclose(file);
    return 0;
}
