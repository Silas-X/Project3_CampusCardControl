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
T str2num(std::string str) {
  T num;
  std::stringstream ss;
  ss.clear();
  ss.str = "";
  ss << str;
  ss >> num;
  return num;
}

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
};  // namespace general

#endif