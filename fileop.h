#ifndef FILEOP_H
#define FILEOP_H

#include "student.h"

/**
 * @brief 保存学生数据到文本文件
 * @param filename 文件名
 * @return 成功返回0，失败返回-1
 */
int save_to_text_file(const char *filename);

/**
 * @brief 从文本文件加载学生数据
 * @param filename 文件名
 * @return 成功返回0，失败返回-1
 */
int load_from_text_file(const char *filename);

/**
 * @brief 保存学生数据到二进制文件
 * @param filename 文件名
 * @return 成功返回0，失败返回-1
 */
int save_to_binary_file(const char *filename);

/**
 * @brief 从二进制文件加载学生数据
 * @param filename 文件名
 * @return 成功返回0，失败返回-1
 */
int load_from_binary_file(const char *filename);

#endif // FILEOP_H
