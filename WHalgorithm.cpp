// @copyright<lhx>[2023.12.18]
#include "WHalgorithm.h"

Axiom init(std::string pre, std::string conclu) {
  auto precondition = expToRPN(pre);
  auto conclusion = expToRPN(conclu);
  Axiom axiom;
  axiom.precondition.clear();
  axiom.conclusion.clear();
  axiom.precondition.push_back(precondition);
  axiom.conclusion.push_back(conclusion);
  return axiom;
}

std::tuple<int, int> isMinimum(const Axiom &axiom) {
  for (int i = 0; i < axiom.precondition.size(); ++i) {
    if (axiom.precondition[i].length() == 1 &&
        Myoperators::isProposition(axiom.precondition[i][0]))
      continue;
    else
      return {0, i};
  }

  for (int i = 0; i < axiom.conclusion.size(); ++i) {
    if (axiom.conclusion[i].length() == 1 &&
        Myoperators::isProposition(axiom.conclusion[i][0]))
      continue;
    else
      return {1, i};
  }
  return {-1, -1};
}

bool checkAxiom(const Axiom &axiom) {
  if (axiom.precondition.empty() || axiom.conclusion.empty()) return false;
  for (int i = 0; i < axiom.precondition.size(); ++i) {
    auto c = axiom.precondition[i][0];
    for (int j = 0; j < axiom.conclusion.size(); ++j) {
      auto d = axiom.conclusion[j][0];
      if (c == d) return true;
    }
  }
  return false;
}

bool isRPN(const std::string &exp) {
  if (exp.empty()) return false;
  if (Myoperators::isOperator(exp[0])) return false;
  if (exp.length() > 1 && Myoperators::isProposition(exp[exp.length() - 1]))
    return false;

  std::stack<char> s;
  int opndNum = 0;
  for (auto c : exp) {
    if (Myoperators::isProposition(c)) {
      opndNum++;
      continue;
    } else if (Myoperators::isOperator(c)) {
      if (c == '!') {
        // 一目
        if (opndNum < 1) return false;
      } else {
        // 二目
        if (opndNum < 2) return false;
        opndNum--;
      }
    }
  }

  return opndNum == 1 ? true : false;
}

