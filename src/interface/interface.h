#ifndef INTERFACE_H_
#define INTERFACE_H_
#include <string>
#include "../sys/controller.h"
namespace ui {

class Interface {
 public:
  enum Menus {
    EXIT = 0,
    MAIN_MENU,
    HOLDER_MENU,
    CAMPUS_MENU,
    DEPOSIT_MENU,
    STATUS_BAR
  };

 private:
  int opt;

  struct MenuType {
    void (Interface::*MenuInfo)();
    Menus (Interface::*MenuAction)(std::string message);
  };
  Interface(cardSystem::card_storage* _cardCore);
  static Interface* userInterface;
  cardSystem::card_storage* cardCore;

 public:
  static Interface* InitInterface(cardSystem::card_storage* _cardCore);
  bool Dispatch();
  ~Interface();

  // accessor
  int GetOpt() const;

  // mutator
  bool SetOpt(int _opt);

  Menus Guard(MenuType& currentMenu);
  void MainMenuInfo();  // MAIN_MENU
  Menus MainMenu(std::string message);
  void HolderMenuInfo();  // HOLDER_MENU
  Menus HolderMenu(std::string message);
  void CampusMenuInfo();  // CAMPUS_MENU
  Menus CampusMenu(std::string message);
  void DepositMenuInfo();  // DEPOSIT_MENU
  Menus DepositMenu(std::string message);

  void StatusBar() const;
};
}  // namespace ui

#endif