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
void mkdir(std::string addr, std::string rootAddr) {
  std::string command = "mkdir ";
  if (rootAddr != "") {
    command += rootAddr;
    command += "/" + addr;
  } else
    command = "mkdir " + addr;
  system(command.c_str());
}

std::string FormAddr(std::string rootAddr, std::string dir,
                     std::string fileName) {
  std::string str = "./" + rootAddr;
  if (dir != "") str += "/" + dir;
  if (fileName != "") str += "/" + fileName;
  return str;
}
}  // namespace general