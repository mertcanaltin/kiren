#pragma once

#include <string>
#include <memory>
#include <iostream>

namespace kiren {
    constexpr const char* VERSION = "0.1.0";
    
    class Runtime {
    public:
        Runtime();
        ~Runtime();
        
        bool executeFile(const std::string& filepath);
        bool executeString(const std::string& code, const std::string& filename = "<eval>");
        
        // Utility methods
        bool fileExists(const std::string& filepath);
        std::string readFile(const std::string& filepath);
        
    private:
        void setupGlobals();
    };
    
    // Factory function
    std::unique_ptr<Runtime> createRuntime();
}