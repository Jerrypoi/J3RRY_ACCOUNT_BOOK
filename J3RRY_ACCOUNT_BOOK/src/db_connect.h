#ifndef DB_CONNECT_H
#define DB_CONNECT_H
#include "include/sqlite/sqlite3.h"
#include <stdbool.h>
#include <stdio.h>
extern sqlite3* db;
/**
 * ���������ݿ������
 * @param db_filename ���ݿ��ļ���
 */
bool connect(const char* db_filename);
/**
 * �����ݿ⻹û�н���������£���ȡ sql �ļ����������ݿ��еı�
 * @param sql_filename sql �ļ���
 */
bool init_db(const char* sql_filename);
#endif
