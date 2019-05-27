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
 protected:
  std::string userName;

 public:
  // constructor & destructor
  Card(std::string _userName, std::string _passwd);
  ~Card();

  // accessors
  std::string GetName() const;

  virtual std::string LookUp() = 0;

  // mutators
  virtual bool Deposit(MoneyType amount) = 0;
  virtual bool Withdraw(MoneyType amount) = 0;

  virtual bool Pay(MoneyType amount) = 0;

  std::string SetName() const;
};

class Campus_Card : virtual public Card {
 private:
  std::string studentId;
  std::string department;
  std::string passwd;

 public:
  // contructor & destructor;
  Campus_Card(std::string _userName, std::string _passwd);
  ~Campus_Card();

  // accessor
  std::string GetStudentId() const;
  std::string GetDepartment() const;
  std::string GetPasswd() const;

  // mutators
  bool SetStudentId(std::string id);
  bool SetDepartment(std::string department);
  std::string SetPasswd() const;

  bool Deposit(MoneyType amount);
  bool Withdraw(MoneyType amount);

  bool Pay(MoneyType amount);
  std::string LookUp();
};

class Deposit_Card : virtual public Card {
 private:
  MoneyType overDraft;  // The limit amount of making an overdraft;
  std::string passwd;

 public:
  // contructor & destructor;
  Deposit_Card(std::string _name, std::string _passwd);
  ~Deposit_Card();

};
}  // namespace card

#endif