#include "binding_card.h"

namespace card {
Binding_Card(const Campus_Card &campusCard, const Deposit_Card &depositCard)
    : Campus_Card{campusCard}, Deposit_Card{depositCard} {}
}  // namespace card