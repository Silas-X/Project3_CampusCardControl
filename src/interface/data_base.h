#ifndef DATA_BASE_H_
#define DATA_BASE_H_
#include <fstream>
#include <string>
#include "../card/binding_card.h"
#include "../card/card.h"
#include "../general/generalFun.h"
#include "../sys/controller.h"
#include "log_it.h"

namespace fileSystem {
const std::string DEFAULT_ROOT_INDEX = "./DataFiles/";
class Data_Base {
 private:
  std::ifstream inputFile;
  std::ofstream outputFile;
  std::string rootAddr;
  std::vector<std::string> userAddrList;
  static Data_Base* fileCore;
  cardSystem::card_storage* cardCore;
  logit::LogIt* logCore;
  Data_Base(cardSystem::card_storage* _cardCore, logit::LogIt* _logCore,
            std::string _rootAddr = DEFAULT_ROOT_INDEX);

 public:
  static Data_Base* Init(cardSystem::card_storage* _cardCore,
                         logit::LogIt* _logCore,
                         std::string rootAddr = DEFAULT_ROOT_INDEX);
  std::string GetRootAddr() const;
  void SetRootAddr(std::string addr);
  bool WriteOutData();
  bool WriteOutIndex(std::string rootAddr);
  bool WriteOutUserInfo(std::string userAddr, card::Binding_Card* current);
  bool WriteOutAllUserInfo();
  bool ReadInAllData();
  bool ReadInIndex();
  bool ReadInUserData(std::string _userAdd);
};
}  // namespace fileSystem

#endif