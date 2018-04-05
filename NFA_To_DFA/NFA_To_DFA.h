#ifndef _NFA_TO_DFA_H
#define _NFA_TO_DFA_H

#define MAXSTATESNUM 20
#include <string>
#include "intArr.h"

struct state
{
    int stateNum;        //这个状态的编号
    int *nextNum;        //根据输入字符将会指向哪些状态
    intarr nfaArr;       //NFA状态集
    bool isMake = false; //是否标记
    static int maxNum;   //最大状态标号
};

struct sstate
{
    intarr nfaArr; //NFA状态集
    int stateNum = 0;
};

class nfa_to_dfa
{
  public:
    nfa_to_dfa(std::string fn); //默认构造函数
    void getIntArr(int num, std::string s);
    void closure_s();                     //空字符匹配
    void closure_T(int num, int charNum); //字符集匹配
    void inStates();                      //是否在当前DFA状态中了
    void read();                          //读取NFA数据
    void convert();                       //开始转换
    void output();
    ~nfa_to_dfa() {} //析构函数

  private:
    std::string charracters;          //nfa字符集
    int charrLength = 0;              //字符集的长度
    int statesNumber = 0;             //nfa状态个数，默认为0
    int currState = 1;                //开始状态编号，默认为1,不用输入
    int endNum = 1;                   //nfa接受状态个数，默认为1
    int *acceptStates = NULL;         //nfa接受状态集
    std::string **convertFrom = NULL; //转换表
    std::string filePath;             //文件输入对象
    sstate shareState;                //一个共享对象，用于转换

    int acceptNum = 0;      //转换出的dfa接受状态个数
    intarr DfaAcceptstates; //dfa接受状态集
};

#endif // !IOSTREAN