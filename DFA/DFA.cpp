#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string inputChar;           //要匹配的字符串

string charracters;         //字符集
int stateNum = 0;           //状态个数，默认为0
int currState = 1;          //开始状态编号，默认为1
int endNum = 1;             //接受状态个数，默认为1
int *acceptState = NULL;    //接受状态
int **convertFrom = NULL;   //转换表

void init()
{
    cout << "输入字符集,?表示任意字符，若可以匹配任意字符，请放在最后" << endl;
    cin >> charracters;
    int leng = charracters.length();
    cout << "输入状态个数，默认从1开始，构建状态集" << endl;
    cin >> stateNum;
    cout << "输入接受状态的个数，之后接着输入状态的编号" << endl;
    cin >> endNum;
    acceptState = new int[endNum];
    for (int i = 0; i < endNum; i++)
    {
        cin >> acceptState[i];
    }
    cout << "输入状体装换表,例如\n* / other" << endl;
    cout << "2 -1 -1\n -1 3 -1\n 3 4 3\n 5 4 3\n -1 -1 -1" << endl;
    cout << "行为状态标号，列为字符集，对应为一个二维数组，\n在哪个状态输入哪个字符转到哪个状态，-1为错误状态" << endl;
    for (int i = 0; i < leng; i++)
    {
        cout << charracters[i] << ends;
    }
    cout << endl
         << "开始输入转换表" << endl;
    convertFrom = new int *[stateNum];
    for (int i = 0; i < stateNum; i++)
    {
        convertFrom[i] = new int[leng];
        for (int j = 0; j < leng; j++)
        {
            cin >> convertFrom[i][j];
        }
    }
}

void read()
{
    ifstream in("dfa_in1.dfa");

    if (in.is_open())                       // 有该文件
    {
        getline(in, charracters);           //读取字符集
        int leng = charracters.length();
        in >> stateNum;                     //读取状态数
        in >> endNum;                       //读取接受状态个数
        acceptState = new int[endNum];      //读取接受状态
        for (int i = 0; i < endNum; i++)
        {
            acceptState[i]=0;
            in >> acceptState[i];
        }

        convertFrom = new int *[stateNum];  //读取转换表
        for (int i = 0; i < stateNum; i++)
        {
            convertFrom[i] = new int[leng];
            for (int j = 0; j < leng; j++)
            {
                convertFrom[i][j]=0;
                in >> convertFrom[i][j];
            }
        }
    }
    else    // 没有该文件
    {
        cout << "没有这个文件" << endl;
        return;
    }
}

void input()
{
    cout << "输入要识别的字符串" << endl;
    cin >> inputChar;
}

void DFA()
{
    int num = 0;
    while (num < (int)inputChar.length())
    { //循环匹配输入的字符
        int y = 0;
        bool isExist = false; //检测下一个字符是否在字符集中
        for (; y < (int)charracters.length(); y++)
        {
            if (inputChar[num] == charracters[y])
            {
                isExist = true;
                break;
            }
            //任意字符匹配匹配
            else if (y == charracters.length() - 1 && charracters[y] == '?')
            {
                isExist = true;
                break;
            }
        }
        if (isExist)
        { //检测输入的字符是否能在当前状态转换表中匹配
            if (convertFrom[currState - 1][y] > 0)
            {
                currState = convertFrom[currState - 1][y];
            }
            else
            {
                cout << "当前字符匹配出错 -1 :" << num + 1 << " " << inputChar[y] << endl;
                return;
            }
        }
        else
        {
            cout << "当前字符无法出错，不存在字符集中:" << num + 1 << " " << inputChar[y] << endl;
            return;
        }
        num++;
    }
    bool notAcceptState = true; //判断当前状态是否在借号状态中
    for (int i = 0; i < endNum; i++)
    {
        if (currState == acceptState[i])
        {
            cout << "匹配成功" << endl;
            notAcceptState = false;
        }
    }
    if (notAcceptState)
    {
        cout << "字符串不在接受状态中" << endl;
    }
}

void outChars(int n, int *arr)
{
    ofstream out("dfa_out.dfa", ios::app); //将在N个范围内的字符串束输入到文件里
    for (int i = 0; i < n; i++)
    {
        cout << charracters[arr[i]];
        out << charracters[arr[i]];
    }
    cout << endl;
    out << endl;
    return;
}

void isAcceptState(int currstate, int n, int *arr)
{ //判断当前装填是否在接受状态中
    for (int i = 0; i < endNum; i++)
    {
        if (currstate == acceptState[i])
        {
            outChars(n, arr);
        }
    }
}

void searchChars(int currstate, int n, int N, int *arr)
{
    if (n < N) //每次匹配完一个字符，判断已经匹配的字符串是否在dfa的语言集中
    {
        isAcceptState(currstate, n, arr);
    }
    else
    {
        isAcceptState(currstate, n, arr);
        return;
    }
    for (int i = 0; i < (int)charracters.length(); i++)
    {   //从开始状态根据转换表依次匹配能出去的字符并转换状态通过递归遍历
        if (convertFrom[currstate - 1][i] > 0)
        {
            arr[n] = i;
            n++;
            searchChars(convertFrom[currstate - 1][i], n, N, arr);
            n--;
        }
    }
}

int main()
{
    cout << "手动输入：1 ，从文件读取 0" << endl;
    bool isHandIn = false;
    cin >> isHandIn;
    if (isHandIn)
    {
        init();
    }
    else
    {
        read();
    }
    
    input();
    DFA();

    cout << "输入待显示的字符串的最大长度N" << endl;
    int N;
    cin >> N;
    int *arr = new int[N];
    searchChars(1, 0, N, arr);
    delete []arr;
    delete []acceptState;
    delete []convertFrom;
    system("pause");
    return 0;
}
