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
    std::string exclusion = "LISTENING";
    std::string pointerToExclusion = exclusion.c_str();
    int lengthOfExclusion = pointerToExclusion.length();
    int exists = result.find(exclusion);
    std::string PID = result.substr(exists + lengthOfExclusion + 4, 10);
    std::string command2 = "taskkill /PID " + PID + " /F";
    std::string secondResult = commandExecution(command2);
  } catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  return 0;
}