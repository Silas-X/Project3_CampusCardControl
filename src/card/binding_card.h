/*提供校园卡和储蓄卡绑定的操作
 *
 *
 *
 */
#ifndef BINDING_CARD_H_
#define BINDING_CARD_H_
#include "campus_card.h"
#include "card.h"
#include "deposit_card.h"

namespace card {
class Binding_Card : public Campus_Card, public Deposit_Card {
 private:
  bool campusExist;
  bool depositExist;
  bool binding;

 public:
  Binding_Card();
  Binding_Card(const Campus_Card& campusCard);
  Binding_Card(const Deposit_Card& depositCard);
  Binding_Card(const Campus_Card& campusCard, const Deposit_Card& depositCard);

  // accessor
  int GetIdentifier() const;
  int GetStatus() const;
  std::string GetInfo() const;
  bool IsCampusCard() const;
  bool IsDepositCard() const;
  bool IsBinding() const;

  // mutator
  bool AddNewCard(CardType cardType, Card* card);
  bool AddCampusCard(Campus_Card* campusCard);
  bool AddDepositCard(Deposit_Card* depositCard);
  //设置标志位
  bool SetBindingCards();//设置绑定标志位
  bool SetCampusStatus(bool status = false);
  bool SetDepositStatus(bool status = false);

  // Account Operations
  bool Deposit(MoneyType amount, CardType targetCard = DEPOSIT_CARD);
  bool Withdraw(MoneyType amount, CardType targetCard = ALL_CARD);
  bool Pay(MoneyType amount, CardType targetCard = ALL_CARD);
  bool Transfer(MoneyType amount, CardType src = DEPOSIT_CARD,
                CardType dest = CAMPUS_CARD);
};

}  // namespace card

#endif