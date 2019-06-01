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
               const Deposit_Card &depositCard = Deposit_Card{"NAN", "NAN",
                                                              "NAN", 0, 0});
  int GetIdentifier() const;
};
}  // namespace card

#endif