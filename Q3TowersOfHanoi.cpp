#include <bits/stdc++.h>
using namespace std;

void solveTowersOfHanoi(int n,char &source,char& target,char &other,int &stepNumber){
    if(n == 1){
        stepNumber++;
        printf("step %d: %c -> %c \n",stepNumber,source,target);
    }else{
        solveTowersOfHanoi(n-1,source,other,target,stepNumber);
        stepNumber++;
        printf("step %d: %c -> %c \n",stepNumber,source,target);
        solveTowersOfHanoi(n-1,other,target,source,stepNumber);
    }
}

int main (){
    char A = 'a';
    char B = 'b';
    char C = 'c';
    int step = 0;
    solveTowersOfHanoi(5,A,C,B,step);
    return 0;
}