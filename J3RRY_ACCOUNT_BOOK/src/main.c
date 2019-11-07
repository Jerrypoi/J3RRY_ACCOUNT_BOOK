#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "include/sqlite/sqlite3.h"
#include "db_connect.h"
sqlite3* db;

int main(int argc, char *argv[]){
	// Init database connection;
	connect("test.db");
	init_db("./src/sql/db.sql");
	user result = getUserById(db, 1);
	transaction_class a = getTransactionClassByID(db, 1);
	transaction hkb = getTransactionByID(db, 1);
	insertIntoUser(db,0, "jerry","passwd","email");
	insertIntoTransactionClass(db, 0, "test_class");
	insertIntoTransactions(db, 0, 0, 2313.1, 1,1, "1999-06-01");
    sqlite3_close(db);
    return 0;
}
