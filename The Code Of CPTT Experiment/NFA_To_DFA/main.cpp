#include "NFA_To_DFA.h"
#include "minimalDFA.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n=0;
    cin>>n;
    if(n==1){
        nfa_to_dfa nd("nd.nfa");
        minDfa dfa("dfa.dfa");
    }
    else if(n==2){
        nfa_to_dfa nd("nd2.nfa");
        minDfa dfa("dfa2.dfa");
    }
    else if(n==3){
        nfa_to_dfa nd("nd3.nfa");
        minDfa dfa("dfa3.dfa");
    }
    else{
        cout<<"input a error num"<<endl;
    }

    return 0;
}