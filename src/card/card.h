/*@decription: This header file provide a class for card object
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
#include <string>
namespace card {

typedef int MoneyType;

class Card {
 private:
  std::string userName;
  std::string passwd;
  //  Time issueTime;

 public:
  // constructor & destructor
  Card(std::string _userName, std::string _passwd);
  ~Card();

  // accessors
  std::string GetName() const;
  std::string GetPasswd() const;
  virtual bool Deposit(MoneyType amount);
  virtual bool Withdraw(MoneyType amount);
  virtual bool Pay(MoneyType amount);
  virtual std::string LookUp();

  // mutators
  std::string SetName() const;
  std::string SetPasswd() const;
};

}  // namespace card

#endif