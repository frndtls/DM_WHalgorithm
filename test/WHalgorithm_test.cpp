// @copyright<lhx>[2023.12.18]

#include "../header/WHalgorithm.h"

#include <iostream>
#include <string>
int main() {
  std::string precond, conclu;
  std::cout << "please input precondition: ";
  std::cin >> precond;
  std::cout << "please input conclusion: ";
  std::cin >> conclu;
  if (isExp(precond) && isExp(conclu)) WHalgorithm(init(precond, conclu));
  return 0;
}
