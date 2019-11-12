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

	
	
	// 初始化数据库：
	bool result = db_connect("test.db");
	ASSERT_EQ(result, true);
	drop_all_tables();
	result = init_db("db.sql");
	ASSERT_EQ(result, true);

	result = insertIntoUser(db, 1, "jerry", "pwd", "email");
	EXPECT_EQ(result, true);
	user* u = getUserById(db, 1);
	EXPECT_EQ(u->id, 1);
	EXPECT_EQ(strcmp(u->name, "jerry"), 0); // 这里要用 strcmp 是因为不能直接进行 char * 与 "jerry" 的比较
	EXPECT_EQ(strcmp(u->password, "pwd"), 0);
	EXPECT_EQ(strcmp(u->email_addr, "email"), 0);
	// ASSERT 和 EXPECT 的区别：
	// ASSERT 判断条件失败后，就会退出而不会继续判断，EXPECT 会继判断
	// 所以一般像连接数据库这样关键性的操作会用 ASSERT，而其他的会用 EXPECT

	u = getUserByName(db, "jerry");
	EXPECT_EQ(u->id, 1);
	EXPECT_EQ(strcmp(u->name, "jerry"), 0);
	EXPECT_EQ(strcmp(u->password, "pwd"), 0);
	EXPECT_EQ(strcmp(u->email_addr, "email"), 0);
}
TEST(TestTransactionClassModel, TestGetAndInsert) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);

	// 将数据库文件删除，重新开始创建数据库，以便进行测试
	remove("test.db");

	
	// 初始化数据库：
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

	// 将数据库文件删除，重新开始创建数据库，以便进行测试
	remove("test.db");
	// 初始化数据库：
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
	// 将数据库文件删除，重新开始创建数据库，以便进行测试
	remove("test.db");


	// 初始化数据库：
	bool result = db_connect("test.db");
	ASSERT_EQ(result, true);
	drop_all_tables();
	result = init_db("db.sql");
	ASSERT_EQ(result, true);

	int id = user_sign_up("jerry", "mima", "mima", "email"); // 因为这是数据库中第一个用户，所以 id 应当递增为1
	EXPECT_EQ(id, 1);
	
	
	id = user_sign_up("jerry1", "mima", "zhebushimima", "email"); // 测试密码输错的情况
	EXPECT_EQ(id,-1);

	id = user_sign_up("jerry", "mima", "mima", "email"); // 测试重复插入的情况
	EXPECT_EQ(id, -1);
}
int main(int argc,char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}