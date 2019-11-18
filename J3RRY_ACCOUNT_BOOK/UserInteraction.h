#ifndef USER_LOGIN_H
#define USER_LOGIN_H
#ifdef __cplusplus
extern "C" {
#endif

extern int user_id;
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
int user_sign_up(char* username, char* password, char* password_confirm, char* email_address);
#ifdef __cplusplus
}
#endif

#endif
