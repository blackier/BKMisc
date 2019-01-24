#include "minimalDFA.h"
#include <iostream>
#include <fstream>
using namespace std;

int minState::maxNum = 0;

minDfa::minDfa(std::string str)
{
    path = str;
    read();
}

void minDfa::read()
{
    cout << "read" << endl;
    ifstream in(path);
    getline(in, charracters);
    cout << charracters << endl;

    charLength = charracters.length();
    in >> stateNum;
    cout << stateNum << endl;

    in >> endNum;
    cout << endNum << endl;
    acceptState = new int[endNum];
    for (int i = 0; i < endNum; i++)
    {
        in >> acceptState[i];
        cout << acceptState[i] << ends;
    }
    cout << endl;

    convertFrom = new int *[stateNum];
    for (int i = 0; i < stateNum; i++)
    {
        convertFrom[i] = new int[charLength];
        for (int j = 0; j < charLength; j++)
        {
            in >> convertFrom[i][j];
            cout << convertFrom[i][j] << ends;
        }
        cout << endl;
    }
    divide();
}

void minDfa::divide()
{
    cout << "divide" << endl;
    states = new minState[20];
    int *isAccept = new int[stateNum];
    int *isInstates = new int[stateNum];
    for (int i = 0; i < stateNum; i++)
    {
        bool isaccept = false;
        for (int j = 0; j < endNum; j++)
        {
            if (acceptState[j] == i + 1)
            {
                isaccept = true;
                break;
            }
        }
        if (isaccept)
        {
            isAccept[i] = 1;
        }
        else
        {
            isAccept[i] = 0;
        }
        isInstates[i] = 0;
    }
    for (int i = 0; i < stateNum;)
    {
        states[minState::maxNum].sameState &= i + 1;
        states[minState::maxNum].minNum = minState::maxNum + 1;
        states[minState::maxNum].isAcceptState = isAccept[i];
        states[minState::maxNum].nextState = new int[charLength]{0};
        isInstates[i] = 1;
        for (int k = 0; k < charracters.length(); k++)
        {
            states[minState::maxNum].nextState[k] = convertFrom[i][k];
        }
        for (int j = i + 1; j < stateNum; j++)
        {
            bool isqueal = true;
            for (int k = 0; k < charracters.length(); k++)
            {
                if (convertFrom[i][k] != convertFrom[j][k])
                {
                    isqueal = false;
                }
            }
            if (isqueal)
            {
                if (isAccept[i] != isAccept[j])
                {
                    continue;
                }
                states[minState::maxNum].sameState &= j + 1;
                isInstates[j] = 1;
            }
        }
        minState::maxNum++;
        i++;
        while (isInstates[i] && i < stateNum)
        {
            i++;
        }
    }
    for (int i = 0; i < minState::maxNum; i++)
    {
        for (int j = 0; j < minState::maxNum; j++)
        {
            for (int k = 0; k < charLength; k++)
            {
                int t = states[i].nextState[k];
                if (states[j].sameState.getNum(t))
                {
                    states[i].nextState[k] = states[j].minNum;
                }
            }
        }
    }
    output();
}

void minDfa::output()
{
    ofstream out("mindfa.dfa", ios::app);
    for (int i = 0; i < minState::maxNum; i++)
    {
        out << "{";
        for (int j = 0; j < states[i].sameState.getSize(); j++)
        {
            out << states[i].sameState[j] << ",";
        }
        out << "}\t";
        out << states[i].minNum << ": ";
        for (int j = 0; j < charracters.length(); j++)
        {
            out << states[i].nextState[j] << " ";
        }
        out << "\t\tisacceptstate:" << states[i].isAcceptState;
        out << endl;
    }
    out << "***********" << endl;
}