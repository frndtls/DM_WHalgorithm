// @copyright<lhx>[2023.12.18]
#pragma once
#include <string>
#include <vector>

#include "expToPar.h"
#include "expToTT.h"
#include "operators.h"
std::string preAndCondToOne(const std::string& pre, const std::string& cond);

std::vector<std::vector<Propos>> getClauseSet(const std::string& preAndCond);

int equalToCluse(const std::vector<Propos>& clause1,
                 const std::vector<Propos>& clause2);

bool boilDownInference(std::vector<std::vector<Propos>> clauseSet);
