#include "interface.h"
#include <limits.h>
#include <iostream>
#include "log_it.h"
namespace ui {
Interface* Interface::userInterface = NULL;
Interface::Interface(cardSystem::card_storage* _cardCore,
                     logit::LogIt* _logCore)
    : cardCore{_cardCore}, logCore{_logCore}, selected{NULL} {}
Interface* Interface::InitInterface(cardSystem::card_storage* _cardCore,
                                    logit::LogIt* _logCore) {
  if (userInterface == NULL) userInterface = new Interface{_cardCore, _logCore};
  return userInterface;
}
Interface::~Interface() {
  foundedList.clear();
  logCore = NULL;
  selected = NULL;
}
int Interface::GetOpt() const { return opt; }

bool Interface::SetOpt(int _opt) {
  opt = _opt;
  return true;
}

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
      case ACCOUNT_MENU:
        runMenu.MenuInfo = &Interface::AccountMainMenuInfo;
        runMenu.MenuAction = &Interface::AccountMainMenu;
        break;
    }
    if (exitFlag) break;
    SetOpt(Guard(runMenu));
  }
  return true;
}

Interface::Menus Interface::Guard(MenuType& currentMenu) {
  system("reset");
  StatusBar();
  std::string userMessage;
  (this->*currentMenu.MenuInfo)();
  // std::getline(std::cin, userMessage);
  std::cout << "输入Exit 以退出程序" << std::endl;
  std::cin >> userMessage;
  if (userMessage == "Exit") return EXIT;
  return (this->*currentMenu.MenuAction)(userMessage);
}

void Interface::MainMenuInfo() {
  std::cout << "   请选择所需的服务" << std::endl;
  std::cout << "[1]\t 管理全部持卡人信息" << std::endl;
  std::cout << "[2]\t 管理个人账户" << std::endl;
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
      return ACCOUNT_MENU;
    case 0:
      return EXIT;
  }
  return MAIN_MENU;
}

void Interface::HolderMenuInfo() {
  std::cout << "请选择所需的服务" << std::endl;
  std::cout << "[1]\t 显示 全部持卡人信息" << std::endl;
  std::cout << "[2]\t 查询/选择 持卡人信息" << std::endl;
  std::cout << "[3]\t 添加 持卡人信息" << std::endl;
  std::cout << "[4]\t 修改 持卡人信息" << std::endl;
  std::cout << "[5]\t 注销 持卡人信息" << std::endl;
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
      general::Pause();
      break;
    case 2:
      LookUp();
      selected = (foundedList.empty()) ? NULL : *(foundedList.begin());
      Print(foundedList);
      general::Pause();
      break;
    case 3:
      Add();
      break;
    case 4:
      Modify();
      break;
    case 5:
      Delete();
      break;
    case 6:
      return MAIN_MENU;
  }
  return HOLDER_MENU;
}

void Interface::AccountMainMenuInfo() {
  while (selected == NULL) {
    if (!ChooseAccount()) return;
  }
  std::cout << "请选择所需的服务" << std::endl;
  std::cout << "[1]\t 校园卡业务" << std::endl;
  std::cout << "[2]\t 储蓄卡业务" << std::endl;
  std::cout << "[3]\t 更换账户" << std::endl;
  std::cout << "[0]\t 返回上级菜单" << std::endl;
}

Interface::Menus Interface::AccountMainMenu(std::string message) {
  int option;
  if (!general::str2num(message, option) || option > 3 || option < 0) {
    std::cout << "无效输入" << std::endl;
    return MAIN_MENU;
  }
  switch (option) {
    case 0:
      return MAIN_MENU;
    case 1:
      system("reset");
      StatusBar();
      CampusAccount();
      break;
    case 2:
      system("reset");
      StatusBar();
      DepositAccount();
      break;
    case 3:
      selected = NULL;
      break;
  }
  return ACCOUNT_MENU;
}

