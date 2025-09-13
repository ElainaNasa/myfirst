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
    
        snprintf(msg, sizeof(msg),"INSERT INTO students (stu_id, stu_name, ics, pdp, ds, dl) VALUES "
        "('%s', '%s', %.2f, %.2f, %.2f, %.2f)",
        s->stu_id, s->stu_name, s->score.ics, s->score.pdp, s->score.ds, s->score.dl);
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
