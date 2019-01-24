#include <string>
#ifndef MAXNUM
#define MAXNUM 100
#endif
#ifndef _STRUCT_H
#define _STRUCT_H

/******数据定义******/
struct rule
{                       //一个文法
    std::string startSymbol; //开始符号
    std::string tuidao;      //推导式
};

struct record{      //记录一个终结符号由那些产生式得出的
    int num=0;      //数量
    int gramNum[MAXNUM];    //产生式的编号
};

struct set
{                     //集合
    char startSymbol; //非终结符
    char set[MAXNUM]; //frist or follow集合
    record gramNum[MAXNUM]; //记录一个终结符号是由哪些文法推导出的
    int num = 0;
    bool isExistE = false; //是否存在空串
};

struct tableCell{   //预测分析表的一个单元
    int num=0;
    rule cell[MAXNUM];
    bool error=true;
};

#endif