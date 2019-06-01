/*@description: This header file provide a class for card object
 *@author: Silas XU
 *@time: May-27-2019
 *@regulation
 *@     Naming Rules:
        class
            Name-> Pascal Case,
            Member Data -> underscore+trailing underscores
            Member Function -> Pascal Case
             variable -> camel Case
 *
 */

#ifndef SRC_CARD_CARD_H_
#define SRC_CARD_CARD_H_
#include <regex>
#include <sstream>
#include <string>
#include "../general/generalFun.h"

namespace card {
using general::num2str;
using general::str2num;

typedef int MoneyType;
enum ErrorType { INVALID_AMOUNT };
enum CardType { CAMPUS_CARD, DEPOSIT_CARD };

struct Date {
  int year;
  int month;
  int day;
  Date(int y = 0, int m = 0, int d = 0) : year{y}, month{m}, day{d} {}
  bool SetYear(int year) {
    this->year = year;
    return true;
  }
  bool SetMonth(int month) {
    this->month = month;
    return true;
  }
  bool SetDay(int day) {
    this->day = day;
    return true;
  }
  std::string GetDate() {
    std::string res = "Year: " + num2str(year) + "\nMonth: " + num2str(month) +
                      "\nDay: " + num2str(day);
    return res;
  }
};

class Card {
 protected:
  int identifier;
  std::string userName;
  std::string passwd;
  MoneyType balance;
  Date issueDate;
  // TODO::增加卡片状态(激活，冻结，注销)
 public:
  // constructor & destructor
  Card(int _identifier, std::string _userName, std::string _passwd,
       MoneyType _balance = 0);
  ~Card();

  // accessors
  int GetIdentifier() const;
  std::string GetName() const;
  std::string GetPassword() const;
  MoneyType GetBalance() const;
  Date GetIssueDate() const;
  virtual std::string GetInfo() const = 0;

  // mutator
  void SetIdentifier(int _identifier);
  void SetName(std::string _name);
  void SetPasswd(std::string _passwd);

  virtual bool Deposit(MoneyType amount) = 0;
  virtual bool Withdraw(MoneyType amount) = 0;
  virtual bool Pay(MoneyType amount) = 0;
};

}  // namespace card

#endif