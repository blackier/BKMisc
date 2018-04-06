#include "LL.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
using namespace std;

LL::LL(getFirst_Follow *ff, std::string ts, std::string nts, std::string rl)
{
    //获得first和follow集合的对象
    getff=ff;
    //文件对象
    ifstream in;
    //获得终结符
    in.open(ts, ios::in);
    getline(in, terSymbol);
    tsLength=terSymbol.length();
    cout << terSymbol << endl;
    in.close();
    //获得非终结符
    in.open(nts, ios::in);
    getline(in, nonTerSymbol);
    ntsLength=nonTerSymbol.length();
    cout << nonTerSymbol << endl;
    in.close();
    //获得文法转换
    in.open(rl, ios::in);
    grammer = new rule[MAXNUM];
    while (!in.eof())
    {
        getline(in, grammer[gramNum].startSymbol, ',');
        getline(in, grammer[gramNum].tuidao);
        cout << grammer[gramNum].startSymbol << "," << grammer[gramNum].tuidao << endl;
        gramNum++;
    }
    //创建表格
    analyzeTable=new tableCell* [ntsLength];
    for(int i=0;i<ntsLength;i++){
        analyzeTable[i]=new tableCell[tsLength];
    }
}

void LL::fillInTheTable(){
    /*
    对于每一个产生式 A->a
    (1)对于first(a)中的每个终结符号 ？，将 A->a 加入到 M[A,a]种
    (2)如果空串 e 在first(a)中，那么对于follow(A)中的每个终结符号？，将 A->a 加入到
       M(A,b)中。如果 e 在first(a)中，且 $ 在first(A)中，也将 A->a 加入到M[A,$]中。
    */
    for(int i=0;i<ntsLength;i++){
        for(int j=0;j<gramNum;j++){
            if(nonTerSymbol[i]==grammer[j].startSymbol[0]){
                for (int k = 0; k < tsLength && grammer[j].tuidao[0]!='e'; k++)
                {
                    if (getff->isInFirstSet(i, terSymbol[k],j))
                    {
                        addInTableCell(i,k,j);
                    }
                }
                if (getff->isInFirstSet(i, 'e', j))
                {
                    int k=0;
                    for (; k < tsLength; k++)
                    {
                        if (getff->isInFollowSet(i, terSymbol[k]))
                        {
                            addInTableCell(i, k, j);
                        }
                    }
                }
            }
        }
    }
    //输出分析表
    for (int i = 0; i < ntsLength; i++)
    {
        cout<<"******非终结符号："<<nonTerSymbol[i]<<"******"<<endl;
        for (int j = 0; j < tsLength; j++)
        {
            if (!analyzeTable[i][j].error)
            {
                cout<<"终结符号："<<terSymbol[j]<<""<<endl;
                int num = analyzeTable[i][j].num;
                for (int k = 0; k < num; k++)
                {
                    cout<<"\t"<<analyzeTable[i][j].cell[k].startSymbol<<"->";
                    cout << analyzeTable[i][j].cell[k].tuidao<<endl;
                    if(k==1){
                        isLLGrammer=false;
                    }
                }
            }
        }
        cout<<endl;
    }
    if(isLLGrammer){
        cout<<"这是一个LL(1)文法"<<endl;
    }
    else{
        cout<<"这不是一个LL(1)文法"<<endl;
    }
}

bool LL::addInTableCell(int h,int l,int gramNum){
    //先判断已有，没有加入
    int num=analyzeTable[h][l].num;
    for(int i=0;i<num;i++){
        if(grammer[gramNum].tuidao==analyzeTable[h][l].cell[i].tuidao){
            return true;
        }
    }
    analyzeTable[h][l].cell[num].startSymbol = grammer[gramNum].startSymbol[0];
    analyzeTable[h][l].cell[num].tuidao = grammer[gramNum].tuidao;
    analyzeTable[h][l].num++;
    analyzeTable[h][l].error=false;
    return false;
}

void LL::analyzeChars(std::string path){
    if(!isLLGrammer){
        cout<<"不是LL(1)文法不进行分析"<<endl;
        return;
    }
    ifstream in(path);
    string chars;
    getline(in,chars);  //输入串
    int length=chars.length();
    int ip=0;           //输入指针
    queue<char> match;  //已匹配的串
    stack<char> st;     //栈
    st.push('$');       //初始化栈
    char E=grammer[0].startSymbol[0];
    st.push(E);
    
    int const spaceNum=20;
    {   //输出初始数据
        cout << "已匹配\t\t栈\t\t    输入\t\t  动作" << endl;
        for (int i = 0; i < spaceNum-st.size(); i++)
        {
            cout << " ";
        }
        stack<char> sta=st;
        while(!sta.empty()){
            cout<<sta.top();
            sta.pop();
        }
        for (int i = 0; i < spaceNum-length+ip; i++)
        {
            cout << " ";
        }
        cout<<chars<<"$"<<endl;
    }
    
    char top=st.top();
    while(top!='$'){
        char ch;
        if(ip==length){
            ch='$';
        }
        else{
            ch=chars[ip];
        }
        int h=getff->getNTSNum(top);
        int l=getff->getTSNum(ch);
        if(top==ch){
            match.push(ch);
            st.pop();
            ip++;
            { //输出数据
                //输出已匹配字符
                queue<char> ma=match;
                while(!ma.empty()){
                    cout<<ma.front();
                    ma.pop();
                }
                //间隔
                for (int i = 0; i < spaceNum - st.size()-match.size(); i++)
                {
                    cout << " ";
                }
                //输出栈
                stack<char> sta = st;
                while (!sta.empty())
                {
                    cout << sta.top();
                    sta.pop();
                }
                //间隔
                for (int i = 0; i < spaceNum - length + ip; i++)
                {
                    cout << " ";
                }
                //输出剩余输入
                for(int i=ip;i<length;i++){
                    cout<<chars[i];
                }
                cout << "$";
                //输出动作
                cout<<"\t\t匹配 "<<ch<<endl;
            }
        }
        else if(getff->isTerSymbol(top)){
            cout<<"error1"<<endl;
            return;
        }
        else if(analyzeTable[h][l].error){
            cout << "error2" << endl;
            return;
        }
        else{
            int n = analyzeTable[h][l].cell[0].tuidao.length();
            char ss=analyzeTable[h][l].cell[0].startSymbol[0];
            string str=analyzeTable[h][l].cell[0].tuidao;
            st.pop();
            n--;
            for(;n>=0&&str[0]!='e';n--){
                st.push(str[n]);
            }
            { //输出数据
                //输出已匹配字符
                queue<char> ma = match;
                while (!ma.empty())
                {
                    cout << ma.front();
                    ma.pop();
                }
                //间隔
                for (int i = 0; i < spaceNum - st.size() - match.size(); i++)
                {
                    cout << " ";
                }
                //输出栈
                stack<char> sta = st;
                while (!sta.empty())
                {
                    cout << sta.top();
                    sta.pop();
                }
                //间隔
                for (int i = 0; i < spaceNum - length+ip; i++)
                {
                    cout << " ";
                }
                //输出剩余输入
                for(int i=ip;i<length;i++){
                    cout<<chars[i];
                }
                cout<< "$";
                //输出动作
                cout << "\t\t输出 " <<ss<<"->"<<str<<endl;
            }
        }
        top=st.top();
    }
    cout<<"匹配成功！"<<endl;
}