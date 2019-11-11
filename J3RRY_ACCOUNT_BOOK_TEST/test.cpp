#include <gtest/gtest.h>
#include "db_connect.h"
#include "string.h"
#include "model.h"


TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);

	// �����ݿ��ļ�ɾ�������¿�ʼ�������ݿ⣬�Ա���в���
	remove("test.db");

	
	// ��ʼ�����ݿ⣺
	bool result = db_connect("test.db");
	ASSERT_EQ(result, true);
	result = init_db("db.sql");
	ASSERT_EQ(result, true);

	
	result = insertIntoUser(db, 1, "jerry", "pwd", "email");
	EXPECT_EQ(result, true);
	user* u = getUserById(db, 1);
	EXPECT_EQ(u->id, 1);
	EXPECT_EQ(strcmp(u->name, "jerry"), 0); // ����Ҫ�� strcmp ����Ϊ����ֱ�ӽ��� char * �� "jerry" �ıȽ�
	// ASSERT �� EXPECT ������
	// ASSERT �ж�����ʧ�ܺ󣬾ͻ��˳�����������жϣ�EXPECT ����ж�
	// ����һ�����������ݿ������ؼ��ԵĲ������� ASSERT���������Ļ��� EXPECT

	u = getUserByName(db, "jerry");
	EXPECT_EQ(u->id, 1);
	EXPECT_EQ(strcmp(u->name, "jerry"), 0);
	EXPECT_EQ(strcmp(u->password, "pwd"), 0);
	EXPECT_EQ(strcmp(u->email_addr, "email"), 0);
}
int main(int argc,char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}