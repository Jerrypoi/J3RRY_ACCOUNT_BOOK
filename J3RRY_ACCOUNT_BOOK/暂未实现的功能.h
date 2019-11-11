#pragma once
#include "model.h"
#include "db_connect.h"
#include "llist.h"
/**
* @return 返回值为用户的 id，若登录失败返回 -1,
* @param user_name 用户名，要求用户名具有唯一性，在注册时检测用户名是否唯一
* @param password 用户密码
*/
int login(char* user_name, char* password);
/**
 * @return 返回注册好的用户 id，这样在注册完用户不用再登录一次。若注册失败返回 -1
 * @param username 用户输入的用户名，在数据库中用户名应当保持唯一性，这里在创建数据库的时候已经约束好了，所以只需要判断插入表是否成功即可（不成功说明用户名重复）
 * @param password 用户输入的密码。
 * @param password_confirm 用户第二次输入的密码，两次输入密码应当一致
 * @param email_address 用户邮箱地址
 */
int sign_up(char* username, char* password, char* password_confirm, char* email_address);

/**
 * @return 返回输入的交易类别的 id，如果不存在则返回 -1
 * @param transaction_class 交易类别
 */
int find_transaction_class(char* transaction_class);
/**
 * @return 创建交易类别，若创建成功返回创建好的 id，若失败返回 -1
 * @param transaction_class 交易类别
 */
int create_transaction_class(char* transaction_class);
/**
 * @return 记录是否成功
 * @param type 收入还是支出，0 收入，1 支出
 * @param amount 交易金额
 * @param transaction_class_id 交易类别 id，调用这个函数前要调用 find_transaction_class 获取交易的 id
 * @param transaction_date 交易日期，如果为 NULL 则设置为系统时间的今天, 在 utilities.h 中有获取当前系统日期的函数。
 */
bool record_transaction(int type, double amount, int transaction_class_id, char* transaction_date);

/**
 * 导出用户的交易记录，注意交易记录包括交易记录表与交易类别表。
 * 同时导出的交易记录只能导出当前已经登录的用户的交易记录，不能导出别人的
 * @return 成功返回 true，失败 false
 * @param filename 用户输入的导出文件名
 */
bool export_data(char* filename);

/**
 * 导入用户给的交易记录
 * @return 成功返回 true，失败 false
 */
bool import_data(char* filename);