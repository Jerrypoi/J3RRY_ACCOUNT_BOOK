#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "include/sqlite/sqlite3.h"
#include "db_connect.h"
sqlite3* db;

int main(int argc, char *argv[]){
	// Init database connection;
	db_connect("db.db"); // 连接到数据库
	init_db("./db.sql"); // 根据 SQL 文件创建表
	insertIntoUser(db, 0, "jerry", "passwd", "email");
	insertIntoTransactionClass(db, 0, "test_class");
	insertIntoTransactions(db, 0, 0, 2313.1, 1, 1, "1999-06-01");
	user result = getUserById(db, 1);
	transaction_class a = getTransactionClassByID(db, 1);
	transaction hkb = getTransactionByID(db, 1);

    sqlite3_close(db);
    return 0;
}
