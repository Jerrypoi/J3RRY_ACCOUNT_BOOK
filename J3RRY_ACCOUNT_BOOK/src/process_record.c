#include "process_record.h"
llist* getTransactionByUserId(const int user_id)
{
	llist* list = llist_create(NULL);
	char sql[1024];
	sprintf(sql, "select * from transactions where user_id = %d;", user_id);
	sqlite3_exec(db, sql, callback_transaction, list, NULL);
	return list;
}
