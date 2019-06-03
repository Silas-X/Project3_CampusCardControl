#include "log_it.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include "../card/campus_card.h"
#include "../card/deposit_card.h"
#include "../general/generalFun.h"
namespace logit {
LogIt* LogIt::logCore = NULL;
LogIt* LogIt::Init() {
  if (logCore == NULL) {
    logCore = new LogIt();
  }
  return logCore;
}
LogIt::LogIt() : logFile{"logfile.log"} {
  log.open(logFile, std::fstream::app);
}
bool LogIt::IsSuccess() const {
  if (log.is_open()) return true;
  std::cout << "文件打开失败" << std::endl;
  return false;
}
bool LogIt::NewCard(card::Card& current) {
  if (!IsSuccess()) return false;
  log << general::GetCurrentTime() << "\t"
      << "[创建卡]\t"
      << "[卡类型]:\t" << current.GetCardType() << "\t"
      << "[标识符]:\t" << current.GetIdentifier() << "\t"
      << "[用户名]:\t" << current.GetName() << std::endl;
  return true;
}
bool LogIt::DeleteCard(card::Card& current) {
  if (!IsSuccess()) return false;
  log << general::GetCurrentTime() << "\t"
      << "[删除卡]\t"
      << "[卡类型]:\t" << current.GetCardType() << "\t"
      << "[标识符]:\t" << current.GetIdentifier() << "\t"
      << "[用户名]:\t" << current.GetName() << std::endl;
  return true;
}
bool LogIt::InnerAccount(card::Card& current, std::string operation,
                         card::MoneyType amount) {
  if (!IsSuccess()) return false;
  log << general::GetCurrentTime() << "\t"
      << "[账户操作]\t"
      << "[卡类型]:\t" << current.GetCardType() << "\t"
      << "[标识符]:\t" << current.GetIdentifier() << "\t" << operation << "\t"
      << "[金额]\t" << amount << std::endl;
  return true;
}
bool LogIt::ExternalAccount(card::Card& src, card::Card& dest,
                            std::string operation, card::MoneyType amount) {
  if (!IsSuccess()) return false;
  log << general::GetCurrentTime() << "\t"
      << "[账户操作]\t"
      << "[卡类型]:\t" << src.GetCardType() << "\t"
      << "[标识符]:\t" << src.GetIdentifier() << "\t" << operation << "\t"
      << "[金额]\t" << amount << "到\t"
      << "[标识符]:\t" << dest.GetIdentifier() << "\t" << std::endl;
  return true;
}

}  // namespace logit