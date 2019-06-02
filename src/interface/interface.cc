#include "interface.h"
#include <iostream>
namespace ui {
Interface* Interface::userInterface = NULL;
Interface::Interface(cardSystem::card_storage* _cardCore)
    : cardCore{_cardCore} {}
Interface* Interface::InitInterface(cardSystem::card_storage* _cardCore) {
  if (userInterface == NULL) userInterface = new Interface{_cardCore};
  return userInterface;
}

int Interface::GetOpt() const { return opt; }

bool Interface::SetOpt(int _opt) { opt = _opt; }

bool Interface::Dispatch() {
  bool exitFlag = false;
  MenuType runMenu;
  while (true) {
    switch (GetOpt()) {
      case EXIT:
        exitFlag = true;
        break;
      case MAIN_MENU:
        runMenu.MenuInfo = &Interface::MainMenuInfo;
        runMenu.MenuAction = &Interface::MainMenu;
        break;
      case HOLDER_MENU:
        runMenu.MenuInfo = &Interface::HolderMenuInfo;
        runMenu.MenuAction = &Interface::HolderMenu;
        break;
      case CAMPUS_MENU:
        runMenu.MenuInfo = &Interface::CampusMenuInfo;
        runMenu.MenuAction = &Interface::CampusMenu;
        break;
      case DEPOSIT_MENU:
        runMenu.MenuInfo = &Interface::DepositMenuInfo;
        runMenu.MenuAction = &Interface::DepositMenu;
        break;
    }
    if (exitFlag) break;
    SetOpt(Guard(runMenu));
  }
}

Interface::Menus Interface::Guard(MenuType& currentMenu) {
  system("reset");
  StatusBar();
  std::string userMessage;
  (this->*currentMenu.MenuInfo)();
  std::getline(std::cin, userMessage);
  if (userMessage == "Exit") return EXIT;
  return (this->*currentMenu.MenuAction)(userMessage);
}

void Interface::MainMenuInfo() {
  std::cout << "   请选择所需的服务" << std::endl;
  std::cout << "[1]\t 管理全部持卡人信息" << std::endl;
  std::cout << "[2]\t 管理校园卡信息" << std::endl;
  std::cout << "[3]\t 管理储蓄卡信息" << std::endl;
  std::cout << "[0]\t 退出" << std::endl;
  std::cout << std::endl;
}

Interface::Menus Interface::MainMenu(std::string message) {
  int option = MAIN_MENU;
  if (!general::str2num(message, option) || option > DEPOSIT_MENU ||
      option < EXIT) {
    std::cout << "无效输入" << std::endl;
    return MAIN_MENU;
  }
  switch (option) {
    case 1:
      return HOLDER_MENU;
    case 2:
      return CAMPUS_MENU;
    case 3:
      return DEPOSIT_MENU;
    case 0:
      return EXIT;
  }
  return MAIN_MENU;
}

void Interface::HolderMenuInfo() {
  std::cout << "请选择所需的服务" << std::endl;
  std::cout << "[1]\t 显示全部持卡人信息" << std::endl;
  std::cout << "[2]\t 查询持卡人信息" << std::endl;
  std::cout << "[3]\t 添加持卡人信息" << std::endl;
  std::cout << "[4]\t 修改持卡人信息" << std::endl;
  std::cout << "[5]\t 注销持卡人信息" << std::endl;
  std::cout << "[0]\t 返回上级菜单" << std::endl;
}

Interface::Menus Interface::HolderMenu(std::string message) {
  int option;
  if (!general::str2num(message, option) || option > 6 || option < 0) {
    std::cout << "无效输入" << std::endl;
    return HOLDER_MENU;
  }
  switch (option) {
    case 0:
      return MAIN_MENU;
    case 1:
      cardCore->PrintAll("OneLine");
      getchar();
      break;
    case 2:
      LookUp();
      selected = (foundedList.empty()) ? NULL : *(foundedList.begin());
      Print(foundedList);
      getchar();
      break;
    case 3:
      Add();
      break;
    case 4:
      //      Modify();
    case 5:
      //      Delete();
    case 6:
      return MAIN_MENU;
  }
  return HOLDER_MENU;
}
void Interface::CampusMenuInfo() {}
Interface::Menus Interface::CampusMenu(std::string message) {
  return MAIN_MENU;
}
void Interface::DepositMenuInfo() {}
Interface::Menus Interface::DepositMenu(std::string message) {
  return MAIN_MENU;
}

void Interface::StatusBar() const {
  std::cout << "欢迎使用校园卡管理系统--version 0.1.0" << std::endl;
}

void Interface::LookUp() {
  foundedList.clear();
  std::cout << "请输入查询用户名或标识符" << std::endl;
  std::string message;
  int _identifier;
  getline(std::cin, message);
  card::Binding_Card* holder = NULL;

  if (general::str2num(message, _identifier)) {
    holder = cardCore->FindCard(_identifier);
    if (holder != NULL) foundedList.push_back(holder);
    return;
  }
  foundedList = cardCore->FindCard(message);
  return;
}

void Interface::Add() {
  std::cout << "请选择办卡类型" << std::endl;
  std::cout << "[1] 储蓄卡" << std::endl;
  std::cout << "[2] 校园卡" << std::endl;
  std::cout << "[3]同时办理并绑定" << std::endl;

  std::string message;
  std::cin >> message;
  int option;
  while (!general::str2num(message, option)) {
    std::cout << "输入有误,请重试" << std::endl;
    std::cin >> message;
  }
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
  card::Binding_Card bindingCard{};
  ui::ReadInIdentifier(std::cin, identifier);
  ui::ReadInName(std::cin, name);
  ui::ReadInPasswd(std::cin, passwd);

  if (option == 1 || option == 3) {
    std::cout << "Campus_Card" << std::endl;
    ui::ReadInStudentId(std::cin, studentId);
    ui::ReadInDepartment(std::cin, department);
    ui::ReadInBalance(std::cin, balance);
    campusCard.SetIdentifier(identifier);
    campusCard.SetName(name);
    campusCard.SetPasswd(passwd);
    campusCard.SetStudentId(studentId);
    campusCard.SetDepartment(department);
    campusCard.SetBalance(balance);
    cardCore->AddCampusCard(campusCard);
  }
  if (option == 2 || option == 3) {
    std::cout << "Deposit_Card" << std::endl;
    ui::ReadInCardCode(std::cin, cardCode);
    ui::ReadInOverdraft(std::cin, overdraft);
    ui::ReadInBalance(std::cin, balance);
    depositCard.SetIdentifier(identifier);
    depositCard.SetName(name);
    depositCard.SetPasswd(passwd);
    depositCard.SetCardCode(cardCode);
    depositCard.SetBalance(balance);
    depositCard.SetOverdraft(overdraft);
    cardCore->AddDepositCard(depositCard);
  }
  if (option == 3) {
    cardCore->BindingCard(campusCard, depositCard);
  }
}

void Interface::Print(std::vector<card::Binding_Card*> list) {
  if (list.empty()) {
    std::cout << "不存在任何结果！" << std::endl;
    return;
  }
  std::vector<card::Binding_Card*>::iterator it = list.begin();
  while (it != list.end()) {
    std::cout << (*it)->GetInfo() << std::endl;
    it++;
  }
  return;
}
bool ReadInIdentifier(std::istream& in, int& num) {
  if (in.rdbuf() == std::cin.rdbuf())
    std::cout << std::endl << "请输入您的身份识别号[ID]:\t";
  std::string message;
  in >> message;
  while (!general::str2num(message, num)) {
    std::cout << "输入有误,请重试" << std::endl;
    in >> message;
  }
  return true;
}

bool ReadInName(std::istream& in, std::string& str) {
  if (in.rdbuf() == std::cin.rdbuf())
    std::cout << std::endl << "请输入姓名:\t ";
  in >> str;
  return true;
}

bool ReadInPasswd(std::istream& in, std::string& str) {
  if (in.rdbuf() == std::cin.rdbuf())
    std::cout << std::endl << "请输入密码:\t ";
  in >> str;
  return true;
}
bool ReadInBalance(std::istream& in, card::MoneyType& num) {
  if (in.rdbuf() == std::cin.rdbuf())
    std::cout << std::endl << "请输入金额:\t ";
  std::string message;
  in >> message;
  while (!general::str2num(message, num) || num < 0) {
    std::cout << "输入有误,请重试" << std::endl;
    in >> message;
  }
  return true;
}
bool ReadInOverdraft(std::istream& in, card::MoneyType& num) {
  if (in.rdbuf() == std::cin.rdbuf())
    std::cout << std::endl << "请输入设置透支上限:\t ";
  std::string message;
  in >> message;
  while (!general::str2num(message, num)) {
    std::cout << "输入有误,请重试" << std::endl;
    in >> message;
  }
}

bool ReadInCardCode(std::istream& in, std::string& message) {
  if (in.rdbuf() == std::cin.rdbuf())
    std::cout << std::endl << "请输入卡号:\t ";
  in >> message;
}

bool ReadInStudentId(std::istream& in, std::string& message) {
  if (in.rdbuf() == std::cin.rdbuf())
    std::cout << std::endl << "请输入学号或教工号:\t ";
  in >> message;
}

bool ReadInDepartment(std::istream& in, std::string& message) {
  if (in.rdbuf() == std::cin.rdbuf())
    std::cout << std::endl << "请输入所属学院:\t ";
  in >> message;
}
}  // namespace ui
