//
// Created by Jerry Zhang on 10/31/19.
//
#ifndef MODEL_H
#define MODEL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "llist.h"
#include <stdlib.h>
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
typedef struct user{
    int id;
    char *name;
    char *password;
    char *email_addr;
} user;
/*
create table 'transaction_classes'(
    id integer primary key not null,
    class_name char(64)
);
 */
typedef struct transaction_class{
    int id;
    char *class_name;
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
typedef struct transaction{
    int id;
    bool type;
    float amount;
    int class_id;
    int user_id;
    char *transaction_date;
} transaction;

user getUserById(sqlite3 *db,int id);
transaction_class getTransactionClassByID(sqlite3 *db,int id);
transaction getTransactionByID(sqlite3 *db,int id);
bool insertIntoUser(sqlite3* db, int id, char* name, char* password, char* email);
bool insertIntoTransactionClass(sqlite3* db, int id, char* class_name);
bool insertIntoTransactions(sqlite3* db, int id, bool type, double amount, int class_id, int user_id, char* transaction_date);
#endif // !MODEL_H
