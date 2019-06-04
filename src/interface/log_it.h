#ifndef LOG_IT_H_
#define LOG_IT_H_
#include <fstream>
#include <vector>
#include "../card/campus_card.h"
#include "../card/card.h"
#include "../card/deposit_card.h"
namespace logit {
const std::string FileName = "logfile.log";

class LogIt {
 private:
  std::string logFile;
  std::ofstream log;
  LogIt();
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
  static LogIt* Init();
  ~LogIt();
  void PrintTime();
  bool IsSuccess() const;
  bool NewCard(const card::Card& current);
  bool DeleteCard(const card::Card& current);
  bool InnerAccount(const card::Card& current, std::string operation,
                    card::MoneyType amount = 0);
  bool ExternalAccount(const card::Card& src, const card::Card& dest,
                       std::string operation, card::MoneyType amount);
};
}  // namespace logit
#endif