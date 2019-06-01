#ifndef DEPOSIT_CARD_H_
#define DEPOSIT_CARD_H_
#include "card.h"
namespace card {
const int DEFAULT_OVERDRAFT_LIMIT = 3000;  //默认透支上限

class Deposit_Card : public Card {
 private:
  MoneyType overdraft;  // The limit amount of making an overdraft;
  std::string cardCode;

 public:
  // contructor & destructor;
  Deposit_Card(int _identifer, std::string _name, std::string _passwd,
               std::string _cardCode, MoneyType balance = 0,
               int _overdraft = DEFAULT_OVERDRAFT_LIMIT);
  ~Deposit_Card();

  // accessor
  MoneyType GetOverdraft() const;
  std::string GetInfo() const;
  std::string GetCardCode() const;
  // mutator
  bool SetOverdraft(MoneyType amount);
  bool SetCardCode(std::string code);

  bool Deposit(MoneyType amount);
  bool Withdraw(MoneyType amount);
  bool Pay(MoneyType amount);
};
}  // namespace card

#endif