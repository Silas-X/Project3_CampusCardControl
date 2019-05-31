#include "deposit_card.h"
namespace card {

Deposit_Card::Deposit_Card(std::string _name, std::string _passwd,
                           std::string _cardCode, MoneyType _balance,
                           MoneyType _overdraft)
    : Card{_name, _passwd, _balance},
      cardCode{_cardCode},
      overdraft{_overdraft} {}
Deposit_Card::~Deposit_Card() { overdraft = -1; }

// accessor
MoneyType Deposit_Card::GetOverdraft() const { return overdraft; }
std::string Deposit_Card::GetCardCode() const { return cardCode; }

std::string Deposit_Card::GetInfo() const {
  std::string InfoStr = "";
  InfoStr += "Card Type: Deposit Card";
  InfoStr += "\nHolder's Information:";
  InfoStr += "\n\tName:\t" + GetName();
  InfoStr += "\n\tSerial Number:\t" + GetCardCode();
  // TODO::明文和密文显示
  InfoStr += "\n\tPassword:\t" + GetPassword();
  InfoStr += "\n\tPassword:\t   ******";
  InfoStr += "\nAccount Information";
  InfoStr += "\n\t Balance:\t" + general::num2str(GetBalance());
  InfoStr += "\n\t Overdraft:\t" + general::num2str(GetOverdraft());
  return InfoStr;
}

// mutator
bool Deposit_Card::SetOverdraft(MoneyType amount = DEFAULT_OVERDRAFT_LIMIT) {
  if (amount < 0) return false;  //设定透支额度
  this->overdraft = amount;
  return true;
}

bool Deposit_Card::SetCardCode(std::string _cardCode) {
  // TODO::exceptions
  this->cardCode = _cardCode;
  return true;
}
bool Deposit_Card::Deposit(MoneyType amount) {
  if (amount < 0) return false;
  this->balance += amount;
  return true;
}
bool Deposit_Card::Withdraw(MoneyType amount) {
  if (amount < 0) return false;                  //判断amount输入正确
  if (this->balance - amount < 0) return false;  //取款不允许透支
  this->balance -= amount;
  return true;
}

bool Deposit_Card::Pay(MoneyType amount) {
  if (amount < 0) return false;  //判断amount输入正确
  if (this->balance + overdraft - amount < 0) return false;  //付款允许透支
  this->balance -= amount;
  return true;
}

}  // namespace card