#ifndef USER_LOGIN_H
#define USER_LOGIN_H
#ifdef __cplusplus
extern "C" {
#endif

extern int user_id;
/**
* @return ����ֵΪ�û��� id������¼ʧ�ܷ��� -1,
* @param user_name �û�����Ҫ���û�������Ψһ�ԣ���ע��ʱ����û����Ƿ�Ψһ
* @param password �û�����
*/
int login(char* user_name, char* password);

/**
 * @return ����ע��õ��û� id��������ע�����û������ٵ�¼һ�Ρ���ע��ʧ�ܷ��� -1
 * @param username �û�������û����������ݿ����û���Ӧ������Ψһ�ԣ������ڴ������ݿ��ʱ���Ѿ�Լ�����ˣ�����ֻ��Ҫ�жϲ�����Ƿ�ɹ����ɣ����ɹ�˵���û����ظ���
 * @param password �û���������롣
 * @param password_confirm �û��ڶ�����������룬������������Ӧ��һ��
 * @param email_address �û������ַ
 */
int user_sign_up(char* username, char* password, char* password_confirm, char* email_address);
#ifdef __cplusplus
}
#endif

#endif
