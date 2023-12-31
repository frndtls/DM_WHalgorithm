// @copyright<lhx>[2023.12.16]
#include "../header/expToPar.h"

#include <iostream>

#include "../header/expToTT.h"
#include "../header/operators.h"

int main() {
  std::string str;
  std::cin >> str;

  std::vector<Propos> propos;
  getInfoOfExp(str, propos);
  str += '\0';
  std::string mp, dp;
  expToPar(expToRPN(str), propos, mp, dp);

  std::cout << "mp: " << mp << std::endl;
  std::cout << "dp: " << dp << std::endl;
  return 0;
}
