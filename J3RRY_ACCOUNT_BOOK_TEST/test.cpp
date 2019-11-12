#include <gtest/gtest.h>
#include "db_connect.h"
#include "string.h"
#include <string>
#include "model.h"
#include "user_login.h"
#include "process_record.h"
#include "utilities.h"

TEST(TestUserModel, TestGetAndInsert) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);

	
	
	// ��ʼ�����ݿ⣺
	bool result = db_connect("test.db");
	ASSERT_EQ(result, true);
	drop_all_tables();
	result = init_db("db.sql");
	ASSERT_EQ(result, true);

	result = insertIntoUser(db, 1, "jerry", "pwd", "email");
	EXPECT_EQ(result, true);
	user* u = getUserById(db, 1);
	EXPECT_EQ(u->id, 1);
	EXPECT_EQ(strcmp(u->name, "jerry"), 0); // ����Ҫ�� strcmp ����Ϊ����ֱ�ӽ��� char * �� "jerry" �ıȽ�
	EXPECT_EQ(strcmp(u->password, "pwd"), 0);
	EXPECT_EQ(strcmp(u->email_addr, "email"), 0);
	// ASSERT �� EXPECT ������
	// ASSERT �ж�����ʧ�ܺ󣬾ͻ��˳�����������жϣ�EXPECT ����ж�
	// ����һ�����������ݿ������ؼ��ԵĲ������� ASSERT���������Ļ��� EXPECT

	u = getUserByName(db, "jerry");
	EXPECT_EQ(u->id, 1);
	EXPECT_EQ(strcmp(u->name, "jerry"), 0);
	EXPECT_EQ(strcmp(u->password, "pwd"), 0);
	EXPECT_EQ(strcmp(u->email_addr, "email"), 0);
}
TEST(TestTransactionClassModel, TestGetAndInsert) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);

	// �����ݿ��ļ�ɾ�������¿�ʼ�������ݿ⣬�Ա���в���
	remove("test.db");

	
	// ��ʼ�����ݿ⣺
	bool result = db_connect("test.db");
	ASSERT_EQ(result, true);
	drop_all_tables();
	result = init_db("db.sql");
	ASSERT_EQ(result, true);

	result = insertIntoTransactionClass(db, 1, "testclass");
	EXPECT_EQ(result, true);
	transaction_class* tc = getTransactionClassByID(db, 1);
	//EXPECT_NE(tc, NULL);
	EXPECT_EQ(tc->id, 1);
	EXPECT_EQ(strcmp(tc->class_name, "testclass"), 0);

	tc = getTransactionClassByName(db, "testclass");
	//EXPECT_NE(tc, NULL);
	EXPECT_EQ(tc->id, 1);
	EXPECT_EQ(strcmp(tc->class_name, "testclass"), 0);
}
TEST(TestTransactionModel, TestGetAndInsert) {

	// �����ݿ��ļ�ɾ�������¿�ʼ�������ݿ⣬�Ա���в���
	remove("test.db");
	// ��ʼ�����ݿ⣺
	bool result = db_connect("test.db");
	ASSERT_EQ(result, true);
	drop_all_tables();
	result = init_db("db.sql");
	ASSERT_EQ(result, true);

	result = insertIntoTransactionClass(db, 1, "testclass");
	ASSERT_EQ(result, true);
	result = insertIntoUser(db, 1, "jerry", "pwd", "email");
	ASSERT_EQ(result, true);

	result = insertIntoTransactions(db, 1, true, 1.1, 1, 1, "1999-01-01");
	EXPECT_EQ(result, true);
	transaction* t = getTransactionByID(db, 1);
	EXPECT_LE(abs(t->amount-1.1),0.000001);
	EXPECT_EQ(t->id, 1);
	EXPECT_EQ(t->class_id, 1);
	EXPECT_EQ(t->user_id, 1);
	EXPECT_EQ(strcmp(t->transaction_date, "1999-01-01"), 0);
	EXPECT_EQ(t->type, true);
	
}
TEST(TEST_FUNC,TEST_SIGN_UP)
{
	// �����ݿ��ļ�ɾ�������¿�ʼ�������ݿ⣬�Ա���в���
	remove("test.db");


	// ��ʼ�����ݿ⣺
	bool result = db_connect("test.db");
	ASSERT_EQ(result, true);
	drop_all_tables();
	result = init_db("db.sql");
	ASSERT_EQ(result, true);

	int id = user_sign_up("jerry", "mima", "mima", "email"); // ��Ϊ�������ݿ��е�һ���û������� id Ӧ������Ϊ1
	EXPECT_EQ(id, 1);
	
	
	id = user_sign_up("jerry1", "mima", "zhebushimima", "email"); // ���������������
	EXPECT_EQ(id,-1);

	id = user_sign_up("jerry", "mima", "mima", "email"); // �����ظ���������
	EXPECT_EQ(id, -1);
}
int main(int argc,char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}