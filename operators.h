// @copyright<lhx>[2023.12.15]
#pragma once
#include <iostream>
#include <stdexcept>
#define NUM_OPERATORS 8
namespace Myoperators {
bool calcul(bool a, char op);
bool calcul(bool a, char op, bool b);

const char pri[NUM_OPERATORS][NUM_OPERATORS] = {
    /*当前运算符!    &    |    ^    ~    (    )  \0*/
    /* 栈 !*/ '<', '>', '>', '>', '>', '<', '>', '>',
    /* 顶 &*/ '<', '>', '>', '>', '>', '<', '>', '>',
    /* 运 |*/ '<', '<', '>', '>', '>', '<', '>', '>',
    /* 算 ^*/ '<', '<', '<', '>', '>', '<', '>', '>',
    /* 符 ~*/ '<', '<', '<', '<', '>', '<', '>', '>',
    /*    (*/ '<', '<', '<', '<', '<', '<', 'x', ' ',
    /*    )*/ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    /*   \0*/ '<', '<', '<', '<', '<', '<', ' ', '=',
};

bool isProposition(const char& c);
bool isOperator(const char& c);
int operatorsIndex(const char& op);
};  // namespace Myoperators
