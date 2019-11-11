#include "process_record.h"
/**
 * �����û�id����ȡ�������û��йصĽ���
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
 * ��������û���Ϣ�����޵���ʹ��
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
