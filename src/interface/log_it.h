/*该头文件提供记录日志的方法
 */
#ifndef LOG_IT_H_
#define LOG_IT_H_
#include <fstream>
#include <vector>
#include "../card/campus_card.h"
#include "../card/card.h"
#include "../card/deposit_card.h"
namespace logit {
const std::string DEFAULT_ROOT_ADDR = "./Logs";

class LogIt {
 private:
  std::string logFile;
  std::fstream log;
  std::string rootAddr;
  LogIt(std::string rootAddr = DEFAULT_ROOT_ADDR);
  static LogIt* logCore;

 public:
  enum LogType {
    NEW_CMPUS_CARD,
    NEW_DEPOSIT_CARD,
    DELETE_CAMPUS_CARD,
    DELETE_DEPOSIT_CARD,
    TRANSFER,
    WITHDRAW,
    PAY,
    DEPOSIT,
    READ_DATABASE,
    WRITE_IN_DATABASE
  };
  static LogIt* Init(std::string rootAddr = DEFAULT_ROOT_ADDR);
  ~LogIt();
  void PrintTime();
  bool IsSuccess() const;
  bool OpenTest(std::fstream& out, std::string addr,
                std::ios_base::openmode mode = std::ios_base::app);
  bool NewCard(const card::Card& current);     //写出创建卡片记录
  bool DeleteCard(const card::Card& current);  //写出删除卡片记录
  bool InnerAccount(
      const card::Card& current, std::string operation,
      card::MoneyType amount = 0);  //写出单账户自身操作，即不涉及其他账户信息
  bool ExternalAccount(
      const card::Card& src, const card::Card& dest, std::string operation,
      card::MoneyType amount);  //写出多用户操作，即转账等设计多用户操作
  bool GetUserLog(
      const card::Card& src,
      card::CardType cardType = card::CAMPUS_CARD);  //读入用户账户交易记录
};
}  // namespace logit
#endif