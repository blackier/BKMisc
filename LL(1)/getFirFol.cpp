#include<iostream>
#include<fstream>
#include "getFirFol.h"
using namespace std;

//初始化
getFirst_Follow::getFirst_Follow(string ts, string nts, string rl)
{
    ifstream in;
    //获得终结符
    in.open(ts, ios::in);
    getline(in, terSymbol);
    cout << terSymbol << endl;
    in.close();
    //获得非终结符
    in.open(nts, ios::in);
    getline(in, nonTerSymbol);
    cout << nonTerSymbol << endl;
    in.close();
    //获得文法转换
    in.open(rl, ios::in);
    grammer = new rule[MAXNUM];
    while (!in.eof())
    {
        getline(in, grammer[maxnum].startSymbol, ',');
        getline(in, grammer[maxnum].tuidao);
        cout << grammer[maxnum].startSymbol << "," << grammer[maxnum].tuidao << endl;
        maxnum++;
    }
    //设定frist集合
    firstSet = new set[nonTerSymbol.length()];
    //设定follow集合
    followSet = new set[nonTerSymbol.length()];
}

//判断是否是终结符号
bool getFirst_Follow::isTerSymbol(char s)
{
    for (int i = 0; i < terSymbol.length(); i++)
    {
        if (s == terSymbol[i])
        {
            return true;
        }
    }
    return false;
}
//获得一个非终结符在非终结符集合中的位置
int getFirst_Follow::getNTSNum(char s)
{
    for (int i = 0; i < nonTerSymbol.length(); i++)
    {
        if (s == nonTerSymbol[i])
        {
            return i;
        }
    }
    return 0;
}

//获得一个终结符在终结符集合中的位置
int getFirst_Follow::getTSNum(char s)
{
    for (int i = 0; i < terSymbol.length(); i++)
    {
        if (s == terSymbol[i])
        {
            return i;
        }
    }
    return 0;
}

