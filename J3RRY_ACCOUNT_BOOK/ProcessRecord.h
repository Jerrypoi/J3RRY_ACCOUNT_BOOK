#ifndef PROCESS_RECORD_H
#define PROCESS_RECORD_H
#include "llist.h"
#include "ConnectDB.h"
#include "stdio.h"
#include "stdlib.h"
#include "model.h"
#ifdef __cplusplus
extern "C" {
#endif

	llist* getTransactionByUserId(const int user_id);
	void printAllUser();

	/**
	 * @return 创建交易类别，若创建成功返回创建好的 id，若失败返回 -1
	 * @param transaction_class 交易类别
	 */
	int create_transaction_class(const char* transaction_class_name);
	/**
	 * @return 记录是否成功
	 * @param type 收入还是支出，0 收入，1 支出
	 * @param amount 交易金额
	 * @param transaction_class_id 交易类别 id，调用这个函数前要调用 find_transaction_class 获取交易的 id
	 * @param transaction_date 交易日期，如果为 NULL 则设置为系统时间的今天, 在 utilities.h 中有获取当前系统日期的函数。
	 */
	bool record_transaction(int type, double amount, int transaction_class_id, int user_id, const char* transaction_date);
	/**
	 * @return 返回输入的交易类别的 id，如果不存在则返回 -1
	 * @param transaction_class_name 交易类别
	 */
	int find_transaction_class(const char* transaction_class_name);
#ifdef __cplusplus
}
#endif

#endif /*PROCESS_RECORD_H*/