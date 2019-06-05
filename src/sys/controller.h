/*本头文件提供了管理card的管理类，其包含以map存储Card*的地址，<identifier,Card*>为键值对
 *Card可以存储三种类型的卡片，通过父类指针指向子类的办法
 *提供查找，删除，增加，修改的方法
 *@初始化
 *@增加:增加校园卡，增加储蓄卡，绑定卡,分别对应绑定卡类实例化校园卡，储蓄卡，和设置绑定位
 *@修改：修改指定卡指定类型卡相关信息
 *
 *
 *
 *
 */

#ifndef CONTROLLER_H_
#define DEBUG_

#define CONTROLLER_H_
#include <iomanip>
#include <map>
#include <vector>
#include "../card/binding_card.h"
#include "../card/campus_card.h"
#include "../card/card.h"
#include "../card/deposit_card.h"
namespace cardSystem {

using std::map;
class card_storage {
 private:
  map<int, card::Binding_Card*> storage;
  card_storage();
  static card_storage* butler;

 public:
  static card_storage* init();  // singletons
  ~card_storage();
// accesor
#ifdef DEBUG_
  void print();
#endif
  void PrintAll(std::string ctrl = "OneLine");
  std::vector<std::string> GetAllIdentifier();
  // mutator
  bool DeleteCard(int _identifier);
  bool DeleteCampusCard(int _identifier);
  bool DeleteDepositCard(int _identifier);
  bool AddCampusCard(card::Campus_Card& compusCard);
  bool AddDepositCard(card::Deposit_Card& compusCard);

  bool BindingCard(int identifier);

  // bool BindingCard(card::Campus_Card& card1, card::Deposit_Card& card2);

  card::Binding_Card* FindCard(int _identifier);
  std::vector<card::Binding_Card*> FindCard(std::string _name);
  // Account operations 内部调用对应卡片接口进行操作
  bool Deposit(card::MoneyType amount, card::Binding_Card& current,
               card::CardType cardType = card::DEPOSIT_CARD);
  bool Withdraw(card::MoneyType amount, card::Binding_Card& current,
                card::CardType cardType = card::DEPOSIT_CARD);
  bool Pay(card::MoneyType amount, card::Binding_Card& current,
           card::CardType cardType = card::DEPOSIT_CARD);
  bool ExternalTransfer(card::MoneyType amount, card::Binding_Card* src,
                        card::Binding_Card* dest,
                        card::CardType srcType1 = card::DEPOSIT_CARD,
                        card::CardType destType2 = card::DEPOSIT_CARD);
  bool InternalTransfer(card::MoneyType amount, card::Binding_Card* holder,
                        card::CardType src = card::DEPOSIT_CARD,
                        card::CardType dest = card::CAMPUS_CARD);
};
}  // namespace cardSystem

#endif