#ifndef BINDING_CARD_H_
#define BINDING_CARD_H_
#include "campus_card.h"
#include "card.h"
#include "deposit_card.h"

namespace card {
class Binding_Card : public Campus_Card, public Deposit_Card {
 private:
 public:
  Binding_Card(const Campus_Card &campusCard,
               const Deposit_Card &depositCard = Deposit_Card{-1, "NAN", "NAN",
                                                              "NAN", 0, 0});
  // accessor
  int GetIdentifier() const;

  // mutator
  bool AddNewCard(CardType cardType, const Card &card);
  bool AddCampusCard(Campus_Card &campusCard);
};
}  // namespace card

#endif