#include "binding_card.h"

namespace card {

Binding_Card::Binding_Card(const Campus_Card &campusCard,
                           const Deposit_Card &depositCard)
    : Campus_Card{campusCard}, Deposit_Card{depositCard} {}
int Binding_Card::GetIdentifier() const { return Campus_Card::GetIdentifier(); }
}  // namespace card