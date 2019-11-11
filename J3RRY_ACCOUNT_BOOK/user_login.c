#include "user_login.h"
#include <stdio.h>
#include "model.h"
#include "print.h"
int user_id = -1;

/**
* @return ����ֵΪ�û��� id������¼ʧ�ܷ��� -1,
* @param user_name �û�����Ҫ���û�������Ψһ�ԣ���ע��ʱ����û����Ƿ�Ψһ
* @param password �û�����
*/
int login(char* user_name, char* password) {
	user* data = getUserByName(db, user_name);
	if (!data) {
		return -1;
	}
	if (strcmp(data->password, password) != 0) {
		return -1;
	}
	return data->id;
}

/**
 * @return ����ע��õ��û� id��������ע�����û������ٵ�¼һ�Ρ���ע��ʧ�ܷ��� -1
 * @param username �û�������û����������ݿ����û���Ӧ������Ψһ�ԣ������ڴ������ݿ��ʱ���Ѿ�Լ�����ˣ�����ֻ��Ҫ�жϲ�����Ƿ�ɹ����ɣ����ɹ�˵���û����ظ���
 * @param password �û���������롣
 * @param password_confirm �û��ڶ�����������룬������������Ӧ��һ��
 * @param email_address �û������ַ
 */
int sign_up(char* username, char* password, char* password_confirm, char* email_address) {
	if (strcmp(password, password_confirm) != 0) {
		printRed("Two passwords are inconsistent.\n");
		return -1;
	}
	if (!insertIntoUser(db, 0, username, password, email_address)) {
		printRed("Username already exists.\n");
		return -1;
	}
	user* data = getUserByName(db, username);
	return data->id;
}