#ifndef INTERFACE_H_
#define INTERFACE_H_
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../sys/controller.h"
#include "log_it.h"
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
  std::vector<card::Binding_Card*> foundedList;
  logit::LogIt* logCore;
  card::Binding_Card* selected;
  // std::vector<std::map<int, card::Binding_Card*>::iterator> foundedList;
  // std::map<int, card::Binding_Card*>::iterator selected;
  struct MenuType {
    void (Interface::*MenuInfo)();
    Menus (Interface::*MenuAction)(std::string message);
  };
  Interface(cardSystem::card_storage* _cardCorem, logit::LogIt* _logCore);
  static Interface* userInterface;
  cardSystem::card_storage* cardCore;

 public:
  static Interface* InitInterface(cardSystem::card_storage* _cardCore,
                                  logit::LogIt* _logCore);
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

  // API
  void LookUp();
  void Add();
  bool ChooseAccount();
  void Modify();
  void ModifyBasic();
  void ModifyCampus();
  void ModifyDeposit();
  void Delete();
  void Print(std::vector<card::Binding_Card*> list);
};
bool ReadInIdentifier(std::istream& in, int& num);
bool ReadInName(std::istream& in, std::string& str);
bool ReadInPasswd(std::istream& in, std::string& str);
bool ReadInBalance(std::istream& in, card::MoneyType& num);
bool ReadInOverdraft(std::istream& in, card::MoneyType& num);
bool ReadInCardCode(std::istream& in, std::string& message);
bool ReadInStudentId(std::istream& in, std::string& message);
bool ReadInDepartment(std::istream& in, std::string& message);
}  // namespace ui

#endif