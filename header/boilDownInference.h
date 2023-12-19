// @copyright<lhx>[2023.12.18]
#pragma once
#include <string>
#include <vector>

#include "expToPar.h"
#include "expToTT.h"
#include "operators.h"

/*
    @preAndCondToOne():
    将pre和cond合并为一个字符串，
    也即从A->B 转变为 A&！B这样一个字符串
*/
std::string preAndCondToOne(const std::string& pre, const std::string& cond);

/*
    @printClauseSet():
    打印子句集合，
*/
void printClauseSet(const std::vector<std::vector<Propos>>& clauseSet);

/*
    @getClauseSet():
    由A&！B得到子句集，
    用计算真值表的方式，得到mp的方式得到子句集，每个字句都是析取
*/
std::vector<std::vector<Propos>> getClauseSet(const std::string& preAndCond);

/*
    @equalToCluse():
    由两个字句，判断它们是否能归结，如果能，返回能归结的propo的位置，
    比如 A|B 与 A|！B 那么返回1
    如果不能归结，返回-1；
*/
int equalToCluse(const std::vector<Propos>& clause1,
                 const std::vector<Propos>& clause2);

/*
    @boilDownInference():
    将子句集合中的每个子句都归结，
    展示每个state中，子句集的状态
    不断的归结，如果归结出的clause为空，说明归结推理成功，
    否则失败
*/
bool boilDownInference(std::vector<std::vector<Propos>> clauseSet);
