//#define DEBUG_
#include "data_base.h"
#include <vector>
#include "../general/generalFun.h"
#include "interface.h"
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

Data_Base::~Data_Base() {
  cardCore = NULL;
  logCore = NULL;
}
std::string Data_Base::GetRootAddr() const { return rootAddr; }
void Data_Base::SetRootAddr(std::string addr) { rootAddr = addr; }

bool Data_Base::WriteOutData() {
  std::string command = "rm -rf " + rootAddr;
  system(command.c_str());
  WriteOutIndex(rootAddr);
  WriteOutAllUserInfo();
  return true;
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
  return true;
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
  return true;
}
bool Data_Base::ReadInAllData() {
  if (!ReadInIndex()) return false;
  std::vector<std::string>::iterator it = userAddrList.begin();
  while (it != userAddrList.end()) {
    ReadInUserData(*it);
    it++;
  }
  return true;
}
bool Data_Base::ReadInIndex() {
  std::ifstream in;
  std::string temp = rootAddr + "/Index.txt";
  in.open(temp, std::ifstream::in);
  if (!in.is_open()) {
    std::cout << "无法载入数据文档" << std::endl;
    return false;
  }
  std::string identifier;
  while (in >> identifier) {
    userAddrList.push_back(identifier);
  }
  in.close();
  return true;
}

bool Data_Base::ReadInUserData(std::string _userAddr) {
  bool campusCardFlag = false;
  bool depositCardFlag = false;
  int identifier;
  std::string name;
  std::string passwd;
  std::string department;
  std::string studentId;
  std::string cardCode;
  card::MoneyType balance;
  card::MoneyType overdraft;
  card::Campus_Card campusCard{};
  card::Deposit_Card depositCard{};

  std::ifstream in;
  std::string userAddr = rootAddr + "/" + _userAddr;
  std::string temp;
  temp = userAddr + "/CampusCard.txt";
  in.open(temp, std::ifstream::in);
  if (!in.is_open()) {
    std::cout << "无法载入数据文档" << std::endl;
    return false;
  }
  in >> campusCardFlag;
  if (campusCardFlag) {
    ui::ReadInIdentifier(in, identifier);
    ui::ReadInName(in, name);
    ui::ReadInPasswd(in, passwd);
    ui::ReadInStudentId(in, studentId);
    ui::ReadInDepartment(in, department);
    ui::ReadInBalance(in, balance);
    campusCard.SetIdentifier(identifier);
    campusCard.SetName(name);
    campusCard.SetPasswd(passwd);
    campusCard.SetStudentId(studentId);
    campusCard.SetDepartment(department);
    campusCard.SetBalance(balance);
    cardCore->AddCampusCard(campusCard);
  }
  in.close();
  temp = userAddr + "/DepositCard.txt";
  in.open(temp, std::ifstream::in);
  if (!in.is_open()) {
    std::cout << "无法载入数据文档" << std::endl;
    return false;
  }
  in >> depositCardFlag;
  if (depositCardFlag) {
    ui::ReadInIdentifier(in, identifier);
    ui::ReadInName(in, name);
    ui::ReadInPasswd(in, passwd);
    ui::ReadInCardCode(in, cardCode);
    ui::ReadInBalance(in, balance);
    ui::ReadInOverdraft(in, overdraft);
    depositCard.SetIdentifier(identifier);
    depositCard.SetName(name);
    depositCard.SetPasswd(passwd);
    depositCard.SetCardCode(cardCode);
    depositCard.SetBalance(balance);
    depositCard.SetOverdraft(overdraft);
    cardCore->AddDepositCard(depositCard);
  }
  in.close();

  temp = userAddr + "/Binding.txt";
  in.open(temp, std::ifstream::in);
  if (!in.is_open()) {
    std::cout << "无法载入数据文档" << std::endl;
    return false;
  }
  bool isBinded;
  in >> isBinded;
  if (isBinded) cardCore->BindingCard(identifier);
  in.close();
  return true;
}

}  // namespace fileSystem