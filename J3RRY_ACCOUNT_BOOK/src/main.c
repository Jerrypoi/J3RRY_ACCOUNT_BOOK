#include <stdio.h>
#include <stdlib.h>
#include "model.h"
#include "include/sqlite/sqlite3.h"
#include "../db_connect.h"


int main(int argc, char *argv[]){
	int rc = sqlite3_open("test.db", db);
    
    char file_buffer[1024 * 2];
	FILE* file = fopen("./src/sql/db.sql","r");
    if(file) {
        int index = 0;
        int c;
        while((c = getc(file)) != EOF) {
            file_buffer[index++] = c;
        }
        file_buffer[index] = '\0';
    }
    rc = sqlite3_exec(db,file_buffer,NULL,0,&zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }
	user result = getUserById(db, 1);
	transaction_class a = getTransactionClassByID(db, 1);
	transaction hkb = getTransactionByID(db, 1);
	insertIntoUser(db,0, "jerry","passwd","email");
	insertIntoTransactionClass(db, 0, "test_class");
	insertIntoTransactions(db, 0, 0, 2313.1, 1,1, "1999-06-01");
    sqlite3_close(db);
    return 0;
}
