// @copyright<lhx>[2023.12.15]
#pragma once
#include <memory.h>

#include <cmath>
#include <stack>
#include <string>
#include <vector>

#include "operators.h"

/*
  Propos:
  name:表示命题名称，如P、Q等
  value:表示命题的值，如P=true、Q=false等
*/
struct Propos {
  char name;
  bool value;
  explicit Propos(char name = ' ', bool value = false)
      : name(name), value(value) {}
};

/*
  hashPropos:
  用hash的方法存每个命题的value,便于快速访问
*/
extern bool hashPropos[26];

/*
  void initHashPropos():
  将hashPropos全部初始化为0
*/
void initHashPropos();

/*
  void getInfoOfExp(const std::string& exp, std::vector<Propos>& propos):
  先调用isExp判断输入的字符串是否为表达式;
  再初始化propos;比如P&S&R&P,那么propos就是{P,S,R},暂不赋值
*/
void getInfoOfExp(const std::string& exp, std::vector<Propos>& propos);

/*
  void assignForPropos(int count, std::vector<Propos>& propos):
  先初始化hashPropos;
  再为propos赋值,比如count=3,(011)那么{P,S,R}就是{false,true,true}
*/
void assignForPropos(int count, std::vector<Propos>& propos);

/*
  bool rpnToValue(const std::string& rpn):
  数据结构：栈
  由rpn计算命题公式的值，在这之前要求已经调用assignForPropos
*/
bool rpnToValue(const std::string& rpn);

/*
  bool isExp(const std::string& str):
  判断输入的字符串是否为表达式:
  但是check功能有限，一部分check功能在expToRPN中实现
*/
bool isExp(const std::string& str);

/*
  std::string expToRPN(const std::string& str):
  数据结构：栈
  在isExp检查之后，将通过检查的exp转换为rpn表达式
*/
std::string expToRPN(const std::string& str);

/*
  void expToTT(const std::string& rpn, const std::vector<Propos> propos):
  参数要求合法的rpn,以及已经初始化好的propos;
  输出整个真值表
*/
void expToTT(const std::string& rpn, const std::vector<Propos> propos);
