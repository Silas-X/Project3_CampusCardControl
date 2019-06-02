#ifndef LOG_IT_H_
#define LOG_IT_H_
#include <fstream>
namespace logit {
class LogIt {
 private:
  std::string logFile;
  std::ofstream log;

 public:
  LogIt();
  ~LogIt();
  void LogingCenter();
  void LogingCard();
};
}  // namespace logit
#endif