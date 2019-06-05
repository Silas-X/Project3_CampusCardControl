#ifndef CARDSYSTEM_H_
#define CARDSYSTEM_H_
#define DEBUG_
#include "../card/binding_card.h"
#include "../card/campus_card.h"
#include "../card/card.h"
#include "../card/deposit_card.h"

#include "../interface/data_base.h"
#include "../interface/interface.h"
#include "../interface/log_it.h"

#include "controller.h"

#ifdef DEBUG_
#include "../../src/card/binding_card.cc"
#include "../../src/card/campus_card.cc"
#include "../../src/card/card.cc"
#include "../../src/card/deposit_card.cc"
#include "../../src/general/generalFun.cc"
#include "../../src/interface/data_base.cc"
#include "../../src/interface/interface.cc"
#include "../../src/interface/log_it.cc"
#include "../../src/sys/controller.cc"
#endif
namespace cardSystem {
class CardSystem {
 private:
  card_storage *storageCore;
  ui::Interface *interfaceCore;
  logit::LogIt *logCore;
  fileSystem::Data_Base *fileCore;

 public:
  CardSystem();
  ~CardSystem();
  bool Launcher();
};
}  // namespace cardSystem

#endif