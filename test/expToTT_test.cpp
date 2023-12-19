// @copyright<lhx>[2023.12.15]
#include "../header/expToTT.h"

#include <iostream>
#include <string>

#include "../header/operators.h"
int main() {
  std::string str;
  std::cin >> str;
  std::vector<Propos> propos;
  getInfoOfExp(str, propos);
  str += '\0';
  expToTT(expToRPN(str), propos);

  return 0;
}
