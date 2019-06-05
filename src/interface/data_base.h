/*该文件提供读入数据和写出数据的软件与硬盘交互方法
 *
 */
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
const std::string DEFAULT_ROOT_INDEX = "./DataFiles";
class Data_Base {
 private:
  std::ifstream inputFile;
  std::ofstream outputFile;
  std::string rootAddr;                   //根目录地址
  std::vector<std::string> userAddrList;  //用户列表，用来读入和写出用户信息
  static Data_Base* fileCore;
  cardSystem::card_storage*
      cardCore;  //程序管理系统，向其中读入存储在硬盘用户信息
  logit::LogIt* logCore;  //写出记录信息
  Data_Base(cardSystem::card_storage* _cardCore, logit::LogIt* _logCore,
            std::string _rootAddr = DEFAULT_ROOT_INDEX);

 public:
  ~Data_Base();
  static Data_Base* Init(cardSystem::card_storage* _cardCore,
                         logit::LogIt* _logCore,
                         std::string rootAddr = DEFAULT_ROOT_INDEX);
  std::string GetRootAddr() const;

  void SetRootAddr(std::string addr);
  bool WriteOutData();//写出全部数据
  bool WriteOutIndex(std::string rootAddr);//写出用户索引
  bool WriteOutAllUserInfo();//写出全部用户信息
  bool WriteOutUserInfo(std::string userAddr, card::Binding_Card* current);//写出用户信息

  bool ReadInAllData();//读入数据
  bool ReadInIndex();//读入索引
  bool ReadInUserData(std::string _userAdd);//读入用户数据文件
};
}  // namespace fileSystem

#endif