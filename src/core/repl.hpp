#pragma once

#include "js_interpreter.hpp"
#include <string>
#include <memory>

namespace kiren::repl {
    
    class REPL {
    public:
        REPL();
        ~REPL() = default;
        
        void start();
        void showWelcome();
        void showHelp();
        
    private:
        std::unique_ptr<js::SimpleInterpreter> interpreter_;
        
        std::string readLine(const std::string& prompt);
        bool processCommand(const std::string& input);
        std::string trim(const std::string& str);
    };
}