void Interface::CampusAccount() {
  if (!selected->IsCampusCard()) {
    std::cout << "不存在" << std::endl;
    general::Pause();
    return;
  }
  std::cout << "请选择所需的服务" << std::endl;
  std::cout << "[1]\t 存款" << std::endl;
  std::cout << "[2]\t 取款" << std::endl;
  std::cout << "[3]\t 绑定账户转入" << std::endl;
  std::cout << "[4]\t 查询记录" << std::endl;
  std::cout << "[0]\t 返回上级菜单" << std::endl;
  std::string message;
  std::cin >> message;
  int option;
  while (!general::str2num(message, option)) {
    std::cout << "输入有误,请重试" << std::endl;
    std::cin >> message;
  }
  card::MoneyType amount;
  switch (option) {
    case 1:
      std::cout << "请输入金额" << std::endl;
      std::cin >> message;
      while (!general::str2num(message, amount)) {
        std::cout << "输入有误,请重试" << std::endl;
        std::cin >> message;
      }

      if (!cardCore->Deposit(amount, *selected, card::CAMPUS_CARD))
        std::cout << "操作失败" << std::endl;
      {
        std::cout << "操作成功" << std::endl;
        logCore->InnerAccount(card::Campus_Card{*selected}, "存款", amount);
      }
      break;

    case 2:
      std::cout << "请输入金额" << std::endl;
      std::cin >> message;
      while (!general::str2num(message, amount)) {
        std::cout << "输入有误,请重试" << std::endl;
        std::cin >> message;
      }

      if (!cardCore->Withdraw(amount, *selected, card::DEPOSIT_CARD))
        std::cout << "操作失败" << std::endl;
      {
        std::cout << "操作成功" << std::endl;
        logCore->InnerAccount(card::Campus_Card{*selected}, "取款", amount);
      }
      break;
    case 3:
      std::cout << "请输入金额" << std::endl;
      std::cin >> message;
      while (!general::str2num(message, amount)) {
        std::cout << "输入有误,请重试" << std::endl;
        std::cin >> message;
      }
      if (!cardCore->InternalTransfer(amount, selected, card::DEPOSIT_CARD,
                                      card::CAMPUS_CARD))
        std::cout << "操作失败" << std::endl;
      {
        std::cout << "操作成功" << std::endl;
        logCore->InnerAccount(card::Campus_Card{*selected}, "个人名下转账",
                              amount);
      }
      break;
    case 4:
      if (!logCore->GetUserLog(card::Campus_Card{*selected}, card::CAMPUS_CARD))
        std::cout << "无日志" << std::endl;
      else
        general::Pause();
      break;
    case 0:
      return;
  }
}

void Interface::DepositAccount() {
  if (!selected->IsDepositCard()) {
    std::cout << "不存在" << std::endl;
    general::Pause();
    return;
  }
  std::cout << "请选择所需的服务" << std::endl;
  std::cout << "[1]\t 存款" << std::endl;
  std::cout << "[2]\t 取款" << std::endl;
  std::cout << "[3]\t 转账" << std::endl;
  std::cout << "[4]\t 查询记录" << std::endl;
  std::cout << "[0]\t 返回上级菜单" << std::endl;
  std::string message;
  std::cin >> message;
  int option;
  while (!general::str2num(message, option)) {
    std::cout << "输入有误,请重试" << std::endl;
    std::cin >> message;
  }
  card::MoneyType amount;
  int target_account;
  switch (option) {
    case 1:
      std::cout << "请输入金额" << std::endl;
      std::cin >> message;
      while (!general::str2num(message, amount)) {
        std::cout << "输入有误,请重试" << std::endl;
        std::cin >> message;
      }
      if (!cardCore->Deposit(amount, *selected, card::DEPOSIT_CARD)) {
        std::cout << "操作失败" << std::endl;
        general::Pause();
      } else {
        std::cout << "操作成功" << std::endl;
        logCore->InnerAccount(card::Deposit_Card{*selected}, "存款", amount);
      }
      break;

    case 2:
      std::cout << "请输入金额" << std::endl;
      std::cin >> message;
      while (!general::str2num(message, amount)) {
        std::cout << "输入有误,请重试" << std::endl;
        std::cin >> message;
      }
      if (!cardCore->Withdraw(amount, *selected, card::DEPOSIT_CARD)) {
        std::cout << "操作失败" << std::endl;
        general::Pause();
      } else {
        std::cout << "操作成功" << std::endl;
        logCore->InnerAccount(card::Deposit_Card{*selected}, "取款", amount);
      }

      break;
    case 3:
      std::cout << "请输入金额" << std::endl;

      std::cin >> message;
      while (!general::str2num(message, amount)) {
        std::cout << "输入有误,请重试" << std::endl;
        std::cin >> message;
      };

      std::cout << "请输入目标账户" << std::endl;
      std::cin >> message;
      while (!general::str2num(message, target_account)) {
        std::cout << "输入有误,请重试" << std::endl;
        std::cin >> message;
      }

      if (!cardCore->ExternalTransfer(amount, selected,
                                      cardCore->FindCard(target_account))) {
        std::cout << "转账失败,请确认输入" << std::endl;
        general::Pause();
      } else {
        std::cout << "操作成功" << std::endl;
        logCore->ExternalAccount(
            card::Deposit_Card{*selected},
            card::Deposit_Card{*(cardCore->FindCard(target_account))}, "转出",
            amount);
        logCore->ExternalAccount(
            card::Deposit_Card{*(cardCore->FindCard(target_account))},
            card::Deposit_Card{*selected}, "收入", amount);
      }
      break;
    case 4:
      if (!logCore->GetUserLog(card::Deposit_Card{*selected},
                               card::DEPOSIT_CARD))
        std::cout << "无日志" << std::endl;
      else
        general::Pause();
      break;
    case 0:
      return;
  }
}

