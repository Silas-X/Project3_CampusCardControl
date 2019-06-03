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
  Deposit_Card(int _identifer = -1, std::string _name = "NAN",
               std::string _passwd = "NAN", std::string _cardCode = "NAN",
               MoneyType balance = 0, int _overdraft = DEFAULT_OVERDRAFT_LIMIT);
  ~Deposit_Card();

  // accessor
  MoneyType GetOverdraft() const;
  std::string GetCardCode() const;
  std::string GetCardType() const;
  std::string GetInfo() const;

  // mutator
  void Copy(const Deposit_Card &origin);

  bool SetOverdraft(MoneyType amount);
  bool SetCardCode(std::string code);

  bool Deposit(MoneyType amount);
  bool Withdraw(MoneyType amount);
  bool Pay(MoneyType amount);
};
}  // namespace card

#endif