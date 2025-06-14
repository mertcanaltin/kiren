#include <gtest/gtest.h>

TEST(BasicTest, GoogleTestWorks) {
    EXPECT_EQ(1 + 1, 2);
    EXPECT_TRUE(true);
}

TEST(BasicTest, StringComparison) {
    std::string hello = "Hello";
    std::string world = "World";
    
    EXPECT_NE(hello, world);
    EXPECT_EQ(hello.length(), 5);
}
