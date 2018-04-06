/*
实验九
一、实验目的
学习和掌握LL（1）文法的判定和LL（1）分析方法。

二、实验任务
（1）存储文法的LL（1）分析表；
（2）根据LL（1）分析表判断文法是否LL（1）文法；
（3）实现LL（1）分析过程。

三、实验内容
（1）确定LL（1）分析表的文件存储格式。
要求为3个以上测试文法准备好相应LL（1）分析表的存储文件。
（2）根据LL（1）分析表判断文法是否LL（1）文法。
看每个表项是否最多只有一条候选式，如是该文法是LL（1）文法。
（3）实现LL（1）分析过程。
当（2）判断出该文法是LL（1）文法时，要求给出3个以上输入串的LL（1）分析过程，并判断输入串是否该文法的合法句子。


实验十
一、实验目的
学习和掌握FIRST集合、FOLLOW集合的计算，LL（1）分析表的构造方法。

二、实验任务
（1）存储文法；
（2）计算给定文法所有非终结符的FIRST集合；
（3）计算给定文法所有非终结符的FOLLOW集合；
（4）构造该文法的LL（1）文法的分析表并按实验九的文法格式存储；
（5）结合实验九，完成完整的LL（1）分析过程。

三、实验内容
（1）确定文法的文件存储格式，存储文法的非终结符集合、开始符号、终结符集合和产生式规则集合。
要求为3个以上测试文法准备好相应的存储文件。
（2）计算给定文法所有非终结符的FIRST集合。
（3）计算给定文法所有非终结符的FOLLOW集合；
（4）构造该文法的LL（1）文法的分析表并按实验九的文法格式存储；
（5）结合实验九，完成完整的LL（1）分析过程。

*/


#include"getFirFol.h"
#include"LL.h"
#include<iostream>
#include<string>
#include<queue>
#include<fstream>
using namespace std;

int main(){
    string ts="test1\\terminalSymbol.ll";
    string nts="test1\\nonTerminalSymbol.ll";
    string rl = "test1\\rule.ll";
    string path="test1\\input1.ll";
    getFirst_Follow gff(ts,nts,rl);
    gff.getFirst();
    gff.getFollow();
    LL ll(&gff,ts,nts,rl);
    ll.fillInTheTable();
    ll.analyzeChars(path);
    system("pause");
    return 0;
}