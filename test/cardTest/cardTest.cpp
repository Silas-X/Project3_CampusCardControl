//#define DEBUG_
//#define TEST_CAMPUS_CARD
//#define TEST_DEPOSIT_CARD
//#define TEST_BINDING_CARD
#define TEST_MENU

#ifdef DEBUG_
#include "../../src/card/binding_card.cc"
#include "../../src/card/campus_card.cc"
#include "../../src/card/card.cc"
#include "../../src/card/deposit_card.cc"
#include "../../src/interface/interface.cc"
#include "../../src/sys/controller.cc"
#endif

#include <iostream>
#include "../../src/card/binding_card.h"
#include "../../src/card/campus_card.h"
#include "../../src/card/card.h"
#include "../../src/card/deposit_card.h"
#include "../../src/interface/interface.h"
#include "../../src/sys/controller.h"

int main() {
  std::string name;
  std::string password;
  std::string stuId;
  std::string department;
  std::string cardCode;
  int num;

  card::MoneyType amount;
  cardSystem::card_storage *system = cardSystem::card_storage::init();
#ifdef TEST_CAMPUS_CARD
  std::cin >> name;
  std::cin >> password;
  std::cin >> stuId;
  std::cin >> department;
  std::cin >> amount;
  card::Campus_Card STU1(1, name, password, stuId, department, amount);
  std::cout << STU1.GetInfo() << std::endl;
  std::cout << STU1.GetBalance() << std::endl;
  std::cin >> num;
  STU1.Deposit(num);
  std::cout << STU1.GetBalance() << std::endl;
  std::cin >> num;
  STU1.Withdraw(num);
  std::cout << STU1.GetBalance() << std::endl;
  std::cin >> num;
  STU1.Pay(num);
  std::cout << STU1.GetBalance() << std::endl;

  std::cin >> name;
  std::cin >> password;
  std::cin >> stuId;
  std::cin >> department;

  STU1.SetName(name);
  STU1.SetPasswd(password);
  STU1.SetStudentId(stuId);
  STU1.SetDepartment(department);
  std::cout << STU1.GetInfo() << std::endl;
#endif
#ifdef TEST_DEPOSIT_CARD
  std::cin >> name;
  std::cin >> password;
  std::cin >> cardCode;
  std::cin >> amount;
  card::Deposit_Card dep1(2, name, password, cardCode, amount);
  std::cout << dep1.GetInfo() << std::endl;
  std::cout << dep1.GetBalance() << std::endl;
  std::cin >> num;
  if (!dep1.Deposit(num)) std::cout << "FAILUSE\n";
  std::cout << dep1.GetBalance() << std::endl;
  std::cin >> num;
  if (!dep1.Withdraw(num)) std::cout << "FAILURE\n";
  std::cout << dep1.GetBalance() << std::endl;
  std::cin >> num;
  if (!dep1.Pay(num)) std::cout << "FAILURE\n";
  std::cout << dep1.GetBalance() << std::endl;

  std::cin >> name;
  std::cin >> password;
  std::cin >> cardCode;
  std::cin >> num;
  dep1.SetName(name);
  dep1.SetPasswd(password);
  dep1.SetCardCode(cardCode);
  dep1.SetOverdraft(num);
  std::cout << dep1.GetInfo() << std::endl;
#endif

#ifdef TEST_BINDING_CARD
#define BINDING_TEST
#define ACCOUNT_TEST
  card::Campus_Card STU1(1, "TESTNAME1", "password", "stuId", "department",
                         2333);
  // system->AddCampusCard(STU1);
  card::Campus_Card STU2(2, "TESTNAME2", "password", "stuId", "department",
                         2333);
  system->AddCampusCard(STU2);
  card::Deposit_Card dep1(1, "TESTNAME1", "PASSWORD", "1234324", 213, 123);
  system->AddDepositCard(dep1);
  card::Deposit_Card dep2(2, "TESTNAME2", "PASSWORD", "1234324", 213, 500);
  system->AddDepositCard(dep2);
  system->BindingCard(STU1, dep1);
  //  system->print();

#ifdef BINDING_TEST
#endif

#ifdef ACCOUNT_TEST
  card::Binding_Card *ptr = system->FindCard(1);
  ptr->Deposit(100, card::CAMPUS_CARD);
  ptr->Deposit(100);
  std::cout << ptr->GetInfo() << std::endl;
  ptr->Withdraw(300);
  std::cout << ptr->GetInfo() << std::endl;
  ptr->Pay(300);
  std::cout << ptr->GetInfo() << std::endl;
  ptr->Deposit(200);
  std::cout << ptr->GetInfo() << std::endl;
  ptr->Transfer(100);
  std::cout << ptr->GetInfo() << std::endl;
  ptr->Transfer(100000, card::CAMPUS_CARD, card::DEPOSIT_CARD);
  std::cout << ptr->GetInfo() << std::endl;
#endif
#endif

#ifdef TEST_MENU
  ui::Interface *userWindow = ui::Interface::InitInterface(system);
  userWindow->SetOpt(ui::Interface::MAIN_MENU);
  userWindow->Dispatch();
#endif
  return 0;
}