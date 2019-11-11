#include "��δʵ�ֵĹ���.h"
#include "utilities.h"

/**
 * @return ������������������ɹ����ش����õ� id����ʧ�ܷ��� -1
 * @param transaction_class �������
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
 * @return ��¼�Ƿ�ɹ�
 * @param type ���뻹��֧����0 ���룬1 ֧��
 * @param amount ���׽��
 * @param transaction_class_id ������� id�������������ǰҪ���� find_transaction_class ��ȡ���׵� id
 * @param transaction_date �������ڣ����Ϊ NULL ������Ϊϵͳʱ��Ľ���, �� utilities.h ���л�ȡ��ǰϵͳ���ڵĺ�����
 */
bool record_transaction(int type, double amount, int transaction_class_id, int user_id, char* transaction_date) {
	if (transaction_date) {
		transaction_date = getSystemDate();
	}
	if (!insertIntoTransactions(db, 0, type, amount, transaction_class_id, user_id, transaction_date)) {
		printf("record transaction failed");
		return false;
	}
	return true;
}





/**
 * @return ��������Ľ������� id������������򷵻� -1
 * @param transaction_class_name �������
 */
int find_transaction_class(char* transaction_class_name) {
	transaction_class* data = getTransactionClassByName(db, transaction_class_name);
	if (!data) {
		printf("There is no such transaction class.\n");
		return -1;
	}
	return data->id;
}