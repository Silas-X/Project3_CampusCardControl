#ifndef CAMPUS_CARD_H_
#define CAMPUS_CARD_H_
#include "card.h"

namespace card {
class Campus_Card : public Card {
 private:
  std::string studentId;
  std::string department;

 public:
  // contructor & destructor;
  Campus_Card(std::string _userName, std::string _passwd,
              std::string _studentId, std::string _department,
              MoneyType _balance = 0);
  ~Campus_Card();

  // accessor
  std::string GetStudentId() const;
  std::string GetDepartment() const;
  std::string GetPasswd() const;
  MoneyType GetBalance() const;
  
  std::string GetInfo() const;
  // mutator
  void SetStudentId(std::string id);
  void SetDepartment(std::string department);

  bool Deposit(MoneyType amount);
  bool Withdraw(MoneyType amount);

  bool Pay(MoneyType amount);
};
}  // namespace card
#endif