#include <gtest/gtest.h>
#include "core/js_interpreter.hpp"

class JSInterpreterTest : public ::testing::Test {
protected:
    void SetUp() override {
        interpreter = std::make_unique<kiren::js::SimpleInterpreter>();
    }
    
    std::unique_ptr<kiren::js::SimpleInterpreter> interpreter;
};

TEST_F(JSInterpreterTest, ExecuteSimpleConsoleLog) {
    EXPECT_TRUE(interpreter->execute("console.log(\"Hello World\");"));
}

TEST_F(JSInterpreterTest, ExecuteVariableDeclaration) {
    EXPECT_TRUE(interpreter->execute("let x = 42;"));
}