//判断一个终结符号是否在一个产生式中
bool getFirst_Follow::isInFirstSet(int i, char s,int gramNum)
{
    int num = firstSet[i].num;
    for (int j = 0; j < num; j++)
    {
        if (s == firstSet[i].set[j])
        {
            int n=firstSet[i].gramNum[j].num;
            for(int k=0;k<n;k++){
                if (gramNum == firstSet[i].gramNum[j].gramNum[k])
                {
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}
//判断一个终结符号是否在follow集合中
bool getFirst_Follow::isInFollowSet(int i, char s)
{
    int num = followSet[i].num;
    for (int j = 0; j < num; j++)
    {
        if (s == followSet[i].set[j])
        {
            return true;
        }
    }
    return false;
}

//判断字符是否已经在first集合中,不在则加入
void getFirst_Follow::addInFirSet(int firNum, char s,int gramNum)
{
    int num = firstSet[firNum].num;
    for (int i = 0; i < num; i++)
    {
        if (firstSet[firNum].set[i] == s)
        {
            int n=firstSet[firNum].gramNum[i].num;
            for(int j=0;j<n;j++){
                if (firstSet[firNum].gramNum[i].gramNum[j]==gramNum){
                    return;
                }
            }
            firstSet[firNum].gramNum[i].gramNum[n]=gramNum;
            firstSet[firNum].gramNum[i].num++;
            return;
        }
    }
    firstSet[firNum].set[num] = s;
    firstSet[firNum].num++;

    int n = firstSet[firNum].gramNum[num].num;
    firstSet[firNum].gramNum[num].gramNum[n] = gramNum;
    firstSet[firNum].gramNum[num].num++;
}

//获得frist集合
void getFirst_Follow::getFirst()
{
    int size = nonTerSymbol.length();
    for (int i = 0; i < size; i++)
    { //非终结符号
        firstSet[i].startSymbol = nonTerSymbol[i];
        for (int j = 0; j < maxnum; j++)
        { //文法
            bool isExistE = true;
            if (firstSet[i].startSymbol == grammer[j].startSymbol[0])
            { //找到相应的推导式
                string tuidao = grammer[j].tuidao;
                if (tuidao[0] == 'e')
                { //如果推导的出空串，则加入
                    addInFirSet(i, 'e',j);
                    firstSet[i].isExistE = true;
                    continue;
                }
                int size = grammer[j].startSymbol.length();
                for (int k = 0; k < size && isExistE; k++)
                {
                    if (isTerSymbol(tuidao[k])) //如果推导式第一个字符为终结符号
                    {
                        addInFirSet(i, tuidao[k],j);
                        break;
                    }
                    isExistE = deep(i, tuidao[k],j); //如果不是，则加入frist(tuidao[0])
                }
            }
        }
    }
    cout<<"first set is"<<endl;
    for (int i = 0; i < size; i++)
    {
        cout << firstSet[i].startSymbol << "{";
        for (int j = 0; j < firstSet[i].num; j++)
        {
            cout << firstSet[i].set[j] << ",";
        }
        cout << "}" << endl;
        // for (int j = 0; j < firstSet[i].num; j++)
        // {
        //     int n=firstSet[i].gramNum[j].num;
        //     for(int k=0;k<n;k++){
        //         cout << firstSet[i].gramNum[j].gramNum[k];
        //     }
        //     cout << endl;
        // }
    }
}

bool getFirst_Follow::deep(int i, char s,int gramNum)
{
    bool isexiste = false;
    for (int j = 0; j < maxnum; j++)
    { //文法
        bool isExistE = true;
        if (s == grammer[j].startSymbol[0])
        { //找到相应的推导式
            string tuidao = grammer[j].tuidao;
            if (tuidao[0] == 'e')
            { //如果推导的出空串，则加入
                addInFirSet(i, 'e',gramNum);
                isexiste = true;
                firstSet[i].isExistE = true;
                continue;
            }
            int size = grammer[j].startSymbol.length();
            for (int k = 0; k < size && isExistE; k++)
            {
                if (isTerSymbol(tuidao[k])) //如果推导式第一个字符为终结符号
                {
                    addInFirSet(i, tuidao[k],gramNum);
                    break;
                }
                isExistE = deep(i, tuidao[k],gramNum); //如果不是，则加入frist(tuidao[0])
                if (isExistE == true)
                {
                    isexiste = true;
                }
            }
        }
    }
    return isexiste;
}

//获得follow集合
void getFirst_Follow::getFollow()
{
    int size = nonTerSymbol.length();
    for (int i = 0; i < size; i++)
    {
        char s = followSet[i].startSymbol = nonTerSymbol[i];
        for (int j = 0; j < maxnum; j++)
        {
            int si = grammer[j].tuidao.length();
            string str = grammer[j].tuidao;
            for (int k = 0; k < si; k++)
            {
                if (str[k] == s && k == si - 1)
                {
                    int ii = getNTSNum(grammer[j].startSymbol[0]);
                    addInFolSet(ii, i, false);
                }
                else if (str[k] == s)
                {
                    while (1)
                    {
                        k++;
                        if (isTerSymbol(str[k]))
                        {
                            addInFolSet(i, str[k]);
                            break;
                        }
                        int ii = getNTSNum(str[k]);
                        addInFolSet(ii, i, true);
                        if (!firstSet[ii].isExistE)
                        {
                            break;
                        }
                        if (si == k + 1)
                        {
                            int ii = getNTSNum(grammer[j].startSymbol[0]);
                            addInFolSet(ii, i, false);
                            break;
                        }
                    }
                }
            }
        }
        addInFolSet(i, '$');
    }
    cout<<"follow set is"<<endl;
    for (int i = 0; i < size; i++)
    {
        cout << followSet[i].startSymbol << "{";
        for (int j = 0; j < followSet[i].num; j++)
        {
            cout << followSet[i].set[j] << ",";
        }
        cout << "}" << endl;
    }
}

void getFirst_Follow::addInFolSet(int fir, int fol, bool isFir)
{
    if (isFir)
    {
        goto LL;
    }
    for (int i = 0; i < followSet[fir].num; i++)
    {
        if (followSet[fir].set[i] != 'e')
        {
            addInFolSet(fol, followSet[fir].set[i]);
        }
    }
    return;
LL:
    for (int i = 0; i < firstSet[fir].num; i++)
    {
        if (firstSet[fir].set[i] != 'e')
        {
            addInFolSet(fol, firstSet[fir].set[i]);
        }
    }
}
void getFirst_Follow::addInFolSet(int fol, char s)
{
    int num = followSet[fol].num;
    for (int i = 0; i < num; i++)
    {
        if (followSet[fol].set[i] == s)
        {
            return;
        }
    }
    followSet[fol].set[num] = s;
    followSet[fol].num++;
}