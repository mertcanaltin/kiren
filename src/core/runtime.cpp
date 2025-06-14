#include "kiren/kiren.hpp"
#include "js_interpreter.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

namespace kiren {
    
    Runtime::Runtime() {
        // Silent initialization - no debug output
        setupGlobals();
    }
    
    Runtime::~Runtime() {
        // Silent cleanup
    }
    
    bool Runtime::executeFile(const std::string& filepath) {
        if (!fileExists(filepath)) {
            std::cerr << "kiren: " << filepath << ": No such file or directory" << std::endl;
            return false;
        }
        
        std::string source = readFile(filepath);
        if (source.empty()) {
            std::cerr << "kiren: Could not read file: " << filepath << std::endl;
            return false;
        }
        
        return executeString(source, filepath);
    }
    
    bool Runtime::executeString(const std::string& code, const std::string& filename) {
        // Direct execution - no debug messages
        js::SimpleInterpreter interpreter;
        return interpreter.execute(code);
    }
    
    bool Runtime::fileExists(const std::string& filepath) {
        return std::filesystem::exists(filepath);
    }
    
    std::string Runtime::readFile(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            return "";
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    
    void Runtime::setupGlobals() {
        // Silent setup
    }
    
    std::unique_ptr<Runtime> createRuntime() {
        return std::make_unique<Runtime>();
    }
}