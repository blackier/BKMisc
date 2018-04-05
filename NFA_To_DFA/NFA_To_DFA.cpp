#include "NFA_To_DFA.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int state::maxNum = 0;

state states[MAXSTATESNUM];

nfa_to_dfa::nfa_to_dfa(std::string fn)
{
    filePath = fn;
    read();
    output();
}

void nfa_to_dfa::read()
{
    ifstream in(filePath);
    getline(in, charracters);
    charrLength = charracters.length();
    in >> statesNumber;
    in >> endNum;
    acceptStates = new int[endNum];
    for (int i = 0; i < endNum; i++)
    {
        in >> acceptStates[i];
    }
    convertFrom = new string *[statesNumber];
    for (int i = 0; i < statesNumber; i++)
    {
        convertFrom[i] = new string[charrLength];
        for (int j = 0; j < charrLength; j++)
        {

            getline(in, convertFrom[i][j], ',');
            cout << convertFrom[i][j] << "*";
        }
        //cout<<endl;
    }
    //cout << convertFrom[10][2] << "";
    convert();
}

void nfa_to_dfa::convert()
{
    int num = 0;
    shareState.nfaArr &= 1;
    closure_s();
    inStates();
    while (!states[num].isMake && num < state::maxNum)
    {
        cout << endl
             << "while" << endl;
        states[num].isMake = true;
        states[num].nextNum = new int[charrLength];
        for (int i = 0; i < charrLength - 1; i++)
        {
            closure_T(num, i);
            closure_s();
            int size = shareState.nfaArr.getSize();
            if (size == 1 && shareState.nfaArr[0] == -1)
            {
                states[num].nextNum[i] = -1;
            }
            else
            {
                inStates();
                states[num].nextNum[i] = shareState.stateNum;
            }
        }
        num++;
    }
}

void nfa_to_dfa::closure_s()
{
    cout << endl
         << "cs" << endl;
    int size = shareState.nfaArr.getSize();
    cout << size << endl;
    if (size == 1 && shareState.nfaArr[0] == -1)
    {
        return;
    }
    for (int i = 0; i < size; i++)
    {
        int nfaNum = shareState.nfaArr[i];
        cout << nfaNum << endl;
        string s = convertFrom[nfaNum - 1][charrLength - 1];
        cout << "String " << s << endl;
        if (s != "-1")
        {
            getIntArr(nfaNum, s);
        }
    }
}

void nfa_to_dfa::getIntArr(int num, std::string s)
{
    static int  sameState=0;
    if (sameState == statesNumber)
    {
        return;
    }
    cout << endl
         << "getintarr" << endl;
    int n = 0;
    for (int i = 0; i < (int)s.length(); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            n = n * 10;
            n += (s[i] - '0');
        }
        if ((s[i] == '|') || (i == s.length() - 1))
        {
            string s = convertFrom[n - 1][charrLength - 1];
            shareState.nfaArr &= n;
            if (s != "-1")
            {
                sameState++;
                getIntArr(n, s);
                sameState--;
            }
            n = 0;
        }
    }
}

void nfa_to_dfa::closure_T(int num, int charNum)
{
    cout << endl
         << "ct" << endl;
    shareState.nfaArr.cleanArr();
    int size = states[num].nfaArr.getSize();
    cout << size << endl;
    for (int i = 0; i < size; i++)
    {
        string s = convertFrom[states[num].nfaArr[i] - 1][charNum];
        cout << "string " << s << " ss" << endl;
        int n = 0;
        if (s == "\n-1" || s == " -1" || s == "-1")
        {
            cout << "string " << s << " cc" << endl;
            continue;
        }
        for (int j = 0; j < (int)s.length(); j++)
        {
            if (s[j] >= '0' && s[j] <= '9')
            {
                n = n * 10;
                n += (s[j] - '0');
            }
            if (s[j] == '|' || j == s.length() - 1)
            {
                cout << n << endl;
                shareState.nfaArr &= n;
                n = 0;
            }
        }
    }
    if (shareState.nfaArr.getSize() == 0)
    {
        shareState.nfaArr &= -1;
    }
}

void nfa_to_dfa::inStates()
{
    cout << endl
         << "instates" << endl;
    for (int i = 0; i < state::maxNum; i++)
    {
        if (states[i].nfaArr == shareState.nfaArr)
        {
            shareState.stateNum = states[i].stateNum;
            return;
        }
    }
    cout << shareState.nfaArr[0] << endl;
    states[state::maxNum].nfaArr = shareState.nfaArr;
    cout << states[state::maxNum].nfaArr[0] << endl;
    states[state::maxNum].stateNum = state::maxNum + 1;
    shareState.stateNum = state::maxNum + 1;
    cout << state::maxNum++;
    cout << state::maxNum;
}

void nfa_to_dfa::output()
{
    ofstream out("nfa_to_dfa.dfa", ios::app);
    //cin>>charracters;
    //state::maxNum++;
    for (int i = 0; i < charrLength-1; i++)
    {
        out << charracters[i];
    }
    out << endl;
    out << state::maxNum << endl;
    for (int i = 0; i < state::maxNum; i++)
    {
        for (int j = 0; j < endNum; j++)
        {
            if (states[i].nfaArr.getNum(acceptStates[j]))
            {
                DfaAcceptstates &= states[i].stateNum;
                acceptNum++;
                continue;
            }
        }
    }
    out << acceptNum << endl;
    for (int i = 0; i < acceptNum; i++)
    {
        out << DfaAcceptstates[i] << " ";
    }
    out << endl;
    for (int i = 0; i < state::maxNum; i++)
    {
        out << "{";
        for (int k = 0; k < states[i].nfaArr.getSize(); k++)
        {
            out << states[i].nfaArr[k] << ",";
        }
        out << "}\t\t";

        for (int j = 0; j < charrLength - 1; j++)
        {

            out << states[i].nextNum[j] << " ";
        }
        out << endl;
    }
}