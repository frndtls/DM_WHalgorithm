// @copyright<lhx>[2023.12.18]

#include "boilDownInference.h"

#include <vector>
std::string preAndCondToOne(const std::string& pre, const std::string& cond) {
  // A->B 变为 A&!B
  return "(" + pre + ")" + "&!(" + cond + ")";
}

void printClauseSet(const std::vector<std::vector<Propos>>& clauseSet) {
  int clauseNum = clauseSet.size();
  // 展示子句集状态
  std::cout << " cluseSet: {";
  for (int k = 0; k < clauseNum; ++k) {
    if (k != 0) std::cout << " , ";
    for (int j = 0; j < clauseSet[k].size(); ++j) {
      if (j != 0) std::cout << '|';
      if (clauseSet[k][j].value == 1) std::cout << '!';
      std::cout << clauseSet[k][j].name;
    }
  }
  std::cout << "}" << std::endl;
}

std::vector<std::vector<Propos>> getClauseSet(const std::string& preAndCond) {
  // mp以&为分隔符，每一个字句又以|为分隔符，P寸1，!P存0
  std::vector<std::vector<Propos>> clauseSet;

  std::string rpn = expToRPN(preAndCond);
  std::vector<Propos> propos;
  getInfoOfExp(preAndCond, propos);
  std::string mp;

  int width = propos.size();
  for (int count = 0; count < std::pow(2, width); ++count) {
    assignForPropos(count, propos);
    // 计算取值
    int res = rpnToValue(rpn);
    if (res == 0) {
      // 说明mp应该取这一项
      clauseSet.push_back(propos);
    }
  }
  return clauseSet;
}

int equalToCluse(const std::vector<Propos>& clause1,
                 const std::vector<Propos>& clause2) {
  int flag = -1;
  if (clause1.size() != clause2.size()) return -1;
  for (int i = 0; i < clause1.size(); ++i) {
    if (clause1[i].name != clause2[i].name) {
      return -1;
    } else {
      if (clause1[i].value != clause2[i].value) {
        if (flag == -1)
          flag = i;
        else
          return -1;
      } else {
        continue;
      }
    }
  }
  return flag;
}

bool boilDownInference(std::vector<std::vector<Propos>> clauseSet) {
  int clauseNum = clauseSet.size();
  // -归结的方法？遇见能归结的就归，归结完的结果替代原来的结果；归结出空字句就停止，推理成功；直到不能归结，还没归结出空子句，推理失败；

  for (int i = 0; i < clauseNum; ++i) {
    // 展示子句集状态
    printClauseSet(clauseSet);

    for (int j = 0; j < clauseNum; ++j) {
      int index = equalToCluse(clauseSet[i], clauseSet[j]);
      if (index != -1) {
        // 能进行归结
        clauseSet[i].erase(clauseSet[i].begin() + index);
        clauseSet[j].erase(clauseSet[j].begin() + index);
        printClauseSet(clauseSet);
        j = -1;
        if (clauseSet[i].size() == 0 || clauseSet[j].size() == 0) return true;
      }
    }
  }
  return false;
}
