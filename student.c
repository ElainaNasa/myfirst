#include "student.h"

// 全局变量定义
STUDENT students[MAX_STUDENTS];
int student_count = 0;

// 初始化学生数组
void init_students() {
    student_count = 0;
    memset(students, 0, sizeof(students));
}
