/*该头文件提供与用户交互的界面
 *通过调用cardCore的方法执行具体任务
 *调用logCore方法执行记录任务
 */
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
    ACCOUNT_MENU,
    STATUS_BAR
  };

 private:
  int opt;
  std::vector<card::Binding_Card*> foundedList;
  logit::LogIt* logCore;
  card::Binding_Card* selected;
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

  Menus Guard(MenuType& currentMenu);  //用于接收Exit指令和保护菜单程序
  
  //菜单，Info为打印菜单信息，对应Menus返回值函数为执行具体菜单任务
  void MainMenuInfo();  // MAIN_MENU
  Menus MainMenu(std::string message);
  void HolderMenuInfo();  // HOLDER_MENU
  Menus HolderMenu(std::string message);
  void AccountMainMenuInfo();
  Menus AccountMainMenu(std::string message);
  void CampusAccount();
  void DepositAccount();

  void StatusBar() const;//打印状态栏信息和当前选择账户信息

  void LookUp();  //搜索用户信息
  //增加操作
  void Add();                                            //添加用户记录
  void AddCampusCard(int identifier, std::string name);  //添加校园卡记录
  void AddDepositCard(int identifier, std::string name);  //添加储蓄卡记录

  bool ChooseAccount();  //选择账户以进行账户操作
  //修改操作
  void Modify();
  void ModifyBasic();
  void ModifyCampus();
  void ModifyDeposit();

  void Delete();
  void Print(std::vector<card::Binding_Card*> list);
};

//读入用户相关信息
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