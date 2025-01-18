#include<iostream>
#include<string>
#include<memory>
#include<cstdio>

std::string commandExecution(const std::string& command) {
  std::string result;
  char buffer[128];
  std::shared_ptr<FILE> pipe(_popen(command.c_str(), "r"), _pclose);

  while(fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
    result += buffer;
  } 

  return result;
}

int main(int args, char* argv[]) {
  const std::string portNumber = argv[1];
  try {
    std::string command = "netstat -ano | findstr :" + portNumber;
    std::string result = commandExecution(command);
    std::cout << result << std::endl;
    size_t pidStart = result.find("LISTENING");
    std::cout << pidStart << std::endl;
    std::string PID = result.substr(pidStart + 9, 13);
    PID.erase(PID.find_last_not_of(" \t\n\r") + 1);
    std::string killCommand = "taskkill /PID " + PID + " /F";
    std::cout << killCommand << std::endl;
    std::string secondResult = commandExecution(killCommand);
    std::cout << secondResult << std::endl;
  } catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  return 0;
}