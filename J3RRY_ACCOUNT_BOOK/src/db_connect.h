#ifndef DB_CONNECT_H
#define DB_CONNECT_H
#include "include/sqlite/sqlite3.h"
#include <stdbool.h>
#include <stdio.h>
extern sqlite3* db;
/**
 * 创建到数据库的连接
 * @param db_filename 数据库文件名
 */
bool connect(const char* db_filename);
/**
 * 在数据库还没有建立的情况下，读取 sql 文件，建立数据库中的表
 * @param sql_filename sql 文件名
 */
bool init_db(const char* sql_filename);
#endif
