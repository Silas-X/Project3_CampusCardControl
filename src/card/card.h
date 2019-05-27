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
#include "general\generalFun.h"

namespace card {
using general::num2str;
using general::str2num;

typedef int MoneyType;

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
  std::string userName;
  std::string passwd;
  MoneyType balance;
  Date issueDate;

 public:
  // constructor & destructor
  Card(std::string _userName, std::string _passwd);
  ~Card();

  // accessors
  std::string GetName() const;

  virtual std::string LookUp() = 0;

  // mutator
  virtual bool Deposit(MoneyType amount) = 0;
  virtual bool Withdraw(MoneyType amount) = 0;

  virtual bool Pay(MoneyType amount) = 0;

  bool SetName(std::string _name);
  bool SetPasswd(std::string _passwd);
};

class Campus_Card : public Card {
 private:
  std::string studentId;
  std::string department;

 public:
  // contructor & destructor;
  Campus_Card(std::string _userName, std::string _passwd);
  ~Campus_Card();

  // accessor
  std::string GetStudentId() const;
  std::string GetDepartment() const;
  std::string GetPasswd() const;

  // mutator
  bool SetStudentId(std::string id);
  bool SetDepartment(std::string department);

  bool Deposit(MoneyType amount);
  bool Withdraw(MoneyType amount);

  bool Pay(MoneyType amount);
  std::string LookUp();
};

class Deposit_Card : public Card {
 private:
  MoneyType overDraft;  // The limit amount of making an overdraft;

 public:
  // contructor & destructor;
  Deposit_Card(std::string _name, std::string _passwd);
  ~Deposit_Card();

  // accessor
  MoneyType GetLimitation() const;

  // mutator
  bool SetOverdraft();

  bool Deposit(MoneyType amount);
  bool Withdraw(MoneyType amount);
  bool Transfer(std::string account, MoneyType amount);
  bool Pay(MoneyType amount);
};
}  // namespace card

#endif