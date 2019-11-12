//
// Created by Jerry Zhang on 10/31/19.
//
#ifndef MODEL_H
#define MODEL_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "llist.h"
#include <stdlib.h>
#include "db_connect.h"
#include "include/sqlite/sqlite3.h"
	/*

	*/
	/*
	create table 'user'(
		id integer primary key not null,
		name char(64),
		password char(64),
		email_addr text
	);
	*/
	typedef struct user {
		int id;
		char* name;
		char* password;
		char* email_addr;
	} user;
	/*
	create table 'transaction_classes'(
		id integer primary key not null,
		class_name char(64)
	);
	 */
	typedef struct transaction_class {
		int id;
		char* class_name;
	} transaction_class;

	/*
	create table 'transactions'(
		id integer primary key not null,
		type boolean not null,
		amount decimal(20,2) not null,
		class_id integer,
		user_id integer,
		transaction_date blob,
		FOREIGN KEY (class_id) references transaction_classes(id),
		foreign key (user_id) references user(id)
	);
	 */
	typedef struct transaction {
		int id;
		bool type; // false Ϊ���룬 true Ϊ֧��
		float amount;
		int class_id;
		int user_id;
		char* transaction_date;
	} transaction;
	typedef struct amount_and_classid {
		double amount;
		int class_id;
	} amount_and_classid;
	/**
	 * ����һ�ຯ���Ǹ���ָ�����Ի�ȡ����
	 * ������Ҳ��ɹ����᷵�� NULL
	 */
	user* getUserById(sqlite3* db, int id);
	transaction_class* getTransactionClassByID(sqlite3* db, int id);
	transaction* getTransactionByID(sqlite3* db, int id);
	user* getUserByName(sqlite3* db, char* name);
	transaction_class* getTransactionClassByName(sqlite3* db, char* name);
	
	llist* getAllTransaction();
	llist* getAllTransactionClass();
	llist* getAllUser();
	
	bool insertIntoUser(sqlite3* db, int id, char* name, char* password, char* email);
	bool insertIntoTransactionClass(sqlite3* db, int id, char* class_name);
	bool insertIntoTransactions(sqlite3* db, int id, bool type, double amount, int class_id, int user_id, char* transaction_date);
	/**
	 * Callback ��������� SQL ִ�н��
	 */
	int callback(void* NotUsed, int argc, char** argv, char** azColName);
	/**
	 * ��׼ callback ������������洢��������
	 */
	int callback_transaction_class(void* list, int argc, char** argv, char** azColName);
	int callback_transaction(void* list, int argc, char** argv, char** azColName);
	int callback_user(void* list, int argc, char** argv, char** azColName);
#ifdef __cplusplus
}
#endif
#endif // !MODEL_H
