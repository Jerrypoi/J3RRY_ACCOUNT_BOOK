#include <gtest/gtest.h>
#include "db_connect.h"
#include "string.h"
#include "model.h"
#include "暂未实现的功能.h"

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);

	// 将数据库文件删除，重新开始创建数据库，以便进行测试
	remove("test.db");

	
	// 初始化数据库：
	bool result = db_connect("test.db");
	ASSERT_EQ(result, true);
	result = init_db("db.sql");
	ASSERT_EQ(result, true);

	
	result = insertIntoUser(db, 1, "jerry", "pwd", "email");
	EXPECT_EQ(result, true);
	user* u = getUserById(db, 1);
	EXPECT_EQ(u->id, 1);
	EXPECT_EQ(strcmp(u->name, "jerry"), 0); // 这里要用 strcmp 是因为不能直接进行 char * 与 "jerry" 的比较
	// ASSERT 和 EXPECT 的区别：
	// ASSERT 判断条件失败后，就会退出而不会继续判断，EXPECT 会继判断
	// 所以一般像连接数据库这样关键性的操作会用 ASSERT，而其他的会用 EXPECT

	u = getUserByName(db, "jerry");
	EXPECT_EQ(u->id, 1);
	EXPECT_EQ(strcmp(u->name, "jerry"), 0);
	EXPECT_EQ(strcmp(u->password, "pwd"), 0);
	EXPECT_EQ(strcmp(u->email_addr, "email"), 0);
}

TEST(TEST_FUNC,TEST_SIGN_UP)
{
	// 将数据库文件删除，重新开始创建数据库，以便进行测试
	remove("test.db");


	// 初始化数据库：
	bool result = db_connect("test.db");
	ASSERT_EQ(result, true);
	result = init_db("db.sql");
	ASSERT_EQ(result, true);

	int id = sign_up("*", "mima", "mima", "email"); // 因为这是数据库中第一个用户，所以 id 应当递增为1
	EXPECT_EQ(id, 1);
	user* u = getUserByName(db, "*");
	
	
	id = sign_up("*", "mima", "zhebushimima", "email"); // 测试密码输错的情况
	EXPECT_EQ(id,-1);
}
int main(int argc,char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}