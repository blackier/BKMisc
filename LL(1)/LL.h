#include "getFirFol.h"
#include "struct.h"

#ifndef _LL_H
#define _LL_H

class LL{
public:
    LL(getFirst_Follow *ff,std::string ts, std::string nts, std::string rl);
    /***构造分析表***/
    void fillInTheTable();
    /***分析字符串***/
    void analyzeChars(std::string path);
    /***在对应的分析表单元格加入文法***/
    bool addInTableCell(int h,int l,int gramNum);
private:
    getFirst_Follow *getff;
    std::string terSymbol;      //终结符号集合
    int tsLength=0;             //终结符号数量
    std::string nonTerSymbol;   //非终结符号集合
    int ntsLength=0;            //非终结符号数量
    rule *grammer = NULL;       //文法
    int gramNum = 0;            //文法公式数目
    tableCell **analyzeTable;   //预测分析表
    bool isLLGrammer=true;      //判断是为LL(1)文法      
};

#endif