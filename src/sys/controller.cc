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

// accessor
#ifdef DEBUG_
void card_storage::print() {
  map<int, card::Binding_Card*>::iterator it = storage.begin();
  while (it != storage.end()) {
    std::cout << it->second->GetInfo() << std::endl;
    it++;
  }
  return;
}
#endif
// void card_storage::GetInfo(int _identifer) const {}

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
bool card_storage::BindingCard(card::Campus_Card& card1,
                               card::Deposit_Card& card2) {
  if (card1.GetIdentifier() != card2.GetIdentifier()) return false;
  AddCampusCard(card1);
  AddDepositCard(card2);
  return FindCard(card1.GetIdentifier())->SetBindingCards();
}

card::Binding_Card* card_storage::FindCard(int _identifier) const {
  return storage.find(_identifier)->second;
}

}  // namespace cardSystem