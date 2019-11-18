#include <gtest/gtest.h>
#include "ConnectDB.h"
#include "string.h"
#include <string>
#include "model.h"
#include "UserInteraction.h"
#include "ProcessRecord.h"
#include "utilities.h"

TEST(TEST_LIB, Test_list_lib)
{
	int data = 1;
	int second_data = 2;
	llist* list = llist_create(&data);
	EXPECT_EQ(*(int*)(*list)->data, 1);
	llist_push(list, &second_data);
	EXPECT_EQ(*(int*)(*list)->data, 2);
	int* ptr = static_cast<int*>(llist_pop(list));
	EXPECT_EQ(*ptr, 2);
	EXPECT_EQ(*(int*)(*list)->data, 1);
	llist_free(list);
}
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
	sqlite3_close(db);
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
	sqlite3_close(db);
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
	sqlite3_close(db);
}
TEST(TEST_FUNCTION, TEST_SIGN_UP)
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
	id = user_sign_up("jerry1", "mima", "mima", "email"); // 因为这是数据库中第一个用户，所以 id 应当递增为1
	EXPECT_EQ(id, 2);
	id = user_sign_up("jerry2", "mima", "mima", "email"); // 因为这是数据库中第一个用户，所以 id 应当递增为1
	EXPECT_EQ(id, 3);
	
	id = user_sign_up("jerry1", "mima", "zhebushimima", "email"); // 测试密码输错的情况
	EXPECT_EQ(id,-1);

	id = user_sign_up("jerry", "mima", "mima", "email"); // 测试重复插入的情况
	EXPECT_EQ(id, -1);
	sqlite3_close(db);
}
TEST(TEST_FUNCTION, Test_RECORD_TRNASACTION)
{
	// 将数据库文件删除，重新开始创建数据库，以便进行测试
	remove("test.db");


	// 初始化数据库：
	bool result = db_connect("test.db");
	ASSERT_EQ(result, true);
	drop_all_tables();

	result = init_db("db.sql");
	ASSERT_EQ(result, true);

	result = record_transaction(true, 2.1, 1, 1, "1999-01-01");
	result = record_transaction(true, 2.1, 1, 1, "1999-01-01");
	result = record_transaction(true, 3.1, 1, 2, "1999-01-01");
	EXPECT_EQ(result, true);
	transaction* t = getTransactionByID(db, 3);
	EXPECT_LE(abs(t->amount - 3.1), 0.000001);
	EXPECT_EQ(t->id, 3);
	EXPECT_EQ(t->class_id, 1);
	EXPECT_EQ(t->user_id, 2);
	EXPECT_EQ(strcmp(t->transaction_date, "1999-01-01"), 0);
	EXPECT_EQ(t->type, true);
	sqlite3_close(db);
}
TEST(TEST_FUNCTION,TEST_create_and_find_transaction_class)
{
	// 将数据库文件删除，重新开始创建数据库，以便进行测试
	remove("test.db");


	// 初始化数据库：
	bool result = db_connect("test.db");
	ASSERT_EQ(result, true);
	drop_all_tables();

	result = init_db("db.sql");
	ASSERT_EQ(result, true);
	const int id1 = create_transaction_class("test_transaction_class1");
	const int id2 = create_transaction_class("test_transaction_class2");
	EXPECT_NE(id1, -1);
	EXPECT_NE(id2, -1);
	const int find_id1 = find_transaction_class("test_transaction_class1");
	const int find_id2 = find_transaction_class("test_transaction_class2");
	EXPECT_EQ(id1, find_id1);
	EXPECT_EQ(id2, find_id2);
	sqlite3_close(db);
}
TEST(TEST_FUNCTION,TEST_get_transaction_by_user_id)
{
	// 将数据库文件删除，重新开始创建数据库，以便进行测试
	remove("test.db");


	// 初始化数据库：
	bool result = db_connect("test.db");
	ASSERT_EQ(result, true);
	drop_all_tables();

	result = init_db("db.sql");
	ASSERT_EQ(result, true);
	result = user_sign_up("jerry", "passwd", "passwd", "email");
	EXPECT_EQ(result, true);
	result = user_sign_up("tom", "passwd", "passwd", "email");
	EXPECT_EQ(result, true);

	result = record_transaction(true, 1, 1, 1, NULL);
	EXPECT_EQ(result, true);
	result = record_transaction(true, 1, 1, 2, NULL);
	EXPECT_EQ(result, true);
	llist* list = getTransactionByUserId(2);
	user u = *(user*)(*list)->data;
	EXPECT_EQ(u.id, 2);
	sqlite3_close(db);
}
TEST(TEST_FUNCTION,Test_getsysdate)
{
	const char* str = getSystemDate();
	EXPECT_NE(strstr(str, "2019"), nullptr); // This test case only works in 2019
}
TEST(TEST_FUNCTION,TEST_check_valid_email)
{
	char* str = const_cast<char*>("jerry@gmail.com");
	ASSERT_EQ(check_valid_email(str), 1);
	str = const_cast<char*>("jerrygmail.com");
	ASSERT_EQ(check_valid_email(str), 0);
	str = const_cast<char*>("jerry@gmailcom");
	ASSERT_EQ(check_valid_email(str), 0);
	str = const_cast<char*>("jerry");
	ASSERT_EQ(check_valid_email(str), 0);
}

TEST(TEST_FUNCTION,TEST_check_valid_date)
{
	char* date = "1999-01-01";
	ASSERT_EQ(check_valid_date(date), 1);
	date = "1999-1-1";
	ASSERT_EQ(check_valid_date(date), 1);
	date = "1999-01-1";
	ASSERT_EQ(check_valid_date(date), 1);
	date = "2000-01-01";
	ASSERT_EQ(check_valid_date(date), 1);
	date = "2000-10-31";
	ASSERT_EQ(check_valid_date(date), 1);
	date = "2013-1-31";
	ASSERT_EQ(check_valid_date(date), 1);
	date = "199-01-01";
	ASSERT_EQ(check_valid_date(date), 0);
	date = "2012-13-01";
	ASSERT_EQ(check_valid_date(date), 0);
	date = "2012-13-31";
	ASSERT_EQ(check_valid_date(date), 0);
}
int main(int argc,char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}