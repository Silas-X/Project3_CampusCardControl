#ifndef DEPOSIT_CARD_H_
#define DEPOSIT_CARD_H_
#include "card/card.h"
namespace card {

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