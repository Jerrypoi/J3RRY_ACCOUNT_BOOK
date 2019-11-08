#include <gtest/gtest.h>
#include "db_connect.h"
#include "string.h"
#include "model.h"


TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
	// 将数据库文件删除，重新开始创建数据库
	remove("test.db");
	bool result = db_connect("test.db");
	ASSERT_EQ(result, true);
	result = init_db("db.sql");
	ASSERT_EQ(result, true);
	result = insertIntoUser(db, 1, "jerry", "pwd", "email");
	EXPECT_EQ(result, true);
	user u = getUserById(db, 1);
	EXPECT_EQ(u.id, 1);
	EXPECT_EQ(strcmp(u.name, "jerry"), 0); // 这里要用 strcmp 是因为不能直接进行 char * 与 "jerry" 的比较
	
}
int main(int argc,char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
}