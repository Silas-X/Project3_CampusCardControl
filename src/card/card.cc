#include "card.h"
#include <string>

namespace card {
Card::Card(int _identifier, std::string _userName, std::string _passwd,
           MoneyType _balance)
    : identifier{_identifier},
      userName{_userName},
      passwd{_passwd},
      balance{_balance} {}
Card::~Card() {}
// accessor
int Card::GetIdentifier() const { return identifier; }
std::string Card::GetName() const { return userName; }
std::string Card::GetPassword() const { return passwd; }
MoneyType Card::GetBalance() const { return balance; }
Date Card::GetIssueDate() const { return issueDate; }

// mutator
void Card::SetIdentifier(int _identifier) { identifier = _identifier; }
void Card::SetName(std::string _name) { userName = _name; }
void Card::SetPasswd(std::string _passwd) { this->passwd = _passwd; }

}  // namespace card
