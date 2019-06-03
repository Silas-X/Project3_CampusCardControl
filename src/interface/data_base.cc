//#define DEBUG_
#include "data_base.h"
#include <vector>
#include "../general/generalFun.h"
#ifdef DEBUG_
#include <iostream>
#endif
namespace fileSystem {
Data_Base* Data_Base::fileCore = NULL;
Data_Base::Data_Base(cardSystem::card_storage* _cardCore,
                     logit::LogIt* _logCore, std::string _rootAddr)
    : cardCore{_cardCore}, logCore{_logCore}, rootAddr{_rootAddr} {}
Data_Base* Data_Base::Init(cardSystem::card_storage* _cardCore,
                           logit::LogIt* _logCore, std::string _rootAddr) {
  if (fileCore == NULL)
    fileCore = new Data_Base{_cardCore, _logCore, _rootAddr};
  return fileCore;
}
std::string Data_Base::GetRootAddr() const { return rootAddr; }
void Data_Base::SetRootAddr(std::string addr) { rootAddr = addr; }

bool Data_Base::WriteOutData() {
  std::string command = "rm -rf " + rootAddr;
  system(command.c_str());
  WriteOutIndex(rootAddr);
  WriteOutAllUserInfo();
}

bool Data_Base::WriteOutIndex(std::string rootAddr) {
  std::ofstream out;
  general::mkdir(rootAddr);
  std::string temp = rootAddr + "/Index.txt";
  out.open(temp);
  userAddrList = cardCore->GetAllIdentifier();
  std::vector<std::string>::iterator it = userAddrList.begin();
  while (it != userAddrList.end()) {
    out << *it << std::endl;
    it++;
  }
  out.close();
}

bool Data_Base::WriteOutAllUserInfo() {
  std::vector<std::string>::iterator it = userAddrList.begin();
  while (it != userAddrList.end()) {
    std::string str = *it;
    WriteOutUserInfo(*it, cardCore->FindCard(general::str2num(str)));
    it++;
  }
  return true;
}

bool Data_Base::WriteOutUserInfo(std::string _userAddr,
                                 card::Binding_Card* current) {
  std::ofstream out;
  std::string temp;
  std::string userAddr = rootAddr + "/" + _userAddr;
  general::mkdir(userAddr);
  temp = userAddr + "/CampusCard.txt";
  out.open(temp, std::fstream::out);
  out << current->IsCampusCard() << std::endl;
  out << current->GetIdentifier() << std::endl;
  out << current->Campus_Card::GetName() << std::endl;
  out << current->Campus_Card::GetPassword() << std::endl;
  out << current->Campus_Card::GetStudentId() << std::endl;
  out << current->Campus_Card::GetDepartment() << std::endl;
  out << current->Campus_Card::GetBalance() << std::endl;
  out.close();
  temp = userAddr + "/DepositCard.txt";
  out.open(temp, std::fstream::out);
  out << current->IsDepositCard() << std::endl;
  out << current->GetIdentifier() << std::endl;
  out << current->Deposit_Card::GetName() << std::endl;
  out << current->Deposit_Card::GetPassword() << std::endl;
  out << current->Deposit_Card::GetCardCode() << std::endl;
  out << current->Deposit_Card::GetBalance() << std::endl;
  out << current->Deposit_Card::GetOverdraft() << std::endl;
  out.close();
  temp = userAddr + "/Binding.txt";
  out.open(temp, std::fstream::out);
  out << current->IsBinding() << std::endl;
  out.close();
}

bool ReadInIndex(std::string rootAddr) { std::ifstream in; }

}  // namespace fileSystem