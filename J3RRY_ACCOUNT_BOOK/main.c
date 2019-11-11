#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "include/sqlite/sqlite3.h"
#include "db_connect.h"
#include "process_record.h"
#include "utilities.h"
sqlite3* db;

int main(int argc, char *argv[]){
	// Init database connection;
	db_connect("db.db"); // 连接到数据库
	init_db("./db.sql"); // 根据 SQL 文件创建表
	insertIntoUser(db, 0, "jerry", "passwd", "email");
	insertIntoTransactionClass(db, 0, "test_class");
	insertIntoTransactions(db, 0, 0, 2313.1, 1, 1, "1999-06-01");
	user* result = getUserByName(db, "je12rry");
	transaction_class* a = getTransactionClassByID(db, 1);
	transaction* hkb = getTransactionByID(db, 1);
	printAllUser();
	printf("time: %s", getSystemDate());
    sqlite3_close(db);
    return 0;
}
