#ifndef _MINIMALDFA_H
#define _MINIMALDFA_H
#include <string>
#include"intArr.h"


struct minState
{
    static int maxNum;      //最大状态数
    intarr sameState;       //相同的输出的状态集合
    int  minNum;            //这个最小dfa的状态标
    int *nextState=NULL;    //不同输入字符的情况下指向不同状态的集合
    int isAcceptState=0;    //是否为接受状态
};

class minDfa
{
  public:
    minDfa(std::string str);  //构造函数
    void read();              //读取数据
    void divide();            //划分dfa
    void output();            //状态集
    bool isqueal();           //判断两个最小化dfa是否相等

  private:
    std::string charracters;  //字符集
    int charLength=0;
    int stateNum = 0;         //状态个数，默认为0
    int currState = 1;        //开始状态编号，默认为1
    int endNum = 1;           //接受状态个数，默认为1
    int *acceptState = NULL;  //接受状态
    int **convertFrom = NULL; //转换表
    minState *states;         //最小化dfa状态集
    std::string path;         //要读取文件的路劲
};

#endif