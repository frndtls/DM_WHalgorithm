// @copyright<lhx>[2023.12.15]
#pragma once
#include <memory.h>

#include <cmath>
#include <stack>
#include <string>
#include <vector>

#include "operators.h"

struct Propos {
  char name;
  bool value;
  explicit Propos(char name = ' ', bool value = false)
      : name(name), value(value) {}
};

bool hashPropos[26];
void initHashPropos();
void getInfoOfExp(const std::string& exp, std::vector<Propos>& propos);
void assignForPropos(int count, std::vector<Propos>& propos);
bool rpnToValue(const std::string& rpn);
bool isExp(const std::string& str);
std::string expToRPN(const std::string& str);
void expToTT(const std::string& rpn, const std::vector<Propos> propos);
