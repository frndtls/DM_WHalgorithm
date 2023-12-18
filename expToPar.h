// @copyright<lhx>[2023.12.16]
#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "expToTT.h"
#include "operators.h"

void expToPar(const std::string& rpn, std::vector<Propos> propos,
              std::string& mp, std::string& dp);

std::string getMp(int count, std::vector<Propos> propos);

std::string getDp(int count, std::vector<Propos> propos);
