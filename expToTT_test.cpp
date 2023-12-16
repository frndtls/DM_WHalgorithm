// @copyright<lhx>[2023.12.15]
#include "expToTT.h"

#include <iostream>
#include <string>

#include "operators.h"
int main() {
  std::string str;
  std::cin >> str;
  str += '\0';
  std::vector<Propos> propos;
  getInfoOfExp(str, propos);
  // std::string RPN = expToRPN(str);
  // std::cout << RPN << std::endl;
  return 0;
}
