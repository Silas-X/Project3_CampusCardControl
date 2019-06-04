/*@description
 *This header file provide general functions that are needed in this project.
 *@namespace general
 *@function list
 *
 *
 *
 */

#ifndef GENERAL_FUN_H_
#define GENERAL_FUN_H_

#include <ctime>
#include <sstream>
#include <string>
namespace general {
template <class T>
bool str2num(std::string str, T &num) {
  std::stringstream ss;
  ss.clear();
  ss << str;
  ss >> num;
  return !ss.fail();
}

template <class T>
bool num2str(T num, std::string &str) {
  // TODO:exceptions num is not a nums;
  std::stringstream ss;
  ss.clear();
  ss << num;
  ss >> str;
  return !ss.fail();
}

template <class T>
T str2num(const std::string &str) {
  T num;
  std::stringstream ss;
  ss.clear();
  ss << str;
  ss >> num;
  return num;
}

int str2num(std::string str);
template <class T>
std::string num2str(T num) {
  // TODO:exceptions num is not a nums;
  std::string str;
  std::stringstream ss;
  ss.clear();
  ss << num;
  ss >> str;
  return str;
}

char *GetCurrentTime();
void Pause();
void mkdir(std::string addr,std::string rootAddr="");
std::string FormAddr(std::string rootAddr,std::string dir="",std::string fileName="");
};  // namespace general

#endif