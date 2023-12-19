// @copyright<lhx>[2023.12.16]

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "../header/expToPar.h"
#include "../header/expToTT.h"

int main() {
  int n; /*命题个数*/
  std::cin >> n;

  std::vector<Propos> propos;
  for (int i = 0; i < n; ++i) {
    char name;
    std::cin >> name;
    propos.push_back(Propos(name));
  }
  int width = propos.size();
  std::string dp;
  for (int j = 0; j < std::pow(2, width); ++j) {
    int value = 0;
    int count = 0;
    for (int i = 0; i < width + 1; ++i) {
      if (i == width) {
        std::cin >> value;
        break;
      }
      int x;
      std::cin >> x;
      if (x == 1) count += std::pow(2, width - 1 - i);
    }
    if (value == 1) {
      if (!dp.empty()) dp += " | ";
      assignForPropos(count, propos);
      dp += getDp(count, propos);
    }
  }
  std::cout << "expression: " << dp << std::endl;
  return 0;
}
