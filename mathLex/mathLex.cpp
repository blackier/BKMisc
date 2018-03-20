#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#define MAXTOKENLEN 40
#define MAXRESERVED 5
using namespace std;

char tokenString[MAXTOKENLEN + 1];
int line = 0;
typedef enum { //DFA状态集
    START,
    INCOMMENT,
    INNUM,
    INID,
    ININ,
    INOUT,
    DONE
} stateType;

typedef enum { //用于匹配的类型，判断输入
    /* 异常状态 */
    ENDFILE,
    ERROR,
    /* 保留字 */
    CIN,
    COUT,
    WHILE,
    THEN,
    END,
    /* DFA状态 */
    ID,
    NUM,
    /* 特殊符号 */
    IN,
    OUT,
    EQ,
    PLUS,
    MINUS,
    TIMES,
    OVER,
    LPAREN,
    RPAREN,
    SEMI
} tokenType;

static struct //保留字结构体，用于输出
{
    const char *str;
    tokenType tok;
} reservedWords[MAXRESERVED] = {
    {"cin", CIN},
    {"while", WHILE},
    {"then", THEN},
    {"cout", COUT},
    {"end", END}};

bool isLetter(char c) //是否为字符
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isDigit(char c) //判断是否为数字
{
    if (c >= '0' && c <= '9')
    {
        return true;
    }
    else
    {
        return false;
    }
}

static tokenType reservedLookup(char *s)
{
    for (int i = 0; i < MAXRESERVED; i++)
        if (!strcmp(s, reservedWords[i].str))
            return reservedWords[i].tok;
    return ID;
}

void printToken(tokenType token, const char tokenString[]) //输出函数
{
    switch (token)
    {
    case CIN:
    case COUT:
    case WHILE:
    case THEN:
    case END:
        cout << "\t" << line << ": reserved word:" << tokenString << endl;
        break;
    case IN:
        cout << "\t" << line << ": >>" << endl;
        break;
    case OUT:
        cout << "\t" << line << ": <<" << endl;
        break;
    case EQ:
        cout << "\t" << line << ": =" << endl;
        break;
    case PLUS:
        cout << "\t" << line << ": +" << endl;
        break;
    case MINUS:
        cout << "\t" << line << ": -" << endl;
        break;
    case TIMES:
        cout << "\t" << line << ": *" << endl;
        break;
    case OVER:
        cout << "\t" << line << ": /" << endl;
        break;
    case NUM:
        cout << "\t" << line << ": NUM, val=" << tokenString << endl;
        break;
    case ID:
        cout << "\t" << line << ": ID, name= " << tokenString << endl;
        break;
    case SEMI:
        cout << "\t" << line << ": ;" << endl;
        break;
    case LPAREN:
        cout << "\t" << line << ": (" << endl;
        break;
    case RPAREN:
        cout << "\t" << line << ": )" << endl;
        break;
    case ERROR:
        cout << "ERROR:" << tokenString << endl;
        break;
    default: /* should never happen */
        cout << "Unknown token:" << token << endl;
    }
}

void getToken(string ss) // 词法分析
{
    int tokenStringIndex = 0;           // 匹配字符的下标
    tokenType currentToken;             // 当前匹配状态
    static stateType stateSave = START; //保存DFA状态
    stateType state = stateSave;        //DFA状态
    bool save = true;
    int ssIndex = 0; // 输入字符串ss的下标
    while (ssIndex < ss.length())
    {
        while (ssIndex < ss.length() && state != DONE)
        {
            char c = ss[ssIndex];
            save = true;
            switch (state)
            {
            case START: //开始状态
                if (isdigit(c))
                {
                    state = INNUM;
                }
                else if (isLetter(c))
                {
                    state = INID;
                }
                else if (c == '>')
                {
                    state = ININ;
                }
                else if (c == '<')
                {
                    state = INOUT;
                }
                else if ((c == ' ') || (c == '\t') || (c == '\n'))
                {
                    save = false;
                }
                else if (c == '{')
                {
                    save = false;
                    state = INCOMMENT;
                }
                else
                {
                    state = DONE;
                    switch (c)
                    {
                    case '=':
                        currentToken = EQ;
                        break;
                    case '+':
                        currentToken = PLUS;
                        break;
                    case '-':
                        currentToken = MINUS;
                        break;
                    case '*':
                        currentToken = TIMES;
                        break;
                    case '/':
                        currentToken = OVER;
                        break;
                    case '(':
                        currentToken = LPAREN;
                        break;
                    case ')':
                        currentToken = RPAREN;
                        break;
                    case ';':
                        currentToken = SEMI;
                        break;
                    default:
                        currentToken = ERROR;
                        break;
                    }
                }
                break;
            case INCOMMENT: //注释状态
                save = false;
                if (c == '}')
                {
                    state = START;
                }
                break;
            case INNUM: //数字状态
                if (!isdigit(c))
                {
                    ssIndex--;
                    save = false;
                    state = DONE;
                    currentToken = NUM;
                }
                break;
            case INID: //标识符状态
                if (!isLetter(c))
                {
                    ssIndex--;
                    save = false;
                    state = DONE;
                    currentToken = ID;
                }
                break;
            case ININ: //输入状态
                state = DONE;
                if (c == '>')
                {
                    currentToken = IN;
                }
                else
                {
                    currentToken = ERROR;
                }
                break;
            case INOUT:
                state = DONE;
                if (c == '<')
                {
                    currentToken = OUT;
                }
                else
                {
                    currentToken = ERROR;
                }
                break;
            case DONE: //接受状态
            default:
                cout << "happen a never state" << endl;
                break;
            }
            if ((save) && (tokenStringIndex <= MAXTOKENLEN))
            {
                tokenString[tokenStringIndex++] = (char)c;
            }
            if (state == DONE)
            {
                tokenString[tokenStringIndex] = '\0';
                if (currentToken == ID)
                    currentToken = reservedLookup(tokenString);
            }
            ssIndex++;
        }
        if (state == DONE)
        {
            printToken(currentToken, tokenString);
            state = START;
        }
        tokenStringIndex = 0;
    }
    stateSave = state;
}

int main()
{
    fstream in("input.math");
    string ss;
    while (!in.eof())
    {
        line++;
        getline(in, ss);
        cout << line << ":" << ss << endl;
        getToken(ss);
    }
    return 0;
}
