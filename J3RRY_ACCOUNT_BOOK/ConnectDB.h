#ifndef DB_CONNECT_H
#define DB_CONNECT_H
#ifdef __cplusplus
extern "C" {
#endif
	
#include "include/sqlite/sqlite3.h"
#include <stdbool.h>
#include <stdio.h>
	extern sqlite3* db;
	/**
	 * ���������ݿ������
	 * @param db_filename ���ݿ��ļ���
	 */
	bool db_connect(const char* db_filename);
	/**
	 * �����ݿ⻹û�н���������£���ȡ sql �ļ����������ݿ��еı�
	 * @param sql_filename sql �ļ���
	 */
	bool init_db(const char* sql_filename);

	bool drop_all_tables();
#ifdef __cplusplus
}
#endif
#endif
