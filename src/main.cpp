#include "./sys/cardSystem.h"
#define DEBUG_
#ifdef DEBUG_
#include "./sys/cardSystem.cc"
#endif
int main() {
  cardSystem::CardSystem systemCore{};
  if (!systemCore.Launcher()) std::cout << "出错" << std::endl;
  return 0;
}