#include "cardSystem.h"

namespace cardSystem {
CardSystem::CardSystem() {
  storageCore = cardSystem::card_storage::init();
  logCore = logit::LogIt::Init();
  fileCore = fileSystem::Data_Base::Init(storageCore, logCore);
  interfaceCore = ui::Interface::InitInterface(storageCore, logCore);
}
CardSystem::~CardSystem() {
  delete storageCore;
  storageCore = NULL;
  delete interfaceCore;
  interfaceCore = NULL;
  delete logCore;
  logCore = NULL;
  delete fileCore;
  fileCore = NULL;
}
bool CardSystem::Launcher() {
  fileCore->ReadInAllData();
  if (!interfaceCore->SetOpt(ui::Interface::MAIN_MENU)) return false;
  if (!interfaceCore->Dispatch()) return false;
  if (!fileCore->WriteOutData()) return false;
  return true;
}
}  // namespace cardSystem