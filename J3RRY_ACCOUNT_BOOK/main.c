#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "include/sqlite/sqlite3.h"
#include "ConnectDB.h"
#include "ProcessRecord.h"
#include "utilities.h"
#include "view.h"
#include "viewGUI.h"
#pragma warning( disable : 6031)  // Ignore specific warning message from visual studio.
sqlite3* db;

int main(int argc, char *argv[]){
	// Init database connection;
	db_connect("db.db"); // 连接到数据库
	init_db("./db.sql"); // 根据 SQL 文件创建表
	//printAllUser();
	ACCOUNT_BOOK_MAIN_LOOP();
	//ACCOUNT_BOOK_GUI_MAIN_LOOP(); // Not completed.
	sqlite3_close(db);
    return 0;
}
