#include "repl.hpp"
#include <iostream>
#include <sstream>

namespace kiren::repl {
    
    REPL::REPL() {
        interpreter_ = std::make_unique<js::SimpleInterpreter>();
    }
    
    void REPL::start() {
        showWelcome();
        
        std::string input;
        while (true) {
            input = readLine("> ");
            input = trim(input);
            
            if (input == ".exit" || input == ".quit") {
                std::cout << "�� Goodbye! Thanks for using Kiren!" << std::endl;
                break;
            }
            
            if (input == ".help") {
                showHelp();
                continue;
            }
            
            if (input == ".clear") {
                std::cout << "\033[2J\033[H";
                showWelcome();
                continue;
            }
            
            if (input.empty()) {
                continue;
            }
            
            if (!processCommand(input)) {
                std::cout << "❌ Error executing command" << std::endl;
            }
        }
    }
    
    void REPL::showWelcome() {
        std::cout << "✨ Welcome to Kiren v0.1.0 REPL!" << std::endl;
        std::cout << "🚀 Type JavaScript code to execute, or .help for commands" << std::endl;
        std::cout << "🌟 Where JavaScript Dreams Take Flight!" << std::endl;
        std::cout << std::endl;
    }
    
    void REPL::showHelp() {
        std::cout << std::endl;
        std::cout << "🎮 Kiren REPL Commands:" << std::endl;
        std::cout << "  .help       Show this help message" << std::endl;
        std::cout << "  .exit       Exit the REPL" << std::endl;
        std::cout << "  .quit       Exit the REPL" << std::endl;
        std::cout << "  .clear      Clear the screen" << std::endl;
        std::cout << std::endl;
    }
    
    std::string REPL::readLine(const std::string& prompt) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        return line;
    }
    
    bool REPL::processCommand(const std::string& input) {
        return interpreter_->execute(input);
    }
    
    std::string REPL::trim(const std::string& str) {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }
}
