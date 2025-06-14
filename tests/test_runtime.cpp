#include <gtest/gtest.h>
#include "kiren/kiren.hpp"

class RuntimeTest : public ::testing::Test {
protected:
    void SetUp() override {
        runtime = kiren::createRuntime();
    }
    
    std::unique_ptr<kiren::Runtime> runtime;
};

TEST_F(RuntimeTest, CreateRuntime) {
    ASSERT_NE(runtime, nullptr);
}

TEST_F(RuntimeTest, ExecuteSimpleString) {
    EXPECT_TRUE(runtime->executeString("console.log(\"Hello Test!\");"));
}

TEST_F(RuntimeTest, ExecuteNonExistentFile) {
    EXPECT_FALSE(runtime->executeFile("non_existent_file.js"));
}
