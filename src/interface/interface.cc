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
    case 4:
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
  std::cout << "[6]\t 返回上级菜单" << std::endl;
}

Interface::Menus Interface::HolderMenu(std::string message) {
  return MAIN_MENU;
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
}  // namespace ui