void splitAxiom(const std::tuple<int, int> split, Axiom axiom,
                std::queue<Axiom> &axioms) {
  // 对每一个公理进行分化,并入队
  int preOrcon = std::get<0>(split);
  int splitIndex = std::get<1>(split);
  if (preOrcon == 0) {
    // 需要split前提
    std::string str = axiom.precondition[splitIndex];

    if (str[str.length() - 1] == '!') {
      str.pop_back();
      axiom.precondition.erase(axiom.precondition.begin() + splitIndex);
      axiom.conclusion.push_back(str);
      axioms.push(axiom);
      std::cout << "enqueue: ";
      axiom.showAxiom();
    } else {
      char op = str[str.length() - 1];
      str.pop_back();
      std::string str1, str2;
      for (int i = 0; i < str.length(); ++i) {
        str1 = str.substr(0, i);
        str2 = str.substr(i, str.length() - i);
        if (isRPN(str1) && isRPN(str2)) break;
      }
      axiom.precondition.erase(axiom.precondition.begin() + splitIndex);
      switch (op) {
        {
          case '&': {
            Axiom ax1 = axiom;
            ax1.precondition.push_back(str1);
            ax1.precondition.push_back(str2);
            axioms.push(ax1);
            std::cout << "enqueue: ";
            ax1.showAxiom();
          } break;
          case '|': {
            Axiom ax1 = axiom;
            ax1.precondition.push_back(str1);
            Axiom ax2 = axiom;
            ax2.precondition.push_back(str2);
            axioms.push(ax1);
            std::cout << "enqueue: ";
            ax1.showAxiom();
            axioms.push(ax2);
            std::cout << "enqueue: ";
            ax2.showAxiom();
          } break;
          case '^': {
            Axiom ax1 = axiom;
            ax1.conclusion.push_back(str1);
            Axiom ax2 = axiom;
            ax2.precondition.push_back(str2);
            axioms.push(ax1);
            std::cout << "enqueue: ";
            ax1.showAxiom();
            axioms.push(ax2);
            std::cout << "enqueue: ";
            ax2.showAxiom();
          } break;
          case '~': {
            Axiom ax1 = axiom;
            ax1.conclusion.push_back(str1);
            ax1.conclusion.push_back(str2);
            Axiom ax2 = axiom;
            ax2.precondition.push_back(str2);
            ax2.precondition.push_back(str1);
            axioms.push(ax1);
            std::cout << "enqueue: ";
            ax1.showAxiom();
            axioms.push(ax2);
            std::cout << "enqueue: ";
            ax2.showAxiom();
          }
          default:
            break;
        }
      }
    }
  } else if (preOrcon == 1) {
    // 需要split结论
    std::string str = axiom.conclusion[splitIndex];

    if (str[str.length() - 1] == '!') {
      str.pop_back();
      axiom.conclusion.erase(axiom.conclusion.begin() + splitIndex);
      axiom.precondition.push_back(str);
      axioms.push(axiom);
      std::cout << "enqueue: ";
      axiom.showAxiom();
    } else {
      char op = str[str.length() - 1];
      str.pop_back();
      std::string str1, str2;
      for (int i = 0; i < str.length(); ++i) {
        str1 = str.substr(0, i);
        str2 = str.substr(i, str.length() - i);
        if (isRPN(str1) && isRPN(str2)) break;
      }
      axiom.conclusion.erase(axiom.conclusion.begin() + splitIndex);
      switch (op) {
        {
          case '&': {
            Axiom ax1 = axiom;
            ax1.conclusion.push_back(str1);
            axioms.push(ax1);
            std::cout << "enqueue: ";
            ax1.showAxiom();
            Axiom ax2;
            ax2.conclusion.push_back(str2);
            axioms.push(ax2);
            std::cout << "enqueue: ";
            ax2.showAxiom();
          } break;
          case '|': {
            Axiom ax1 = axiom;
            ax1.conclusion.push_back(str1);
            ax1.conclusion.push_back(str2);
            axioms.push(ax1);
            std::cout << "enqueue: ";
            ax1.showAxiom();
          } break;
          case '^': {
            Axiom ax1 = axiom;
            ax1.precondition.push_back(str1);
            ax1.conclusion.push_back(str2);
            axioms.push(ax1);
            std::cout << "enqueue: ";
            ax1.showAxiom();
          } break;
          case '~': {
            Axiom ax1 = axiom;
            ax1.precondition.push_back(str1);
            ax1.conclusion.push_back(str2);
            Axiom ax2 = axiom;
            ax2.precondition.push_back(str2);
            ax2.conclusion.push_back(str1);
            axioms.push(ax1);
            std::cout << "enqueue: ";
            ax1.showAxiom();
            axioms.push(ax2);
            std::cout << "enqueue: ";
            ax2.showAxiom();
          }
          default:
            break;
        }
      }
    }
  }
}

void WHalgorithm(Axiom axiom) {
  // 根据优先级最高的运算符进行分化

  // 初始化这个公理集
  std::queue<Axiom> axioms;
  axioms.push(axiom);
  std::cout << "enqueue: ";
  axiom.showAxiom();
  bool flag = false;
  while (!axioms.empty()) {
    // 对每一个公理进行分化,类似进行BFS
    Axiom ax = axioms.front();
    axioms.pop();
    std::cout << "dequeue: ";
    ax.showAxiom();
    std::tuple<int, int> split = isMinimum(ax);
    if (split == std::make_tuple<int, int>(-1, -1)) {
      // 如果是最小公理,则检查是否成立
      if (checkAxiom(ax)) {
        std::cout << "check successfully!" << std::endl;
        continue;
      } else {
        std::cout << "check failed!" << std::endl;
        std::cout << "infer failed!" << std::endl;
        return;
      }
    } else {
      // 需要分化公理
      splitAxiom(split, ax, axioms);
    }
  }
  std::cout << "infer successfully!" << std::endl;
}
