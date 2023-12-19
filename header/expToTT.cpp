// @copyright<lhx>[2023.12.15]
#include "expToTT.h"

#include "operators.h"

bool hashPropos[26];

void initHashPropos() { memset(hashPropos, 0, sizeof(hashPropos)); }
bool isExp(const std::string& exp) {
  // 只检查操作符前后是否有操作数，操作数前后是否有操作符

  for (int i = 0; i < exp.length(); ++i) {
    if (Myoperators::isOperator(exp[i])) {
      // 如果是操作符
      if (exp[i] == '!') {
        if (i != 0 &&
            (Myoperators::isProposition(exp[i - 1]) || exp[i - 1] == ')'))
          return false;
      } else if (exp[i] == '(') {
        if (i == exp.length() - 1) return false;
        if (i != 0 && (Myoperators::isProposition(exp[i - 1]))) return false;
        if (exp[i + 1] != '(' && exp[i + 1] != '!' &&
            Myoperators::isOperator(exp[i + 1]))
          return false;
      } else if (exp[i] == ')') {
        if (i == 0) return false;
        if (exp[i - 1] != ')' && Myoperators::isOperator(exp[i - 1]))
          return false;
        if (i != exp.length() - 1 && exp[i + 1] != ')' &&
            Myoperators::isProposition(exp[i + 1]))
          return false;
      } else {
        if (i == 0 || i == exp.length() - 1) return false;
        if (Myoperators::isOperator(exp[i - 1]) && exp[i - 1] != ')')
          return false;
        if (Myoperators::isOperator(exp[i + 1]) && exp[i + 1] != '(' &&
            exp[i + 1] != '!')
          return false;
      }
    } else if (Myoperators::isProposition(exp[i])) {
      if (i != 0 && i != exp.length() - 1) {
        if (Myoperators::isProposition(exp[i - 1]) ||
            Myoperators::isProposition(exp[i + 1]))
          return false;
      }
    } else {
      return false;
    }
  }
  return true;
}

void getInfoOfExp(const std::string& exp, std::vector<Propos>& propos) {
  if (!isExp(exp)) return;
  for (auto c : exp) {
    if (Myoperators::isProposition(c)) {
      int i = 0;
      for (; i < propos.size(); ++i) {
        if (c == propos[i].name) break;
      }
      if (i == propos.size()) propos.push_back(Propos(c, false));
    }
  }
  // for (int i = 0; i < propos.size(); ++i) std::cout << propos[i].name << ' ';
}

std::string expToRPN(const std::string& exp) {
  std::string RPN;
  std::stack<char> s;
  int opndNum = 0;
  s.push('\0');
  int i = 0;
  int check = 0;  // 检查与！有关的情况
  while (i != -1) {
    // 检查与！有关的情况，也即！之后不能来普通运算符
    if (exp[i] == '!') check++;
    if (check) {
      if (check == -1) {
        if (Myoperators::isProposition(exp[i]) || exp[i] == '!' ||
            exp[i] == '(') {
          std::cout << "expression error 0" << std::endl;
          return "";
        } else {
          check = 0;
        }
      } else {
        if (Myoperators::isProposition(exp[i])) {
          check = -1;
        } else if (Myoperators::isOperator(exp[i]) && exp[i] != '!' &&
                   exp[i] != '(') {
          std::cout << "expression error 1" << std::endl;
          return "";
        }
      }
    }

    if (Myoperators::isProposition(exp[i])) {
      opndNum++;
      RPN += exp[i];
      i++;
      continue;
    } else if (Myoperators::isOperator(exp[i])) {
      char prior = Myoperators::pri[Myoperators::operatorsIndex(s.top())]
                                   [Myoperators::operatorsIndex(exp[i])];
      switch (prior) {
        case '<': {
          // 说明栈顶运算符优先级更小，当前运算符进栈
          s.push(exp[i]);
          i++;
          continue;
        } break;
        case '=': {
          // 说明\0遇到\0,运算理应结束
          i = -1;
          continue;
        } break;
        case '>': {
          opndNum -= s.top() == '!' ? 0 : 1;
          if (opndNum < 0) {
            std::cout << "expression error 4" << std::endl;
            return "";
          }
          RPN += s.top();
          s.pop();
          continue;
        } break;
        case 'x': {
          // (遇到），（直接出栈
          s.pop();
          i++;
          continue;
        } break;
        case ' ': {
          // 错误情况
          std::cout << "expression error 2" << std::endl;
          return "";
        } break;
        default:
          break;
      }
    } else {
      std::cout << "expression error 3" << std::endl;
      return "";
    }
  }

  if (opndNum != 1) {
    std::cout << "expression error 5" << std::endl;
    return "";
  }
  return RPN;
}

void assignForPropos(int count, std::vector<Propos>& propos) {
  initHashPropos();
  int width = propos.size();
  for (int j = 0; j < width; j++) {
    int res = count & 1;
    // 说明末尾位为1
    propos[width - 1 - j].value = static_cast<bool>(res);
    hashPropos[propos[width - 1 - j].name - 'A'] = static_cast<bool>(res);
    count >>= 1;
  }
}

bool rpnToValue(const std::string& rpn) {
  std::stack<char> s;
  std::stack<bool> propos;
  for (auto c : rpn) {
    if (Myoperators::isProposition(c)) {
      propos.push(hashPropos[c - 'A']);
      // std::cout << hashPropos[c - 'A'] << std::endl;
      continue;
    } else if (Myoperators::isOperator(c)) {
      if (c == '!') {
        // 一目
        bool opnd1 = propos.top();
        propos.pop();
        bool res = Myoperators::calcul(opnd1, c);
        propos.push(res);
      } else {
        // 二目
        bool opnd2 = propos.top();
        propos.pop();
        bool opnd1 = propos.top();
        propos.pop();
        bool res = Myoperators::calcul(opnd1, c, opnd2);
        propos.push(res);
      }
    }
  }
  return propos.top();
}

void expToTT(const std::string& rpn, std::vector<Propos> propos) {
  // rpn propos都已经初始化
  int width = propos.size();

  // 输出表头
  for (int i = 0; i < width + 1; ++i) {
    if (i == width) {
      std::cout << 'V' << std::endl;
      continue;
    }
    std::cout << propos[i].name << ' ';
  }

  for (int count = 0; count < std::pow(2, width); ++count) {
    assignForPropos(count, propos);
    // 输出取值
    for (int i = 0; i < width; ++i) {
      std::cout << propos[i].value << ' ';
    }
    std::cout << rpnToValue(rpn) << std::endl;
  }
}
