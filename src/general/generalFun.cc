#include "generalFun.h"
#include <ctime>
#include <iostream>
namespace general {

int str2num(std::string str) {
  int num;
  std::stringstream ss;
  ss.clear();
  ss << str;
  ss >> num;
  return num;
}
char *GetCurrentTime() {
  time_t timer;
  timer = time(NULL);
  return ctime(&timer);
}
void Pause() {
  while (true) {
    std::string str;
    std::cout << "输入 X 以继续" << std::endl;
    getline(std::cin, str);
    if (str == "X" || str == "x") break;
  }
}
void mkdir(std::string addr) {
  std::string command = "mkdir " + addr;
  system(command.c_str());
}
}  // namespace general