#include "card.h"
#include <string>

namespace card {
Card_Base::Card_Base(int _identifier, std::string _username)
    : identifier{_identifier}, userName{_username} {}

Card::Card(int _identifier, std::string _userName, std::string _passwd,
           MoneyType _balance)
    :  // identifier{_identifier},
       // userName{_userName},
      Card_Base{_identifier, _userName},
      passwd{_passwd},
      balance{_balance} {}
Card::~Card() {}
// accessor
int Card_Base::GetIdentifier() const { return identifier; }
std::string Card_Base::GetName() const { return userName; }
std::string Card::GetPassword() const { return passwd; }
MoneyType Card::GetBalance() const { return balance; }

// mutator
void Card_Base::SetIdentifier(int _identifier) { identifier = _identifier; }
void Card_Base::SetName(std::string _name) { userName = _name; }
void Card::SetPasswd(std::string _passwd) { this->passwd = _passwd; }
void Card::SetBalance(MoneyType amount) { this->balance = amount; }
}  // namespace card
