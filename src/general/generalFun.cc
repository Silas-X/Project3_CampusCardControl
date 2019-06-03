#include "generalFun.h"
#include <ctime>
#include <iostream>
namespace general {
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
}  // namespace general