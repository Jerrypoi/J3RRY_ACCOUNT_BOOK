#include "db_connect.h"
#ifdef __cplusplus
extern "C" {
#endif
	sqlite3* db;
	/**
	 * ���������ݿ������
	 * @param db_filename ���ݿ��ļ���
	 */
	bool db_connect(const char* db_filename)
	{
		const int rc = sqlite3_open(db_filename, &db);
		if (rc != SQLITE_OK)
		{
			// �������ݿ�ʧ��
			return false;
		}
		else
		{
			// �������ݿ�ɹ�
			return true;
		}
	}
	/**
	 * �����ݿ⻹û�н���������£���ȡ sql �ļ����������ݿ��еı�
	 * @param sql_filename sql �ļ���
	 */
	bool init_db(const char* sql_filename)
	{
		char* error_msg = { 0 };
		FILE* file = fopen(sql_filename, "r");
		if (!file)
		{
			// �� sql �ļ�ʧ��
			return false;
		}
		char file_buffer[1024 * 10]; // sql �ļ������СΪ 10KB
		int index = 0;
		int c;
		while ((c = getc(file)) != EOF) {
			file_buffer[index++] = (char)c;
		}
		file_buffer[index] = '\0';
		const int rc = sqlite3_exec(db, file_buffer, NULL, NULL, &error_msg);
		if (rc != SQLITE_OK)
		{
			// ������ʧ�ܣ����������Ϣ
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