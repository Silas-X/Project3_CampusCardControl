#include "binding_card.h"

namespace card {

Binding_Card::Binding_Card(const Campus_Card &campusCard,
                           const Deposit_Card &depositCard)
    : Campus_Card{campusCard}, Deposit_Card{depositCard} {}
// accessor
int Binding_Card::GetIdentifier() const { return Campus_Card::GetIdentifier(); }

// mutators
bool Binding_Card::AddNewCard(CardType cardType, const Card &card) {}
bool Binding_Card::AddCampusCard(Campus_Card &campusCard) {
  this->Campus_Card::Copy(campusCard);
  return true;
}
}  // namespace card