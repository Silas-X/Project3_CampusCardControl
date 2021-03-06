#include "campus_card.h"
#include <string>
namespace card {
Campus_Card::Campus_Card(int _identifier, std::string _userName,
                         std::string _passwd, std::string _studentId,
                         std::string _department, MoneyType _balance)
    : Card_Base{_identifier, _userName},
      Card{_identifier, _userName, _passwd, _balance} {
  this->studentId = _studentId;
  this->department = _department;
}

Campus_Card::~Campus_Card() {
  this->studentId = -1;
  this->department = -1;
}
// accessor
std::string Campus_Card::GetCardType() const { return "Campus_Card"; }
std::string Campus_Card::GetStudentId() const { return studentId; }
std::string Campus_Card::GetDepartment() const { return department; }
std::string Campus_Card::GetInfo() const {
  std::string InfoStr = "";
  InfoStr += "\nCard Type:\t" + GetCardType();
  InfoStr += "\nHolder's Information:";
  InfoStr += "\n\tName:\t" + GetName();
  InfoStr += "\n\tStudent ID:\t" + GetStudentId();
  InfoStr += "\n\tDepartment:\t" + GetDepartment();
  InfoStr += "\nAccount Information";
  InfoStr += "\n\t Balance:\t" + general::num2str(GetBalance());
  return InfoStr;
}

// mutator
void Campus_Card::Copy(const Campus_Card &origin) {
  this->SetName(origin.GetName());
  this->SetPasswd(origin.GetPassword());
  this->SetStudentId(origin.GetStudentId());
  this->SetDepartment(origin.GetDepartment());
  this->SetIdentifier(origin.GetIdentifier());
  this->SetBalance(origin.GetBalance());
  return;
}

void Campus_Card::SetStudentId(std::string id) { this->studentId = id; }
void Campus_Card::SetDepartment(std::string department) {
  this->department = department;
}

bool Campus_Card::Deposit(MoneyType amount) {
  if (amount <= 0) return false;
  this->balance += amount;
  return true;
}

bool Campus_Card::Withdraw(MoneyType amount) {
  if (this->balance - amount < 0) return false;
  this->balance -= amount;
  return true;
}

bool Campus_Card::Pay(MoneyType amount) { return Withdraw(amount); }

}  // namespace card