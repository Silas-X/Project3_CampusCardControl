#include "binding_card.h"

namespace card {
Binding_Card::Binding_Card() : campusExist{false}, depositExist{false} {}
Binding_Card::Binding_Card(const Campus_Card &campusCard)
    : Campus_Card{campusCard},
      Deposit_Card{},
      campusExist{true},
      depositExist{false} {}
Binding_Card::Binding_Card(const Deposit_Card &depositCard)
    : Campus_Card{},
      Deposit_Card{depositCard},
      campusExist{false},
      depositExist{true} {}
Binding_Card::Binding_Card(const Campus_Card &campusCard,
                           const Deposit_Card &depositCard)
    : Campus_Card{campusCard},
      Deposit_Card{depositCard},
      campusExist{true},
      depositExist{true} {}
// accessor
int Binding_Card::GetIdentifier() const { return Campus_Card::GetIdentifier(); }
std::string Binding_Card::GetInfo() const {
  std::string res;
  res = "Identifier:\t " + general::num2str(GetIdentifier());
  res += "\n";
  res += IsCampusCard() ? Campus_Card::GetInfo() : "Campus_Card: Not Exist";
  res += "\n";
  res += IsDepositCard() ? Deposit_Card::GetInfo() : "Deposit_Card: Not Exist";
  res += "\nStatus:\t";
  res += IsBinding() ? "\nBINDED" : "\nNOT BINDED";
  return res;
}


bool Binding_Card::IsCampusCard() const { return campusExist; }
bool Binding_Card::IsDepositCard() const { return depositExist; }
bool Binding_Card::IsBinding() const { return binding; }

// mutators//子类利用父类指针传递但无法执行进一步操作，再次利用其子类性质操作
// TODO:如何利用多态的性质从而实现一个函数能够传递多个函数再分发？
bool Binding_Card::AddNewCard(CardType cardType, Card *current) {
  this->Campus_Card::SetIdentifier(current->GetIdentifier());
  this->Campus_Card::SetName(current->GetName());
  switch (cardType) {
    case CAMPUS_CARD:
      return AddCampusCard(dynamic_cast<Campus_Card *>(current));
      break;
    case DEPOSIT_CARD:
      return AddDepositCard(dynamic_cast<Deposit_Card *>(current));
    default:
      break;
  }
  return false;
}

bool Binding_Card::AddCampusCard(Campus_Card *campusCard) {
  this->Campus_Card::Copy(*campusCard);
  this->campusExist = true;
  return true;
}

bool Binding_Card::AddDepositCard(Deposit_Card *depositCard) {
  this->Deposit_Card::Copy(*depositCard);
  this->depositExist = true;
  return true;
}
bool Binding_Card::SetBindingCards() {
  this->binding = (campusExist & depositExist);
  return this->binding;
}
bool Binding_Card::SetCampusStatus(bool status) {
  this->campusExist = status;
  return true;
}
bool Binding_Card::SetDepositStatus(bool status) {
  this->depositExist = status;
  return true;
}
// Account Operations
bool Binding_Card::Deposit(MoneyType amount, CardType targetCard) {
  if (targetCard == CAMPUS_CARD) return this->Campus_Card::Deposit(amount);
  if (targetCard == DEPOSIT_CARD) return this->Deposit_Card::Deposit(amount);
  return false;
}

bool Binding_Card::Withdraw(MoneyType amount, CardType targetCard) {
  if (amount < 0) return false;
  if (targetCard == CAMPUS_CARD) return this->Campus_Card::Withdraw(amount);
  if (targetCard == DEPOSIT_CARD) return this->Deposit_Card::Withdraw(amount);
  // targetCard==ALL_CARD;
  if (this->Campus_Card::Withdraw(amount)) return true;
  if (this->Deposit_Card::Withdraw(amount)) return true;
  if (this->Campus_Card::balance + this->Deposit_Card::balance +
          this->Deposit_Card::GetOverdraft() >=
      amount) {
    if (this->Deposit_Card::Withdraw(amount - this->Campus_Card::balance) &&
        this->Campus_Card::Withdraw(this->Campus_Card::balance))
      return true;
  }
  return false;
}

bool Binding_Card::Pay(MoneyType amount, CardType targetCard) {
  if (amount < 0) return false;
  if (targetCard == CAMPUS_CARD) return this->Campus_Card::Pay(amount);
  if (targetCard == DEPOSIT_CARD) return this->Deposit_Card::Pay(amount);
  // targetCard==ALL_CARD;
  if (this->Campus_Card::Pay(amount)) return true;
  if (this->Deposit_Card::Pay(amount)) return true;
  if (this->Campus_Card::balance + this->Deposit_Card::balance +
          this->Deposit_Card::GetOverdraft() >=
      amount) {
    if (this->Deposit_Card::Pay(amount - this->Campus_Card::balance) &&
        this->Campus_Card::Pay(this->Campus_Card::balance))
      return true;
  }
  return false;
}

bool Binding_Card::Transfer(MoneyType amount, CardType src, CardType dest) {
  if (src == dest) return false;
  if (src == CAMPUS_CARD) {
    if (!this->Campus_Card::Withdraw(amount)) return false;
    this->Deposit_Card::Deposit(amount);
    return true;
  }
  if (src == DEPOSIT_CARD) {
    if (!this->Deposit_Card::Withdraw(amount)) return false;
    this->Campus_Card::Deposit(amount);
    return true;
  }
  return false;
}

}  // namespace card