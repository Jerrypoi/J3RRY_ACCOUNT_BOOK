//
// Created by Jerry Zhang on 11/6/19.
//

#include "model.h"
/**
 * Call back 函数，sqlite3_exec 执行完 sql 命令后调用 callback。其中，sqlite_exec3 会将它的第四个参数传入 callback 函数的第一个参数
 * Call back 函数的 argv 是 sql 命令的执行结果，按列分开
 * 
 */
int callback_user(void* list, int argc, char** argv, char** azColName) {
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
	llist_push( list, u);
	return 0;
}
/**
 * Callback 函数，输出 SQL 执行结果
 */
int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}
int callback_transaction_class(void* list, int argc, char** argv, char** azColName) {
	// The order of this should not be changed.
	transaction_class* data = (transaction_class*)malloc(sizeof(transaction_class));
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
int callback_transaction(void* list, int argc, char** argv, char** azColName) {
	// The order of this should not be changed.
	transaction* data = (transaction*)malloc(sizeof(transaction));
	if (!data) {
		return -1;
	}
	data->id = atoi(argv[0]);
	data->type = atoi(argv[1]);
	data->amount = atof(argv[2]);
	data->class_id = atoi(argv[3]);
	data->user_id = atoi(argv[4]);
	data->transaction_date = (char*)malloc(sizeof(char) * strlen(argv[5]) * 2);
	if (argv[5] && data->transaction_date) {
		strcpy(data->transaction_date, argv[5]);
	}
	else {
		data->transaction_date = NULL;
	}
	llist_push((llist*)list, data);
	return 0;
}

/**
 * 根据用户 id 获取用户数据
 * sqlite3_exec() 这个函数的 list 参数会传入 callback_user 函数，因此在 callback_user 函数中将用户信息取出放入 list 中即可
 * @param id 用户id，int
 * @param db 数据库连接
 */
user* getUserById(sqlite3 *db,const int id) {
	user* data = (user*)malloc(sizeof(user));
	if (!data)
	{
		return NULL;
	}
	char sql[1024] = { 0 };
	llist *list = llist_create(NULL);
	sprintf(sql, "select * from user where id = %d;", id);
	sqlite3_exec(db, sql, callback_user, list, NULL);
	return (user*)((*list)->data);
}
// 根据名字获取用户信息
user* getUserByName(sqlite3* db, char* name)
{
	user* data = (user*)malloc(sizeof(user));
	if (!data)
	{
		return NULL;
	}
	char sql[1024] = { 0 };
	llist* list = llist_create(NULL);
	sprintf(sql, "select * from user where name = '%s';", name);
	sqlite3_exec(db, sql, callback_user, list, NULL);
	return (user*)((*list)->data);
}

/**
 * 根据 id 查找交易类别
 */
transaction_class* getTransactionClassByID(sqlite3* db, const int id) {
	char sql[1024] = { 0 };
	llist* list = llist_create(NULL);
	sprintf(sql, "select * from transaction_classes where id = %d;", id);
	sqlite3_exec(db, sql, callback_transaction_class, list, NULL);
	return (transaction_class*)((*list)->data);
}
/**
 * 根据交易类别的名字查找交易类别
 */
transaction_class* getTransactionClassByName(sqlite3* db, char* name)
{
	char sql[1024] = { 0 };
	llist* list = llist_create(NULL);
	sprintf(sql, "select * from transaction_classes where class_name ='%s';", name);
	sqlite3_exec(db, sql, callback_transaction_class, list, NULL);
	return (transaction_class*)((*list)->data);
}

/**
 * 根据交易 ID 查询交易信息
 */
transaction* getTransactionByID(sqlite3 *db, const int id) {
	char sql[1024] = { 0 };
	llist* list = llist_create(NULL);
	sprintf(sql, "select * from transactions where id =%d;",id);
	sqlite3_exec(db, sql, callback_transaction, list, NULL);
	return (transaction *)((*list)->data);
}
/**
 * 获取所有交易信息
 */
llist* getAllTransaction()
{
	llist* result = llist_create(NULL);
	char sql[1024];
	sprintf(sql, "select * from transactions;");
	sqlite3_exec(db, sql, callback_transaction, result, NULL);
	return result;
}
/**
 * 获取所有交易类别
 */
llist* getAllTransactionClass()
{
	llist* result = llist_create(NULL);
	char sql[1024];
	sprintf(sql, "select * from transaction_classes;");
	sqlite3_exec(db, sql, callback_transaction_class, result, NULL);
	return result;
}
/**
 * 获取所有用户信息
 */
llist* getAllUser()
{
	llist* result = llist_create(NULL);
	char sql[1024];
	sprintf(sql, "select * from user;");
	sqlite3_exec(db, sql, callback_user, result, NULL);
	return result;
}
/**
 * 插入到用户表，调用函数时将 id 设置为 0 可以让数据库自动（递增地）分配一个 id
 */
bool insertIntoUser(sqlite3* db, int id, char* name, char* password, char* email) {
	char* zErrMsg = 0; // 错误信息
	char sql[1024] = {0};
	if (id != 0) // 判断是否自动分配id
		sprintf(sql, "insert into user values(%d,'%s','%s','%s');", id, name, password, email);
	else
		sprintf(sql,"insert into user(name,password,email_addr) values('%s','%s','%s');", name, password, email);
	const int rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	if (rc == SQLITE_OK) {

		return true;
	}
	else {
		//fprintf(stderr, "inserting into user table failed: %s\n", zErrMsg);
		sqlite3_free(zErrMsg); 
		return false;
	}
}
/**
 * 插入到交易类别表，调用函数时将 id 设置为 0 可以让数据库自动（递增地）分配一个 id
 */
bool insertIntoTransactionClass(sqlite3* db, int id, char* class_name) {
	char* zErrMsg = 0; // 错误信息
	char sql[1024] = { 0 };
	if (id != 0) // 判断是否自动分配id
		sprintf(sql, "insert into transaction_classes values(%d,'%s');", id, class_name);
	else
		sprintf(sql, "insert into transaction_classes(class_name) values('%s');", class_name);
	const int rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	if (rc == SQLITE_OK) {
		return true;
	}
	else {
		//fprintf(stderr, "inserting into transaction_classes table failed: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return false;
	}
}
/**
 * 插入到交易表，调用函数时将 id 设置为 0 可以让数据库自动（递增地）分配一个 id。
 * 其中 transaction_date 的格式应当为 yyyy-mm-dd 例如：2019-11-11
 */
bool insertIntoTransactions(sqlite3* db, const int id, const bool type, const double amount, const int class_id, const int user_id, char* transaction_date) {
	char* zErrMsg = 0;
	char sql[1024] = { 0 };
	if (id != 0) // 判断是否自动分配id
		sprintf(sql, "insert into transactions values(%d,%s,%.2lf,%d,%d,'%s');",id, type ? "true" : "false",amount,class_id,user_id,transaction_date);
	else
		sprintf(sql, "insert into transactions(type,amount,class_id,user_id,transaction_date) values(%s,%lf,%d,%d,'%s');", type ? "true" : "false", amount, class_id, user_id, transaction_date);
	int rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);
	if (rc == SQLITE_OK) {
		return true;
	}
	else {
		//fprintf(stderr, "inserting into transactions table failed: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		return false;
	}
}