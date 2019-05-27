#include "card.h"
#include <string>

namespace card {
Card::Card(std::string _userName, std::string _passwd)
    : userName{_userName}, passwd{_passwd} {}
Card::~Card() {}
std::string Card::GetName() const { return userName; }
bool Card::SetName(std::string _name) {
  userName = _name;
  return true;
}

}  // namespace card