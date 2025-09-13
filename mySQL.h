#ifndef MYSQL_HELPER_H
#define MYSQL_HELPER_H

#include <mysql/mysql.h>
#include <stdbool.h>
#include "student.h"
#include "speak.h"

// 数据库配置结构体
typedef struct {
    const char *host;
    const char *user;
    const char *password;
    const char *database;
    unsigned int port;
} DBConfig;

// 数据库连接结构体
typedef struct {
    MYSQL *conn;
} DBConnection;

// 初始化数据库配置
void initDBConfig(DBConfig *config, const char *host, const char *user, const char *password, const char *database, unsigned int port);

// 连接数据库
bool dbConnect(DBConnection *db, DBConfig *config);

// 关闭数据库
void dbClose(DBConnection *db);

// 执行非查询 SQL（INSERT、UPDATE、DELETE）
bool dbExecute(DBConnection *db, const char *sql);

// 执行查询 SQL（SELECT）
MYSQL_RES* dbQuery(DBConnection *db, const char *sql);

// 释放查询结果
void dbFreeResult(MYSQL_RES *res);

// ====== 菜单对应函数 ======

// 插入学生记录
bool insertStudent(DBConnection *db, STUDENT *s);

// 按姓名查询学生
MYSQL_RES* searchByName(DBConnection *db, const char *name);

// 按学号查询学生
MYSQL_RES* searchByID(DBConnection *db, const char *stu_id);

// 根据学号修改学生记录
bool modifyByID(DBConnection *db, const char *stu_id, STUDENT *s);

// 根据学号删除学生记录
bool deleteByID(DBConnection *db, const char *stu_id);

// 计算每个学生总分和平均分
MYSQL_RES* totalAndAveragePerStudent(DBConnection *db);

// 计算每门课程平均分
MYSQL_RES* averagePerCourse(DBConnection *db);

// 按课程成绩降序排序
MYSQL_RES* sortByCourse(DBConnection *db, const char *course);

// 每门课程统计分析（平均、最高、最低）
MYSQL_RES* statsPerCourse(DBConnection *db);

#endif // MYSQL_HELPER_H
