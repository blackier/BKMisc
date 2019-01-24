#include "intArr.h"
#include <iostream>
using namespace std;

int intarr::number=0;

intarr::intarr()
{
    arr = new int[MAXSIZE]{0};
    size = 0;
}

intarr::intarr(intarr &arr1)
{
    size=arr1.size;
    arr = new int[MAXSIZE];
    for(int i=0;i<size;i++){
        arr[i]=arr1[i];
    }
}

void intarr::cleanArr(){
    size=0;
    arr = new int[MAXSIZE];
}

void intarr::operator &= (int num)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == num)
        {
            return;
        }
    }
    arr[size] = num;
    size++;
    return;
}

void intarr::operator &= (intarr &arr1)
{
    for (int i = 0; i < arr1.getSize(); i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (arr1[i] == arr[j])
            {
                goto l;
            }
        }
        arr[size] = arr1[i];
        size++;
    l:;
    }
}

void intarr::getSort(){
    for(int i=0;i<size-1;i++){
        for(int j=i+1;j<size;j++){
            if(arr[i]>arr[j]){
                int temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
}

int& intarr::operator[](int i)
{
    return arr[i];
}

bool intarr:: operator==( intarr &arr1){
    if(size!=arr1.getSize()){
        return false;
    }
    getSort();
    arr1.getSort();
    for(int i=0;i<size;i++){
        if(arr[i]!=arr1[i]){
            return false;
        }
    }
    return true;
}

bool intarr:: getNum(int num){
    for(int i=0;i<size;i++){
        if(arr[i]==num){
            return true;
        }
    }
    return false;
}

int intarr::getNumber()
{
    return number;
}

void intarr::delNum(int num){
    for(int i=0;i<size; i++){
        if(num==arr[i]){
            arr[i]=arr[size-1];
            arr[size-1]=0;
            size--;
			return;
        }
    }
}
