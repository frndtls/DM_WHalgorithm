// @copyright<lhx>[2023.12.15]
#pragma once
#include <iostream>
#include <stdexcept>
#define NUM_OPERATORS 8
namespace Myoperators {

/*
    bool calcul函数定义连接词的计算方式，
    其中calcul(bool a, char op)用于一元连接词！的结果，
    calcul(bool a, char op, bool b)用于二元连接词的结果。
*/
bool calcul(bool a, char op);
bool calcul(bool a, char op, bool b);

/*
    pri数组用于记录运算符的优先级，
    '<':表示栈顶运算符的优先级小，当前运算符入栈
    '>':表示栈顶运算符的优先级大，出栈，计算
    '=':表示整个计算过程结束
    'x':表示'('、')'相遇，可直接出栈
    ' ':表示非法的相遇
*/
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

/*
    isProposition(const char& c)判断是否为命题；
    也即是否为A~Z
*/
bool isProposition(const char& c);

/*
    isOperator(const char& c)判断是否为运算符；
    也即是否为 !    &    |    ^    ~    (    )  \0
*/
bool isOperator(const char& c);

/*
    operatorsIndex(const char& op)返回operator在pri中的索引，
    便于访问pri矩阵
*/
int operatorsIndex(const char& op);
};  // namespace Myoperators
