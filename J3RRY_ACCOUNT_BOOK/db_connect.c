#include "db_connect.h"
#ifdef __cplusplus
extern "C" {
#endif
	sqlite3* db;
	/**
	 * 创建到数据库的连接
	 * @param db_filename 数据库文件名
	 */
	bool db_connect(const char* db_filename)
	{
		const int rc = sqlite3_open(db_filename, &db);
		if (rc != SQLITE_OK)
		{
			// 连接数据库失败
			return false;
		}
		else
		{
			// 连接数据库成功
			return true;
		}
	}
	/**
	 * 在数据库还没有建立的情况下，读取 sql 文件，建立数据库中的表
	 * @param sql_filename sql 文件名
	 */
	bool init_db(const char* sql_filename)
	{
		char* error_msg = { 0 };
		FILE* file = fopen(sql_filename, "r");
		if (!file)
		{
			// 打开 sql 文件失败
			return false;
		}
		char file_buffer[1024 * 10]; // sql 文件缓存大小为 10KB
		int index = 0;
		int c;
		while ((c = getc(file)) != EOF) {
			file_buffer[index++] = (char)c;
		}
		file_buffer[index] = '\0';
		const int rc = sqlite3_exec(db, file_buffer, NULL, NULL, &error_msg);
		if (rc != SQLITE_OK)
		{
			// 创建表失败，输出错误信息
			//fprintf(stderr, "Create tables failed:\n%s\n", error_msg);
			sqlite3_free(error_msg);
			return false;
		}
		else
		{
			return true;
		}

	}

	bool drop_all_tables()
	{
		char sql[1024];
		sprintf(sql, "drop table transactions;\ndrop table user;\n drop table transaction_classes;\n ");
		const int result = sqlite3_exec(db, sql, NULL, NULL, NULL);
		return result == SQLITE_OK;
	}
#ifdef __cplusplus
}
#endif