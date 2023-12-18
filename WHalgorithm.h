// @copyright<lhx>[2023.12.18]

#include <queue>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

#include "expToTT.h"
#include "operators.h"
struct Axiom {
  /*每一个string都是一个rpn*/
  std::vector<std::string> precondition;
  std::vector<std::string> conclusion;
  void showAxiom() const {
    std::cout << "{";
    for (int k = 0; k < this->precondition.size(); ++k) {
      if (k != 0) std::cout << " , ";
      std::cout << this->precondition[k];
    }
    std::cout << "} -->s ";

    std::cout << "{";
    for (int k = 0; k < this->conclusion.size(); ++k) {
      if (k != 0) std::cout << " , ";
      std::cout << this->conclusion[k];
    }
    std::cout << "} " << std::endl;
  }
  Axiom(const std::string &pre = "", const std::string &conclu = "")
      : precondition{pre}, conclusion{conclu} {}
};

Axiom init(std::string pre, std::string conclu);

std::tuple<int, int> isMinimum(const Axiom &axiom);

bool checkAxiom(const Axiom &axiom);

bool isRPN(const std::string &exp);

void splitAxiom(const std::tuple<int, int> split, Axiom axiom,
                std::queue<Axiom> &axioms);

void WHalgorithm(Axiom axiom);
