#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <variant>
#include <iostream>

namespace kiren::js {
    
    using Value = std::variant<std::string, double, bool>;
    
    class SimpleInterpreter {
    public:
        bool execute(const std::string& code);
        
    private:
        std::unordered_map<std::string, Value> variables_;
        
        // Simple parsing functions
        bool parseLine(const std::string& line);
        bool executeConsoleLog(const std::string& args);
        bool executeVariableDeclaration(const std::string& line);
        
        Value evaluateExpression(const std::string& expr);
        std::string trim(const std::string& str);
    };
}
