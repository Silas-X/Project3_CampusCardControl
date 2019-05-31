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
#define CONTROLLER_H_
#include <map>
#include "../card/campus_card.h"
#include "../card/card.h"
#include "../card/deposit_card.h"
namespace cardSystem {

using std::map;
class card_storage {
 private:
  map<int, card::Card*> cardsStorages;

 public:
 
};

}  // namespace cardSystem

#endif