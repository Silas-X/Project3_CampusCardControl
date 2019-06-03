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
enum CardType { CAMPUS_CARD, DEPOSIT_CARD, ALL_CARD };
class Card_Base {
 protected:
  int identifier;
  std::string userName;

 public:
  Card_Base(int _identifier, std::string _username);
  int GetIdentifier() const;
  std::string GetName() const;
  void SetIdentifier(int _identifier);
  void SetName(std::string _name);
};

class Card : virtual public  Card_Base {
 protected:
  // int identifier;
  // std::string userName;
  std::string passwd;
  MoneyType balance;
  // TODO::增加卡片状态(激活，冻结，注销)
 public:
  // constructor & destructor
  Card(int _identifier, std::string _userName, std::string _passwd,
       MoneyType _balance = 0);
  ~Card();

  // accessors
  virtual std::string GetCardType() const = 0;
//  int GetIdentifier() const;
  //std::string GetName() const;
  std::string GetPassword() const;
  MoneyType GetBalance() const;
  virtual std::string GetInfo() const = 0;

  // mutator
  //void SetIdentifier(int _identifier);
  //void SetName(std::string _name);
  void SetPasswd(std::string _passwd);
  void SetBalance(MoneyType amount);
  virtual bool Deposit(MoneyType amount) = 0;
  virtual bool Withdraw(MoneyType amount) = 0;
  virtual bool Pay(MoneyType amount) = 0;
};

}  // namespace card

#endif