void Interface::StatusBar() const {
  std::cout << "欢迎使用校园卡管理系统--version 0.1.0" << std::endl;
  std::cout << "当前选择账户: ";
  if (selected == NULL)
    std::cout << "当前无选择账户" << std::endl;
  else {
    std::cout << selected->GetIdentifier() << " " << selected->GetName()
              << std::endl;
    if (selected->IsCampusCard())
      std::cout << "校园卡余额\t" << selected->Campus_Card::GetBalance()
                << std::endl;
    if (selected->IsDepositCard())
      std::cout << "储蓄卡余额\t" << selected->Deposit_Card::GetBalance()
                << std::endl;
  }

  std::cout << "===========================================" << std::endl;
}

void Interface::LookUp() {
  foundedList.clear();
  std::cout << "请输入查询/选择用户名或标识符" << std::endl;
  std::string message;
  int _identifier;
  // getline(std::cin, message);
  std::cin >> message;
  card::Binding_Card* holder = NULL;

  if (general::str2num(message, _identifier)) {
    holder = cardCore->FindCard(_identifier);
    if (holder != NULL)
      foundedList.push_back(holder);
    else
      std::cout << "未找到用户，请确认输入" << std::endl;
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
  ui::ReadInIdentifier(std::cin, identifier);
  ui::ReadInName(std::cin, name);

  if (option == 1 || option == 3) {
    AddDepositCard(identifier, name);
  }

  if (option == 2 || option == 3) {
    AddCampusCard(identifier, name);
  }

  if (option == 3) {
    cardCore->BindingCard(identifier);
  }
}

void Interface::AddCampusCard(int identifier, std::string name) {
  std::string passwd;
  std::string department;
  std::string studentId;
  card::MoneyType balance;
  card::Campus_Card campusCard{};

  std::cout << "Campus_Card" << std::endl;
  ui::ReadInStudentId(std::cin, studentId);
  ui::ReadInDepartment(std::cin, department);
  ui::ReadInPasswd(std::cin, passwd);
  ui::ReadInBalance(std::cin, balance);

  campusCard.SetIdentifier(identifier);
  campusCard.SetName(name);
  campusCard.SetPasswd(passwd);
  campusCard.SetStudentId(studentId);
  campusCard.SetDepartment(department);
  campusCard.SetBalance(balance);
  cardCore->AddCampusCard(campusCard);
  logCore->NewCard(campusCard);
}

void Interface::AddDepositCard(int identifier, std::string name) {
  std::string passwd;
  std::string cardCode;
  card::MoneyType balance;
  card::MoneyType overdraft;
  card::Deposit_Card depositCard{};

  std::cout << "Deposit_Card" << std::endl;
  ui::ReadInCardCode(std::cin, cardCode);
  ui::ReadInOverdraft(std::cin, overdraft);
  ui::ReadInPasswd(std::cin, passwd);
  ui::ReadInBalance(std::cin, balance);

  depositCard.SetIdentifier(identifier);
  depositCard.SetName(name);
  depositCard.SetPasswd(passwd);
  depositCard.SetCardCode(cardCode);
  depositCard.SetBalance(balance);
  depositCard.SetOverdraft(overdraft);
  cardCore->AddDepositCard(depositCard);
  logCore->NewCard(depositCard);
}

bool Interface::ChooseAccount() {
  std::cout << "请选择账户" << std::endl;
  std::cout << "[1] 显示全部账户" << std::endl;
  std::cout << "[2] 选择账户" << std::endl;
  std::cout << "[0] 返回上级菜单" << std::endl;
  int option;
  std::string message;
  std::cin >> message;
  while (!general::str2num(message, option)) {
    std::cout << "输入有误,请重试" << std::endl;
    std::cin >> message;
  }
  if (option == 0) return false;
  if (option == 1) {
    cardCore->PrintAll();
  }
  if (option == 2) {
    LookUp();
    selected = (foundedList.empty()) ? NULL : *(foundedList.begin());
  }
  return true;
}
void Interface::Modify() {
  bool exitFlag = false;
  while (selected == NULL) {
    if (!ChooseAccount()) return;
  }
  while (!exitFlag) {
    system("reset");
    StatusBar();
    std::cout << "请选择需要修改的卡片类型" << std::endl;
    std::cout << "[1] 修改基本信息" << std::endl;
    std::cout << "[2] 修改校园卡信息" << std::endl;
    std::cout << "[3] 修改储蓄卡信息" << std::endl;
    std::cout << "[4] 更改选择账户" << std::endl;
    std::cout << "[0] 返回上级菜单" << std::endl;
    int option;
    std::string message;
    std::cin >> message;
    while (!general::str2num(message, option)) {
      std::cout << "输入有误,请重试" << std::endl;
      std::cin >> message;
    }
    switch (option) {
      case 1:
        ModifyBasic();
        break;
      case 2:
        ModifyCampus();
        break;
      case 3:
        ModifyDeposit();
        break;
      case 4:
        ChooseAccount();
        break;
      case 0:
        exitFlag = true;
      default:
        std::cout << "无效输入" << std::endl;
    }
  }
  return;
}
void Interface::ModifyBasic() {
  bool exitFlag = false;
  while (!exitFlag) {
    system("reset");
    StatusBar();
    Print(std::vector<card::Binding_Card*>{selected});
    std::cout << "请选择需要修改的信息" << std::endl;
    std::cout << "[1] 修改姓名" << std::endl;
    std::cout << "[2] 修改密码" << std::endl;
    std::cout << "[0] 返回上级菜单" << std::endl;
    int option;
    std::string message;
    std::cin >> message;
    while (!general::str2num(message, option)) {
      std::cout << "输入有误,请重试" << std::endl;
      std::cin >> message;
    }
    std::string name;
    std::string passwd;
    card::MoneyType amount;
    switch (option) {
      case 1:
        ui::ReadInName(std::cin, name);
        selected->Campus_Card::SetName(name);
        selected->Deposit_Card::SetName(name);
        break;
      case 2:
        ui::ReadInPasswd(std::cin, passwd);
        selected->Campus_Card::SetPasswd(passwd);
        selected->Deposit_Card::SetPasswd(passwd);
        break;
      case 0:
        exitFlag = true;
        break;
    }
  }
}

void Interface::ModifyCampus() {
  if (!selected->IsCampusCard()) {
    std::cout << "不存在" << std::endl;
    general::Pause();
    return;
  }
  bool exitFlag = false;
  while (!exitFlag) {
    system("reset");
    StatusBar();
    Print(std::vector<card::Binding_Card*>{selected});
    std::cout << "请选择需要修改的信息" << std::endl;
    std::cout << "[1] 修改学号" << std::endl;
    std::cout << "[2] 修改学院" << std::endl;
    std::cout << "[3] 修改余额" << std::endl;
    std::cout << "[0] 返回上级菜单" << std::endl;
    int option;
    std::string message;
    std::cin >> message;
    while (!general::str2num(message, option)) {
      std::cout << "输入有误,请重试" << std::endl;
      std::cin >> message;
    }
    std::string studentId;
    std::string department;
    card::MoneyType amount;
    switch (option) {
      case 1:
        ui::ReadInStudentId(std::cin, studentId);
        selected->Campus_Card::SetStudentId(studentId);
        break;
      case 2:
        ui::ReadInDepartment(std::cin, department);
        selected->Campus_Card::SetDepartment(department);
        break;
      case 3:
        ui::ReadInBalance(std::cin, amount);
        selected->Campus_Card::SetBalance(amount);
        break;
      case 0:
        exitFlag = true;
        break;
    }
  }
}
void Interface::ModifyDeposit() {
  if (!selected->IsDepositCard()) {
    std::cout << "不存在" << std::endl;
    general::Pause();
    return;
  }
  bool exitFlag = false;
  while (!exitFlag) {
    system("reset");
    StatusBar();
    Print(std::vector<card::Binding_Card*>{selected});
    std::cout << "请选择需要修改的信息" << std::endl;
    std::cout << "[1] 修改卡号" << std::endl;
    std::cout << "[2] 修改余额" << std::endl;
    std::cout << "[3] 修改透支上限" << std::endl;
    std::cout << "[0] 返回上级菜单" << std::endl;
    int option;
    std::string message;
    std::cin >> message;
    while (!general::str2num(message, option)) {
      std::cout << "输入有误,请重试" << std::endl;
      std::cin >> message;
    }
    std::string cardCode;
    card::MoneyType amount;
    switch (option) {
      case 1:
        ui::ReadInCardCode(std::cin, cardCode);
        selected->Deposit_Card::SetCardCode(cardCode);
        break;
      case 2:
        ui::ReadInBalance(std::cin, amount);
        selected->Deposit_Card::SetBalance(amount);
        break;
      case 3:
        ui::ReadInOverdraft(std::cin, amount);
        selected->Deposit_Card::SetOverdraft(amount);
        break;
      case 0:
        exitFlag = true;
        break;
    }
  }
}

void Interface::Delete() {
  bool exitFlag = false;
  while (selected == NULL) {
    if (!ChooseAccount()) return;
  }
  while (!exitFlag) {
    system("reset");
    StatusBar();
    std::cout << "请选择需要删除的卡片类型" << std::endl;
    std::cout << "[1] 删除该账户" << std::endl;
    std::cout << "[2] 删除校园卡信息" << std::endl;
    std::cout << "[3] 删除储蓄卡信息" << std::endl;
    std::cout << "[4] 更改选择账户" << std::endl;
    std::cout << "[0] 返回上级菜单" << std::endl;
    int option;
    std::string message;
    std::cin >> message;
    while (!general::str2num(message, option)) {
      std::cout << "输入有误,请重试" << std::endl;
      std::cin >> message;
    }
    switch (option) {
      case 1: {
        card::Campus_Card temp = *cardCore->FindCard(selected->GetIdentifier());
        logCore->DeleteCard(temp);
        cardCore->DeleteCard(selected->GetIdentifier());
        selected = NULL;
        exitFlag = true;
        break;
      }
      case 2: {
        card::Campus_Card temp = *cardCore->FindCard(selected->GetIdentifier());
        logCore->DeleteCard(temp);
        cardCore->DeleteCampusCard(selected->GetIdentifier());
        break;
      }
      case 3: {
        card::Deposit_Card temp =
            *cardCore->FindCard(selected->GetIdentifier());
        logCore->DeleteCard(temp);
        cardCore->DeleteDepositCard(selected->GetIdentifier());
        break;
      }
      case 4:
        ChooseAccount();
        break;
      case 0:
        exitFlag = true;
      default:
        std::cout << "无效输入" << std::endl;
    }
  }
  if (selected != NULL && !selected->IsCampusCard() &&
      !selected->IsDepositCard()) {
    card::Deposit_Card temp = *cardCore->FindCard(selected->GetIdentifier());
    logCore->DeleteCard(temp);
    cardCore->DeleteDepositCard(selected->GetIdentifier());
    std::cout << "名下无任何信息，删除账户" << std::endl;
  }
  return;
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
    std::cout << std::endl
              << "请输入您的身份识别号[ID] 小于" << INT_MAX << ":\t";
  std::string message;
  in >> message;
  while (!general::str2num(message, num)) {
    std::cout << "输入有误,请重试1" << std::endl;
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
  return true;
}

bool ReadInCardCode(std::istream& in, std::string& message) {
  if (in.rdbuf() == std::cin.rdbuf())
    std::cout << std::endl << "请输入卡号:\t ";
  in >> message;
  return true;
}

bool ReadInStudentId(std::istream& in, std::string& message) {
  if (in.rdbuf() == std::cin.rdbuf())
    std::cout << std::endl << "请输入学号或教工号:\t ";
  in >> message;
  return true;
}

bool ReadInDepartment(std::istream& in, std::string& message) {
  if (in.rdbuf() == std::cin.rdbuf())
    std::cout << std::endl << "请输入所属学院:\t ";
  in >> message;
  return true;
}
}  // namespace ui