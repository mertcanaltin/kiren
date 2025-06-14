#include "kiren/kiren.hpp"
#include "js_interpreter.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

namespace kiren {
    
    Runtime::Runtime() {
        std::cout << "🎨 Initializing Kiren Runtime..." << std::endl;
        setupGlobals();
        std::cout << "✨ Runtime ready for magic!" << std::endl;
    }
    
    Runtime::~Runtime() {
        std::cout << "🌙 Runtime shutdown complete" << std::endl;
    }
    
    bool Runtime::executeFile(const std::string& filepath) {
        if (!fileExists(filepath)) {
            std::cout << "❌ File not found: " << filepath << std::endl;
            return false;
        }
        
        std::string source = readFile(filepath);
        if (source.empty()) {
            std::cout << "❌ Could not read file: " << filepath << std::endl;
            return false;
        }
        
        return executeString(source, filepath);
    }
    
    bool Runtime::executeString(const std::string& code, const std::string& filename) {
        std::cout << "🎭 Executing: " << filename << std::endl;
        
        // Use our simple JavaScript interpreter
        js::SimpleInterpreter interpreter;
        bool success = interpreter.execute(code);
        
        if (success) {
            std::cout << "✅ Execution completed successfully!" << std::endl;
        } else {
            std::cout << "❌ Execution failed!" << std::endl;
        }
        
        return success;
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
        std::cout << "🌍 Setting up global environment..." << std::endl;
    }
    
    std::unique_ptr<Runtime> createRuntime() {
        return std::make_unique<Runtime>();
    }
}
