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
  Campus_Card(int _identifier = -1, std::string _userName = "NAN",
              std::string _passwd = "NAN", std::string _studentId = "NAN",
              std::string _department = "NAN", MoneyType _balance = 0);
  ~Campus_Card();

  // accessor
  std::string GetCardType() const;
  std::string GetStudentId() const;
  std::string GetDepartment() const;

  std::string GetInfo() const;
  // mutator
  void Copy(const Campus_Card& origin);
  void SetStudentId(std::string id);
  void SetDepartment(std::string department);

  bool Deposit(MoneyType amount);
  bool Withdraw(MoneyType amount);

  bool Pay(MoneyType amount);
};
}  // namespace card
#endif