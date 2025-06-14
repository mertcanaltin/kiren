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
        
        // Public methods for testing and REPL
        Value evaluateExpression(const std::string& expr);
        bool parseLine(const std::string& line);
        
    private:
        std::unordered_map<std::string, Value> variables_;
        
        // Private helper methods
        bool executeConsoleLog(const std::string& args);
        bool executeVariableDeclaration(const std::string& line);
        std::string trim(const std::string& str);
    };
}
