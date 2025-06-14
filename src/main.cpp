#include <iostream>
#include <vector>
#include <string>
#include "kiren/kiren.hpp"

void showHelp() {
    std::cout << "✨ Kiren - Where JavaScript Dreams Take Flight!\n\n";
    std::cout << "Usage:\n";
    std::cout << "  kiren run <file>      🚀 Run JavaScript/TypeScript file\n";
    std::cout << "  kiren help            ❓ Show this help\n";
    std::cout << "  kiren version         📋 Show version info\n";
    std::cout << "\nExamples:\n";
    std::cout << "  kiren run app.js\n";
    std::cout << "  kiren run server.ts\n";
    std::cout << "\n🌟 Happy coding!\n";
}

void showVersion() {
    std::cout << "Kiren v" << kiren::VERSION << " 🚀\n";
    std::cout << "Built with love and C++20 ✨\n";
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv + 1, argv + argc);
    
    if (args.empty()) {
        showHelp();
        return 0;
    }
    
    const std::string& command = args[0];
    
    if (command == "help" || command == "-h" || command == "--help") {
        showHelp();
    }
    else if (command == "version" || command == "-v" || command == "--version") {
        showVersion();
    }
    else if (command == "run") {
        if (args.size() < 2) {
            std::cout << "❌ Error: Please specify a file to run\n";
            std::cout << "💡 Try: kiren run app.js\n";
            return 1;
        }
        
        std::string filename = args[1];
        auto runtime = kiren::createRuntime();
        
        if (!runtime->executeFile(filename)) {
            return 1;
        }
    }
    else {
        std::cout << "❌ Unknown command: " << command << std::endl;
        std::cout << "💡 Try: kiren help\n";
        return 1;
    }
    
    return 0;
}