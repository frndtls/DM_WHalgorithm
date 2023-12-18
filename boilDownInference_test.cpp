// // @copyright<lhx>[2023.12.18]

// #include "boilDownInference.h"

// #include <iostream>
// #include <string>
// int main() {
//   std::string precond, conclu;
//   std::cout << "please input precondition: ";
//   std::cin >> precond;
//   std::cout << "please input conclusion: ";
//   std::cin >> conclu;
//   auto preAndCond = preAndCondToOne(precond, conclu);
//   auto clauseSet = getClauseSet(preAndCond);
//   boilDownInference(clauseSet) == 1
//       ? std::cout << "empty clause! inference is success!" << std::endl
//       : std::cout << "inference is fail!" << std::endl;
//   return 0;
// }
