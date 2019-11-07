//
// Created by Jerry Zhang on 11/6/19.
//

#include "model.h"

static int callback_user(void* list, int argc, char** argv, char** azColName) {
	// The order of this should not be changed.
	user* u = (user*)malloc(sizeof(user));
	if (!u) {
		return -1;
	}
	u->id = strtol(argv[0], NULL, 10);
	u->name = (char*)malloc(sizeof(char) * strlen(argv[1]));
	if (argv[1] && u->name) {
		
		strcpy(u->name, argv[1]);
	}
	else {
		u->name = NULL;
	}
	u->password = (char*)malloc(sizeof(char) * strlen(argv[2]));
	if (argv[2] && u->password) {
		strcpy(u->password, argv[2]);
	}
	else {
		u->password = NULL;
	}
	u->email_addr = (char*)malloc(sizeof(char) * strlen(argv[3]));
	if (argv[3] && u->email_addr) {
		strcpy(u->email_addr, argv[3]);
	}
	else {
		u->email_addr = NULL;
	}
	llist_push( (llist *)list, u);
	return 0;
}
/**
 * 
 */
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}
user getUserById(sqlite3 *db,const int id) {
	user* data = (user*)malloc(sizeof(user*));
	if (!data)
		return;
	data->id = 250;
	data->name = "FK";
	data->password = "NO";
	data->email_addr = "FK";
	char sql[1024] = { 0 };
	llist *list = llist_create(NULL);
	sprintf(sql, "select * from user where id = %d;", id);
	sqlite3_exec(db, sql, callback_user, list, NULL);
	return *((user*)((*list)->data));
}
static int callback_transaction_class(void* list, int argc, char** argv, char** azColName) {
	// The order of this should not be changed.
	transaction_class* data = (transaction_class *)malloc(sizeof(transaction_class));
	if (!data) {
		return -1;
	}
	data->id = atoi(argv[0]);
	data->class_name = (char*)malloc(sizeof(char) * strlen(argv[1]));
	if (argv[1] && data->class_name) {

		strcpy(data->class_name, argv[1]);
	}
	else {
		data->class_name = NULL;
	}
	llist_push((llist*)list, data);
	return 0;
}
static int callback_transaction(void* list, int argc, char** argv, char** azColName) {
	// The order of this should not be changed.
	transaction* data = (transaction*)malloc(sizeof(transaction));
	if (!data) {
		return -1;
	}
	data->id = atoi(argv[0]);
	data->type = atoi(argv[1]);
	data->amount = atof(argv[2]);
	data->class_id = atoi(argv[3]);
	data->user_id = atoi(argv);
	data->transaction_date = (char*)malloc(sizeof(char) * strlen(argv[4]));
	if (argv[4] && data->transaction_date) {
		strcpy(data->transaction_date, argv[4]);
	}
	else {
		data->transaction_date = NULL;
	}
	llist_push((llist*)list, data);
	return 0;
}
transaction_class getTransactionClassByID(sqlite3 *db, const int id) {
	char sql[1024] = { 0 };
	llist* list = llist_create(NULL);
	sprintf(sql, "select * from transaction_classes where id = %d;",id);
	sqlite3_exec(db, sql, callback_transaction_class, list, NULL);
	return *((transaction_class *)((*list)->data));
}
transaction getTransactionByID(sqlite3 *db,int id) {
	char sql[1024] = { 0 };
	llist* list = llist_create(NULL);
	sprintf(sql, "select * from transactions;");
	sqlite3_exec(db, sql, callback_transaction, list, NULL);
	return *((transaction *)((*list)->data));
}

// Insert into user table. Set id = 0 to auto select id.
bool insertIntoUser(sqlite3* db, int id, char* name, char* password, char* email) {
	char* zErrMsg = 0;
	char sql[1024] = {0};
	if (id != 0)
		sprintf(sql, "insert into user values(%d,'%s','%s','%s');", id, name, password, email);
	else
		sprintf(sql,"insert into user(name,password,email_addr) values('%s','%s','%s');", name, password, email);
	const int rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	if (rc == SQLITE_OK) {

		return true;
	}
	else {
		fprintf(stderr, "inserting into user table failed: %s\n", zErrMsg);
		return true;
	}
}
// Insert into user table. Set id = 0 to auto select id.
bool insertIntoTransactionClass(sqlite3* db, int id, char* class_name) {
	char* zErrMsg = 0;
	char sql[1024] = { 0 };
	if (id != 0)
		sprintf(sql, "insert into transaction_classes values(%d,'%s');", id, class_name);
	else
		sprintf(sql, "insert into transaction_classes(class_name) values('%s');", class_name);
	const int rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	if (rc == SQLITE_OK) {
		return true;
	}
	else {
		fprintf(stderr, "inserting into transaction_classes table failed: %s\n", zErrMsg);
		return true;
	}
}

// Insert into transaction table. Set id = 0 to auto select id. Note that transaction date should be in correct format.
bool insertIntoTransactions(sqlite3* db, const int id, const bool type, const double amount, const int class_id, const int user_id, char* transaction_date) {
	char* zErrMsg = 0;
	char sql[1024] = { 0 };
	if (id != 0)
		sprintf(sql, "insert into transactions values(%d,%s,%lf,%d,%d,'%s');",id, type ? "true" : "false",amount,class_id,user_id,transaction_date);
	else
		sprintf(sql, "insert into transactions(type,amount,class_id,user_id,transaction_date) values(%s,%lf,%d,%d,'%s');", type ? "true" : "false", amount, class_id, user_id, transaction_date);
	int rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	if (rc == SQLITE_OK) {
		return true;
	}
	else {
		fprintf(stderr, "inserting into transactions table failed: %s\n", zErrMsg);
		return true;
	}
}