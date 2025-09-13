#include "mySQL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initDBConfig(DBConfig *config, const char *host, const char *user, const char *password, const char *database, unsigned int port) {
    config->host = host;
    config->user = user;
    config->password = password;
    config->database = database;
    config->port = port;
}

bool dbConnect(DBConnection *db, DBConfig *config) {
    db->conn = mysql_init(NULL);
    if (!db->conn) {
        printf("mysql_init failed\n");
        return false;
    }

    if (!mysql_real_connect(db->conn, config->host, config->user, config->password, config->database, config->port, NULL, 0)) {
        printf("Connection failed: %s\n", mysql_error(db->conn));
        return false;
    }
    return true;
}

void dbClose(DBConnection *db) {
    if (db->conn) {
        mysql_close(db->conn);
        db->conn = NULL;
    }
}

bool dbExecute(DBConnection *db, const char *sql) {
    if (mysql_query(db->conn, sql)) {
        printf("Query failed: %s\n", mysql_error(db->conn));
        return false;
    }
    return true;
}

MYSQL_RES* dbQuery(DBConnection *db, const char *sql) {
    if (mysql_query(db->conn, sql)) {
        printf("Query failed: %s\n", mysql_error(db->conn));
        return NULL;
    }
    return mysql_store_result(db->conn);
}

void dbFreeResult(MYSQL_RES *res) {
    if (res) mysql_free_result(res);
}

// ====== 功能函数示例 ======

bool insertStudent(DBConnection *db, STUDENT *s) {
    char msg[256];
    char sql[512];
    snprintf(sql, sizeof(sql),
        "INSERT INTO students (stu_id, stu_name, ics, pdp, ds, dl) VALUES "
        "('%s', '%s', %.2f, %.2f, %.2f, %.2f)",
        s->stu_id, s->stu_name, s->score.ics, s->score.pdp, s->score.ds, s->score.dl);
    
        snprintf(msg, sizeof(msg),"Successfully INSERT INTO students");
    speak(msg);
    msg[0] = '\0';
    return dbExecute(db, sql);
}

MYSQL_RES* searchByID(DBConnection *db, const char *stu_id) {
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT * FROM students WHERE stu_id='%s'", stu_id);
    return dbQuery(db, sql);
}

MYSQL_RES* searchByName(DBConnection *db, const char *name) {
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT * FROM students WHERE stu_name='%s'", name);
    return dbQuery(db, sql);
}

bool modifyByID(DBConnection *db, const char *stu_id, STUDENT *s) {
    char sql[512];
    snprintf(sql, sizeof(sql),
        "UPDATE students SET stu_name='%s', ics=%.2f, pdp=%.2f, ds=%.2f, dl=%.2f WHERE stu_id='%s'",
        s->stu_name, s->score.ics, s->score.pdp, s->score.ds, s->score.dl, stu_id);
    return dbExecute(db, sql);
}

bool deleteByID(DBConnection *db, const char *stu_id) {
    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM students WHERE stu_id='%s'", stu_id);
    return dbExecute(db, sql);
}
/* --- statistics / sorting / aggregation --- */

/*
 * 返回每个学生的 id, name, total, average
 * SELECT stu_id, stu_name, (ics+pdp+ds+dl) AS total, (ics+pdp+ds+dl)/4 AS average FROM students;
 */
MYSQL_RES* totalAndAveragePerStudent(DBConnection *db) {
    if (!db || !db->conn) return NULL;
    const char *sql = "SELECT stu_id, stu_name, (IFNULL(ics,0)+IFNULL(pdp,0)+IFNULL(ds,0)+IFNULL(dl,0)) AS total, "
                      "(IFNULL(ics,0)+IFNULL(pdp,0)+IFNULL(ds,0)+IFNULL(dl,0))/4.0 AS average "
                      "FROM students";
    return dbQuery(db, sql);
}

/*
 * 返回每门课程的平均分
 * SELECT AVG(ics) AS avg_ics, AVG(pdp) AS avg_pdp, AVG(ds) AS avg_ds, AVG(dl) AS avg_dl FROM students;
 */
MYSQL_RES* averagePerCourse(DBConnection *db) {
    if (!db || !db->conn) return NULL;
    const char *sql = "SELECT AVG(ics) AS avg_ics, AVG(pdp) AS avg_pdp, AVG(ds) AS avg_ds, AVG(dl) AS avg_dl FROM students";
    return dbQuery(db, sql);
}

/*
 * 按指定课程降序排序，course 必须是预期字段之一，防止 SQL 注入
 * 返回 SELECT stu_id, stu_name, ics, pdp, ds, dl FROM students ORDER BY <course> DESC;
 */
MYSQL_RES* sortByCourse(DBConnection *db, const char *course) {
    if (!db || !db->conn || !course) return NULL;

    /* 只允许受控字段，防止注入 */
    if (strcmp(course, "ics") != 0 &&
        strcmp(course, "pdp") != 0 &&
        strcmp(course, "ds") != 0 &&
        strcmp(course, "dl") != 0) {
        fprintf(stderr, "sortByCourse: invalid course name '%s'\n", course);
        return NULL;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT stu_id, stu_name, ics, pdp, ds, dl FROM students ORDER BY %s DESC", course);
    return dbQuery(db, sql);
}

/*
 * 每门课程统计（avg, min, max）
 * SELECT AVG(ics) avg_ics, MIN(ics) min_ics, MAX(ics) max_ics, ... FROM students;
 */
MYSQL_RES* statsPerCourse(DBConnection *db) {
    if (!db || !db->conn) return NULL;
    const char *sql =
        "SELECT "
        "AVG(ics) AS avg_ics, MIN(ics) AS min_ics, MAX(ics) AS max_ics, "
        "AVG(pdp) AS avg_pdp, MIN(pdp) AS min_pdp, MAX(pdp) AS max_pdp, "
        "AVG(ds)  AS avg_ds,  MIN(ds)  AS min_ds,  MAX(ds)  AS max_ds,  "
        "AVG(dl)  AS avg_dl,  MIN(dl)  AS min_dl,  MAX(dl)  AS max_dl "
        "FROM students";
    return dbQuery(db, sql);
}