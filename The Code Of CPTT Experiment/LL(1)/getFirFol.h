#include<string>
#include "struct.h"
#ifndef _GETFIRFOL_H
#define _GETFIRFOL_H

/******集合实现******/

class getFirst_Follow
{
  public://公有函数
    getFirst_Follow(std::string ts, std::string nts, std::string rl);
    /***获得first集合***/
    void getFirst();

    /***获得follow集合***/
    void getFollow();

    /***判断一个终结符号是否在一个产生式中***/
    bool isInFirstSet(int i,char s,int gramNum);

    /***判断一个终结符号是否在follow集合中***/
    bool isInFollowSet(int i, char s);

    /***获得符号是否为终结符***/
    bool isTerSymbol(char s);

    /***获得一个非终结符在非终结符集合中的位置***/
    int getNTSNum(char s);

    /***获得一个终结符在终结符集合中的位置***/
    int getTSNum(char s);

  private://私有函数

    /***获得first集合***/
    bool deep(int i, char s,int gramNum);
    void addInFirSet(int fol, char s, int gramNum);

    /***获得follow集合***/
    void addInFolSet(int fir, int fol, bool isFir);
    void addInFolSet(int i, char s);

    /***数据***/
    std::string terSymbol;  //终结符号集合
    std::string nonTerSymbol;   //非终结符号集合
    rule *grammer = NULL;  //文法
    set *firstSet = NULL;  //frist集合
    set *followSet = NULL; //follow集合
    int maxnum = 0;        //文法公式数目
};

#endif