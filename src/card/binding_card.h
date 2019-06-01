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
  Binding_Card(const Campus_Card &campusCard);
  Binding_Card(const Deposit_Card &depositCard);
  Binding_Card(const Campus_Card &campusCard, const Deposit_Card &depositCard);

  // accessor
  int GetIdentifier() const;
  int GetStatus() const;
  std::string GetInfo() const;
  bool IsCampusCard() const;
  bool IsDepositCard() const;
  bool IsBinding() const;

  // mutator
  bool AddNewCard(CardType cardType, Card *card);
  bool AddCampusCard(Campus_Card *campusCard);
  bool AddDepositCard(Deposit_Card *depositCard);
  bool SetBindingCards();

  // Account Operations
  bool Deposit(MoneyType amount, CardType targetCard = DEPOSIT_CARD);
  bool Withdraw(MoneyType amount);

  bool Pay(MoneyType amount);
  bool Transfer(MoneyType amount, CardType src = DEPOSIT_CARD,
                CardType dest = CAMPUS_CARD);
};
}  // namespace card

#endif