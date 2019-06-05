#define DEBUG_
#include "controller.h"
#include <iostream>
#include <map>

namespace cardSystem {
// init Singleton
using std::map;
card_storage* card_storage::butler = NULL;
card_storage::card_storage() { storage.clear(); }
card_storage* card_storage::init() {
  if (butler == NULL) butler = new card_storage;
  return butler;
}
card_storage::~card_storage() {
  std::map<int, card::Binding_Card*>::iterator it = storage.begin();
  while (it != storage.end()) {
    card::Binding_Card* temp = it->second;
    it->second = NULL;
    delete temp;
    it++;
  }
  storage.clear();
}
// accessor
#ifdef DEBUG_
void card_storage::print() {
  if (storage.empty()) {
    std::cout << "无记录" << std::endl;
  }
  map<int, card::Binding_Card*>::iterator it = storage.begin();
  while (it != storage.end()) {
    std::cout << it->second->GetInfo() << std::endl;
    it++;
  }
  return;
}
#endif
void card_storage::PrintAll(std::string ctrl) {
  if (storage.empty()) {
    std::cout << "无记录" << std::endl;
    return;
  }

  std::map<int, card::Binding_Card*>::iterator it = storage.begin();
  std::cout << "Identifier\t"
            << "\tName" << std::endl;
  while (it != storage.end()) {
    if (ctrl == "OneLine") {
      std::cout << it->second->GetIdentifier() << "\t\t\t"
                << it->second->GetName() << std::endl;
    }
    it++;
  }
}
// void card_storage::GetInfo(int _identifer) const {}
std::vector<std::string> card_storage::GetAllIdentifier() {
  std::vector<std::string> identifierList;
  std::map<int, card::Binding_Card*>::iterator it = storage.begin();
  while (it != storage.end()) {
    identifierList.push_back(general::num2str(it->second->GetIdentifier()));
    it++;
  }
  return identifierList;
}
// mutator

bool card_storage::AddCampusCard(card::Campus_Card& campusCard) {
  // TODO::为binding card提供三种模式的构造器
  // TODO::为binding card 提供添加其内部两种卡片的函数
  map<int, card::Binding_Card*>::iterator it =
      storage.find(campusCard.GetIdentifier());
  if (it != storage.end()) {
    return it->second->AddNewCard(card::CAMPUS_CARD, &campusCard);
  }
  card::Binding_Card* temp = new card::Binding_Card(campusCard);
  storage.insert(
      std::pair<int, card::Binding_Card*>(campusCard.GetIdentifier(), temp));
  return true;
}

bool card_storage::AddDepositCard(card::Deposit_Card& depositCard) {
  // TODO::为binding card提供三种模式的构造器
  // TODO::为binding card 提供添加其内部两种卡片的函数
  map<int, card::Binding_Card*>::iterator it =
      storage.find(depositCard.GetIdentifier());
  if (it != storage.end()) {
    return it->second->AddNewCard(card::DEPOSIT_CARD, &depositCard);
  }
  card::Binding_Card* temp = new card::Binding_Card(depositCard);
  storage.insert(
      std::pair<int, card::Binding_Card*>(depositCard.GetIdentifier(), temp));
  return true;
}

bool card_storage::BindingCard(int _identifier) {
  card::Binding_Card* bindingCard = FindCard(_identifier);
  return bindingCard->SetBindingCards();
}

/* bool card_storage::BindingCard(card::Campus_Card& card1,
                               card::Deposit_Card& card2) {
  if (card1.GetIdentifier() != card2.GetIdentifier()) return false;
  AddCampusCard(card1);
  AddDepositCard(card2);
  return FindCard(card1.GetIdentifier())->SetBindingCards();
}
*/
card::Binding_Card* card_storage::FindCard(int _identifier) {
  std::map<int, card::Binding_Card*>::iterator it = storage.find(_identifier);
  if (it == storage.end()) return NULL;
  return storage.find(_identifier)->second;
}
std::vector<card::Binding_Card*> card_storage::FindCard(std::string _name) {
  std::vector<card::Binding_Card*> list;
  std::map<int, card::Binding_Card*>::iterator it = storage.begin();
  while (it != storage.end()) {
    if (it->second->Campus_Card::GetName() == _name) list.push_back(it->second);
    it++;
  }
  return list;
}
// Account operations
bool card_storage::Deposit(card::MoneyType amount, card::Binding_Card& current,
                           card::CardType cardType) {
  if (amount < 0) return false;
  return current.Deposit(amount, cardType);
}
bool card_storage::Withdraw(card::MoneyType amount, card::Binding_Card& current,
                            card::CardType cardType) {
  if (amount < 0) return false;
  return current.Withdraw(amount, cardType);
}
bool card_storage::Pay(card::MoneyType amount, card::Binding_Card& current,
                       card::CardType cardType) {
  if (amount < 0) return false;
  return current.Pay(amount, cardType);
}

bool card_storage::ExternalTransfer(card::MoneyType amount,
                                    card::Binding_Card* src,
                                    card::Binding_Card* dest,
                                    card::CardType srcType,
                                    card::CardType destType) {
  if (amount < 0) return false;
  if (src == dest) return false;
  if (src == NULL || dest == NULL) return false;
  if (!src->Withdraw(amount, srcType)) return false;
  if (!dest->Deposit(amount, destType)) {
    src->Deposit(amount, srcType);
    return false;
  }
  return true;
}

bool card_storage::InternalTransfer(card::MoneyType amount,
                                    card::Binding_Card* holder,
                                    card::CardType src, card::CardType dest) {
  if (amount < 0) return false;
  return (holder->Transfer(amount, src, dest));
}

}  // namespace cardSystem