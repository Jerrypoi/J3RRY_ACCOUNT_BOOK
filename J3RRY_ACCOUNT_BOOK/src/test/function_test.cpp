//
// Created by Jerry Zhang on 11/6/19.
//
#include <gtest/gtest.h>
#include "../model.h"
TEST(test_class_name,test_case_2) {
    EXPECT_EQ(2,2) << "Use << to output a string if this line of test fails\n";

}
TEST(test_class_name, test_case_name) {
    ASSERT_EQ(1,1);
    ASSERT_NE(1,2);
    ASSERT_FALSE(false);
    ASSERT_GE(2,1);

}

int main(int argc,char *argv[]) {
    testing::InitGoogleTest(&argc,argv);
    RUN_ALL_TESTS();
    return 0;
}