# README

## 一些符号：
- ！非
- & 合取
- | 析取
- ^ 蕴含
- ~ 双条件
- 命题全部用A_Z的大写英文字母表示
  
## 编译请参照makefile进行

## 各任务的思路
- **命题公式与真值表**
1. 由命题公式列出真值表：
     1. 将表达式转变为RPN；
     2. 由RPN求出真值表每一项的值;
     3. 测试代码为 **expToTT_test.cpp**
        1. 直接输入公式测试即可
   
        ![测试代码](../code/images/expToTT_test.png)
   
2. 由命题列主析取范式，主合取范式： 
     1. 由命题公式求出真值表；
     2. 根据真值表的0 OR 1，列出极大值或极小值；
     3. 测试代码为 **expToPar_test.cpp**
        1. 直接输入公式测试即可
   
        ![测试代码](../code/images/expToPar_test.png)

3. 由真值表列命题公式 
     1. 写**主析取范式**
     2. 测试代码为 **ttToExp_test.cpp**
        1. 先输入命题个数；
        2. 再输入这些命题的名称，比如 ```P Q``` ；
        3. 再按行输入真值表，比如```1 1 0```,表示P、Q均为1时，公式为0；
        4. **注意输入正确的真值表，避免冲突**
   
        ![测试代码](../code/images/ttToExp_test.png)
 
- **归结推理的实现**
1. 思路：
   1. 将A->B,转换为A&！B;
   2. 再将A&！B转化为rpn,求出其主合取范式；
   3. 由主合取范式建立起子句集；
   4. 进行归结，如果归结出空字句，推理成功；
   5. 否则，推理失败；
2. 测试代码为 **boilDownInference_test.cpp**
   1. 依次输入前提与结论，测试即可；
   
        ![测试代码](../code/images/boilDowninference_test.png)

- **王浩算法的实现**
1. 思路：
   1. 将A->B称为一个公理;
   2. 如果无法用前后件规则消去运算符的公理，称为最小公理；
   3. 由一个公理开始进行基于queue的BFS；
      1. 如果它是最小公理，那么检查公理是否成立；
         1. 如果不成立，那么推理失败；
         2. 如果成立，那么继续进行BFS；
      2. 如果不是最小公理，那么使用前后件规则，分离出一个或两个子公理，入队；
   4. 只有当所有最小公理全部check成功时，推理成功；
2. 测试代码为 **WHalgorithm_test.cpp**
   1. 依次输入前提与结论，测试即可

        ![测试代码](../code/images/WHalgorithm_test.png)