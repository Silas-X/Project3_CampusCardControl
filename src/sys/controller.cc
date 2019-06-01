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
    std::cout << it->second->GetIdentifier();
    it++;
  }
  return;
}
#endif
// void card_storage::GetInfo(int _identifer) const {}

// mutator

bool card_storage::AddCampusCard(const card::Campus_Card& campusCard) {
  // TODO::为binding card提供三种模式的构造器
  // TODO::为binding card 提供添加其内部两种卡片的函数
  map<int, card::Binding_Card*>::iterator it =
      storage.find(campusCard.GetIdentifier());
  if (it != storage.end()) {
    return it->second->AddNewCard(card::CAMPUS_CARD, campusCard);
  }
  card::Binding_Card* temp = new card::Binding_Card(campusCard);
  storage.insert(
      std::pair<int, card::Binding_Card*>(campusCard.GetIdentifier(), temp));
  return true;
}

// bool card_storage::AddDepositCard(int _identifier);
// bool card_storage::BindingCard(card::Card& card1, card::Card* card2);
// bool card_storage::FindCard(int _identifier) const;
}  // namespace cardSystem