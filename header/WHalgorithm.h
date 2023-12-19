// @copyright<lhx>[2023.12.18]

#include <queue>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

#include "expToTT.h"
#include "operators.h"

/*
  @Axiom：
  定义结构体公理 Axiom;
  包含precondition和conclusion两个vector;
  **注意precondition和conclusion的元素都需要是rpn**
  showAxiom()用于展示公理的内容
*/
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

/*
  @init():
  由两个合法的exp,经过转换为rpn,最后得到一个合法的Axiom
*/
Axiom init(std::string pre, std::string conclu);

/*
  @isMinimum():
  判断公理是否为最小公理;
  最小公理指的是公理中再没有可以使用前后件规则的公理;
  比如{P，Q} --> {P}，这个公理是最小公理;
  而{！P}-->{P}，这个公理不是最小公理;
  如果是最小公理，返回{-1,-1}；
  否则返回{i,k},i为0或1，0表示pre可使用前后件规则，1表示conclu可使用前后件规则;
                K为pre或conclu中的第k个元素可使用前后件规则；
*/
std::tuple<int, int> isMinimum(const Axiom &axiom);

/*
  @checkAxiom():
  检查最小公理是否是正确的；
  如果pre和condition都含有至少一个相同的propo,则为true,否则为false;
*/
bool checkAxiom(const Axiom &axiom);

/*
  @isRPN():
  判断一个字符串是否是rpn;
*/
bool isRPN(const std::string &exp);

/*
  @splitAxiom():
  将一个公理用前后件规则变换为一个或两个公理;
  算法的核心在于rpn的最后一个字符为运算优先级最高的运算符；
  对其用前后件规则，比如AB&,则可以分为A，B两个子公式；
  但是要通过遍历将rpn分为一个或两个合法的rpn,以便继续分离；

  同时展示出axioms出队和入队的过程
*/
void splitAxiom(const std::tuple<int, int> split, Axiom axiom,
                std::queue<Axiom> &axioms);

/*
  @WHalgorithm():
  思路：
      利用BFS，用queue这种数据结构，由一个公理入队开始；
      出队，如果是最小公理，那么检查是否成立；
        如果不成立，推理失败；
        如果成立，继续推理queue里后面的元素，
      如果不是最小公里，那么分离，将分离的子公理入队；
      重复这一过程，如果所有这个公理包含的的所有最小公理都成立，那么推理成功；
*/
void WHalgorithm(Axiom axiom);
