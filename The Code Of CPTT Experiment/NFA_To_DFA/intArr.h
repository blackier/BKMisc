#ifndef _INTARR_H
#define _INTARR_H
#define MAXSIZE 20
#include<cmath>
class intarr
{
public:
    intarr();
    intarr(intarr &arr1);                   //复制构造函数
    int inline getSize(){return size;}      //获取集合大小
    void cleanArr();                        //清空集合元素
    void operator &= (int num);             //重载&=，并入单个元素
    void operator &= (intarr &arr1);        //重载&=，并入一个集合
    void getSort();                         //对集合元素从小到大排序
    int &operator[](int i);                 //重载[]，可以向数组一样获得元素
    bool operator == (intarr &arr1);        //重载==，判断两个集合是否相等
    bool getNum(int num);                   //判断一个数字是否在集合中
    void delNum(int num);                   //删除一个数字
    int getNumber();                        //获得创建对象的个数


private:
    int *arr=NULL;      //数组指针
    int size;           //数组大小
    static int number;  //创建对象的个数
};

#endif // !_INTARR_H
