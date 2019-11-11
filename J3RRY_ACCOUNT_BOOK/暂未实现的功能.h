#pragma once
#include "model.h"
#include "db_connect.h"
#include "llist.h"
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
int sign_up(char* username, char* password, char* password_confirm, char* email_address);

/**
 * @return ��������Ľ������� id������������򷵻� -1
 * @param transaction_class �������
 */
int find_transaction_class(char* transaction_class);
/**
 * @return ������������������ɹ����ش����õ� id����ʧ�ܷ��� -1
 * @param transaction_class �������
 */
int create_transaction_class(char* transaction_class);
/**
 * @return ��¼�Ƿ�ɹ�
 * @param type ���뻹��֧����0 ���룬1 ֧��
 * @param amount ���׽��
 * @param transaction_class_id ������� id�������������ǰҪ���� find_transaction_class ��ȡ���׵� id
 * @param transaction_date �������ڣ����Ϊ NULL ������Ϊϵͳʱ��Ľ���, �� utilities.h ���л�ȡ��ǰϵͳ���ڵĺ�����
 */
bool record_transaction(int type, double amount, int transaction_class_id, char* transaction_date);

/**
 * �����û��Ľ��׼�¼��ע�⽻�׼�¼�������׼�¼���뽻������
 * ͬʱ�����Ľ��׼�¼ֻ�ܵ�����ǰ�Ѿ���¼���û��Ľ��׼�¼�����ܵ������˵�
 * @return �ɹ����� true��ʧ�� false
 * @param filename �û�����ĵ����ļ���
 */
bool export_data(char* filename);

/**
 * �����û����Ľ��׼�¼
 * @return �ɹ����� true��ʧ�� false
 */
bool import_data(char* filename);