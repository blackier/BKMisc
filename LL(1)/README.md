### 仿tiny词法分析

- 文件说明

```txt
test*                       输入文件夹
    input*.ll               字符串分析输入
    terminalSymbol.ll       终结符号
    nonTerminmalSymbol.ll   非终结符号
    rule.ll                 文法
struct.h                    符号、文法存储格式
getFirFol.h getFirFol.cpp   获得first和follow集
LL.h LL.cpp                 LL(1)分析
main.cpp                    主函数
```

代码内容为LL(1)分析的编程实现，具体细节见[LL(1)](https://blog.csdn.net/qq_34194662/article/details/79832758)。