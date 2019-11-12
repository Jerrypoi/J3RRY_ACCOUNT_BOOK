#include "process_record.h"
#include "print.h"
#include "utilities.h"

/**
 * 根据用户id，获取所有与用户有关的交易
 */
llist* getTransactionByUserId(const int user_id)
{
	llist* list = llist_create(NULL);
	char sql[1024];
	sprintf(sql, "select * from transactions where user_id = %d;", user_id);
	sqlite3_exec(db, sql, callback_transaction, list, NULL);
	return list;
}
/**
 * 输出所有用户信息，仅限调试使用
 */
void printAllUser()
{
	llist* users = getAllUser();
	struct node* head = *users;
	while(head->data != NULL)
	{
		const user u = *(user*)head->data;
		printf("User:\n");
		printf("id: %d\n", u.id);
		printf("name: %s\n", u.name);
		printf("password: %s\n", u.password);
		printf("email: %s\n", u.email_addr);
		head = head->next;
		if (head == NULL)
			break;
	}
}


/**
 * @return 创建交易类别，若创建成功返回创建好的 id，若失败返回 -1
 * @param transaction_class 交易类别
 */
int create_transaction_class(char* transaction_class_name) {
	if (!insertIntoTransactionClass(db, 0, transaction_class_name)) {
		printf("This transaction class already exists.\n");
		return -1;
	}
	transaction_class* data = getTransactionClassByName(db, transaction_class_name);
	return data->id;
}
/**
 * @return 记录是否成功
 * @param type 收入还是支出，0 收入，1 支出
 * @param amount 交易金额
 * @param transaction_class_id 交易类别 id，调用这个函数前要调用 find_transaction_class 获取交易的 id
 * @param transaction_date 交易日期，如果为 NULL 则设置为系统时间的今天, 在 utilities.h 中有获取当前系统日期的函数。
 */
bool record_transaction(int type, double amount, int transaction_class_id, int user_id, const char* transaction_date) {
	if (transaction_date) {
		transaction_date = getSystemDate();
	}
	if (!insertIntoTransactions(db, 0, type, amount, transaction_class_id, user_id, transaction_date)) {
		printRed("record transaction failed");
		return false;
	}
	return true;
}

/**
 * @return 返回输入的交易类别的 id，如果不存在则返回 -1
 * @param transaction_class_name 交易类别
 */
int find_transaction_class(char* transaction_class_name) {
	transaction_class* data = getTransactionClassByName(db, transaction_class_name);
	if (!data) {
		return -1;
	}
	return data->id;
}
