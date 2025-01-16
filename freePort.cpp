#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>

std::string executeCommand(const std::string& command) {
    std::string result;
    char buffer[128];
    
    std::shared_ptr<FILE> pipe(_popen(command.c_str(), "r"), _pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }

    // Read the output of the command
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }

    return result;
}

int main() {
    try {
        std::string command = "ls"; // Replace "ls" with your desired command
        std::string output = executeCommand(command);
        std::cout << "Command Output:\n" << output << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
