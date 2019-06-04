#include "log_it.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include "../card/campus_card.h"
#include "../card/deposit_card.h"
#include "../general/generalFun.h"
namespace logit {
LogIt* LogIt::logCore = NULL;
LogIt* LogIt::Init(std::string rootAddr) {
  if (logCore == NULL) {
    logCore = new LogIt(rootAddr);
  }
  return logCore;
}
LogIt::LogIt(std::string _rootAddr) : rootAddr{_rootAddr} {
  log.close();
}

bool LogIt::IsSuccess() const {
  if (log.is_open()) return true;
  std::cout << "文件打开失败" << std::endl;
  return false;
}

bool LogIt::OpenTest(std::ofstream& out, std::string addr,
                     std::ios_base::openmode mode) {
  out.close();
  out.open(addr, mode);
  if (out.is_open()) return true;
  std::cout << "文件打开失败" << std::endl;
  return false;
}

bool LogIt::NewCard(const card::Card& current) {
  general::mkdir(rootAddr);
  std::string fileAddr = general::FormAddr(rootAddr, "", "systemLog.log");
  if (!OpenTest(log, fileAddr)) return false;
  log << general::GetCurrentTime() << "\t"
      << "[创建卡]\t"
      << "[卡类型]:\t" << current.GetCardType() << "\t"
      << "[标识符]:\t" << current.GetIdentifier() << "\t"
      << "[用户名]:\t" << current.GetName() << std::endl;
  return true;
}
bool LogIt::DeleteCard(const card::Card& current) {
  general::mkdir(rootAddr);
  std::string fileAddr = general::FormAddr(rootAddr, "", "systemLog.log");
  if (!OpenTest(log, fileAddr)) return false;
  log << general::GetCurrentTime() << "\t"
      << "[删除卡]\t"
      << "[卡类型]:\t" << current.GetCardType() << "\t"
      << "[标识符]:\t" << current.GetIdentifier() << "\t"
      << "[用户名]:\t" << current.GetName() << std::endl;
  return true;
}
bool LogIt::InnerAccount(const card::Card& current, std::string operation,
                         card::MoneyType amount) {
  std::string dirName = general::num2str(current.GetIdentifier());
  general::mkdir(dirName,rootAddr);
  std::string fileName = dirName + ".log";
  std::string fileAddr = general::FormAddr(rootAddr, dirName, fileName);
  if (!OpenTest(log, fileAddr)) return false;
  log << general::GetCurrentTime() << "\t"
      << "[账户操作]\t"
      << "[卡类型]:\t" << current.GetCardType() << "\t"
      << "[标识符]:\t" << current.GetIdentifier() << "\t"
      << "[用户名]:\t" << current.GetName() << "\t" << operation << "\t"
      << "[金额]\t" << amount << std::endl;
  return true;
}
bool LogIt::ExternalAccount(const card::Card& src, const card::Card& dest,
                            std::string operation, card::MoneyType amount) {
  std::string dirName = general::num2str(src.GetIdentifier());
  std::string fileName = dirName + ".log";
  std::string fileAddr = general::FormAddr(rootAddr, dirName, fileName);
  general::mkdir(dirName,rootAddr);
  if (!OpenTest(log, fileAddr)) return false;
  log << general::GetCurrentTime() << "\t"
      << "[账户操作]\t"
      << "[卡类型]:\t" << src.GetCardType() << "\t"
      << "[标识符]:\t" << src.GetIdentifier() << "\t"
      << "[用户名]:\t" << src.GetName() << "\t" << operation << "\t"
      << "[金额]\t" << amount << "到\t"
      << "[标识符]:\t" << dest.GetIdentifier() << "[用户名]:\t"
      << dest.GetName() << "\t"
      << "\t" << std::endl;
  return true;
}

}  // namespace logit