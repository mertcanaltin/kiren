#include "js_interpreter.hpp"
#include <sstream>
#include <regex>
#include <algorithm>

namespace kiren::js {
    
    bool SimpleInterpreter::execute(const std::string& code) {
        std::stringstream ss(code);
        std::string line;
        
        std::cout << "🎭 Executing JavaScript with Kiren's built-in interpreter..." << std::endl;
        
        while (std::getline(ss, line)) {
            line = trim(line);
            if (line.empty() || (line.size() >= 2 && line[0] == '/' && line[1] == '/')) {
                continue; // Skip empty lines and comments
            }
            
            if (!parseLine(line)) {
                std::cout << "❌ Error parsing line: " << line << std::endl;
                return false;
            }
        }
        
        return true;
    }
    
    bool SimpleInterpreter::parseLine(const std::string& line) {
        // console.log(...)
        if (line.find("console.log") != std::string::npos) {
            size_t start = line.find('(');
            size_t end = line.rfind(')');
            if (start != std::string::npos && end != std::string::npos) {
                std::string args = line.substr(start + 1, end - start - 1);
                return executeConsoleLog(args);
            }
        }
        
        // Variable declarations: let x = 42;
        if (line.find("let ") == 0 || line.find("const ") == 0 || line.find("var ") == 0) {
            return executeVariableDeclaration(line);
        }
        
        return true; // Ignore unknown statements for now
    }
    
    bool SimpleInterpreter::executeConsoleLog(const std::string& args) {
        std::cout << "📝 ";
        
        // Simple string parsing
        if (args.size() >= 2 && args.front() == '"' && args.back() == '"') {
            // String literal
            std::string str = args.substr(1, args.length() - 2);
            std::cout << str;
        } else if (args.size() >= 2 && args.front() == '`' && args.back() == '`') {
            // Template literal - basic support
            std::string str = args.substr(1, args.length() - 2);
            
            // Simple ${variable} replacement
            size_t pos = 0;
            while ((pos = str.find("${", pos)) != std::string::npos) {
                size_t end = str.find("}", pos);
                if (end != std::string::npos) {
                    std::string expr = str.substr(pos + 2, end - pos - 2);
                    Value val = evaluateExpression(expr);
                    
                    std::string replacement;
                    if (std::holds_alternative<double>(val)) {
                        replacement = std::to_string((int)std::get<double>(val));
                    } else if (std::holds_alternative<std::string>(val)) {
                        replacement = std::get<std::string>(val);
                    }
                    
                    str.replace(pos, end - pos + 1, replacement);
                    pos += replacement.length();
                } else {
                    break;
                }
            }
            
            std::cout << str;
        } else {
            // Expression
            Value val = evaluateExpression(args);
            if (std::holds_alternative<double>(val)) {
                std::cout << std::get<double>(val);
            } else if (std::holds_alternative<std::string>(val)) {
                std::cout << std::get<std::string>(val);
            }
        }
        
        std::cout << std::endl;
        return true;
    }
    
    bool SimpleInterpreter::executeVariableDeclaration(const std::string& line) {
        // Parse: let x = 42; or let name = "value";
        size_t eq_pos = line.find('=');
        if (eq_pos == std::string::npos) return true;
        
        // Extract variable name
        std::string left = line.substr(0, eq_pos);
        size_t name_start = left.find(' ') + 1;
        std::string var_name = trim(left.substr(name_start));
        
        // Extract value
        std::string right = trim(line.substr(eq_pos + 1));
        if (!right.empty() && right.back() == ';') right.pop_back();
        
        Value value = evaluateExpression(right);
        variables_[var_name] = value;
        
        std::cout << "📦 Variable '" << var_name << "' = ";
        if (std::holds_alternative<double>(value)) {
            std::cout << std::get<double>(value);
        } else if (std::holds_alternative<std::string>(value)) {
            std::cout << "\"" << std::get<std::string>(value) << "\"";
        }
        std::cout << std::endl;
        
        return true;
    }
    
    Value SimpleInterpreter::evaluateExpression(const std::string& expr) {
        std::string trimmed = trim(expr);
        
        // Number literal
        if (!trimmed.empty() && (std::isdigit(trimmed[0]) || (trimmed[0] == '-' && trimmed.length() > 1))) {
            return std::stod(trimmed);
        }
        
        // String literal
        if (trimmed.size() >= 2 && trimmed.front() == '"' && trimmed.back() == '"') {
            return trimmed.substr(1, trimmed.length() - 2);
        }
        
        // Variable reference
        if (variables_.find(trimmed) != variables_.end()) {
            return variables_[trimmed];
        }
        
        // Simple arithmetic: x + y
        size_t plus_pos = trimmed.find(" + ");
        if (plus_pos != std::string::npos) {
            std::string left = trim(trimmed.substr(0, plus_pos));
            std::string right = trim(trimmed.substr(plus_pos + 3));
            
            Value left_val = evaluateExpression(left);
            Value right_val = evaluateExpression(right);
            
            if (std::holds_alternative<double>(left_val) && std::holds_alternative<double>(right_val)) {
                return std::get<double>(left_val) + std::get<double>(right_val);
            }
        }
        
        return std::string(trimmed); // Default to string
    }
    
    std::string SimpleInterpreter::trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }
}
