#include <gtest/gtest.h>
#include "core/js_interpreter.hpp"

class VariableTest : public ::testing::Test {
protected:
    void SetUp() override {
        interpreter = std::make_unique<kiren::js::SimpleInterpreter>();
    }
    
    std::unique_ptr<kiren::js::SimpleInterpreter> interpreter;
};

TEST_F(VariableTest, EvaluateNumber) {
    auto result = interpreter->evaluateExpression("42");
    ASSERT_TRUE(std::holds_alternative<double>(result));
    EXPECT_EQ(std::get<double>(result), 42.0);
}

TEST_F(VariableTest, EvaluateString) {
    auto result = interpreter->evaluateExpression("\"Hello World\"");
    ASSERT_TRUE(std::holds_alternative<std::string>(result));
    EXPECT_EQ(std::get<std::string>(result), "Hello World");
}
