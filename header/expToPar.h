// @copyright<lhx>[2023.12.16]
#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "expToTT.h"
#include "operators.h"

/*
    void expToPar(const std::string& rpn, std::vector<Propos> propos,
                  std::string& mp, std::string& dp):
    参数要求合法的rpn,propos也以及初始化，mp,dp可以非空
    mp,dp经过函数调用后变为主合取范式，主析取范式

    思路：还是根据命题公式的真值表判断，哪一项极大值（极小值）要取，哪一项不取
*/
void expToPar(const std::string& rpn, std::vector<Propos> propos,
              std::string& mp, std::string& dp);

/*
    std::string getMp(int count, std::vector<Propos> propos):
    得到 合取范式 中的 析取范式单元
*/
std::string getMp(int count, std::vector<Propos> propos);

/*
    std::string getDp(int count, std::vector<Propos> propos):
    得到 析取范式 中的 合取范式单元
*/
std::string getDp(int count, std::vector<Propos> propos);
