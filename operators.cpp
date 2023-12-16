// @copyright<lhx>[2023.12.15]
#include "operators.h"

bool Myoperators::calcul(bool a, char op) {
  if (op != '!') {
    std::cout << "invalid operator" << std::endl;
    throw std::logic_error("invalid operator");
  }
  return !a;
}

bool Myoperators::calcul(bool a, char op, bool b) {
  switch (op) {
    case '&':
      return a && b;
      break;
    case '|':
      return a || b;
      break;
    case '^':
      return !(!a && b);
      break;
    case '~':
      return a == b;
      break;
    default: {
      throw std::logic_error("invalid operator");
      std::cout << "invalid operator" << std::endl;
    } break;
  }
}

bool Myoperators::isProposition(const char& c) { return c <= 'Z' && c >= 'A'; }

int Myoperators::operatorsIndex(const char& op) {
  switch (op) {
    {
      case '!':
        return 0;
        break;
      case '&':
        return 1;
        break;
      case '|':
        return 2;
        break;
      case '^':
        return 3;
        break;
      case '~':
        return 4;
        break;
      case '(':
        return 5;
        break;
      case ')':
        return 6;
        break;
      case '\0':
        return 7;
        break;
      default: {
        throw std::logic_error("invalid operator");
        std::cout << "invalid operator" << std::endl;
      } break;
    }
  }
}

bool Myoperators::isOperator(const char& c) {
  return c == '!' || c == '&' || c == '|' || c == '^' || c == '~' || c == '(' ||
         c == ')' || c == '\0';
}