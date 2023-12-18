// @copyright<lhx>[2023.12.16]
#include "expToPar.h"

void expToPar(const std::string& rpn, std::vector<Propos> propos,
              std::string& mp, std::string& dp) {
  // rpn propos都已经初始化
  int width = propos.size();
  mp.clear();
  dp.clear();
  for (int count = 0; count < std::pow(2, width); ++count) {
    assignForPropos(count, propos);
    // 计算取值
    int res = rpnToValue(rpn);
    if (res == 0) {
      // 说明mp应该取这一项
      if (!mp.empty()) mp += " & ";
      mp += getMp(count, propos);
    } else {
      // 说明dp应该取这一项
      if (!dp.empty()) dp += " | ";
      dp += getDp(count, propos);
    }
  }
}

std::string getMp(int count, std::vector<Propos> propos) {
  std::string mp;
  // 合取范式，这里的mp应该是析取
  for (auto p : propos) {
    if (!mp.empty()) mp += '|';
    if (p.value == 1) mp += "!";
    mp += p.name;
  }
  return mp;
}

std::string getDp(int count, std::vector<Propos> propos) {
  std::string dp;
  // 析取范式，这里的dp是合取范式
  for (auto p : propos) {
    if (!dp.empty()) dp += '&';
    if (p.value == 0) dp += "!";
    dp += p.name;
  }
  return dp;
}
