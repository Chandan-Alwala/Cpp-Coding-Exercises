#include <bits/stdc++.h>
using namespace std;

class textEditor{
    private:
    int cursor = -1;
    vector<char> charSequence{};
    public:
    void insert(char a){
        if(this->cursor == charSequence.size()-1){
            charSequence.push_back(a);   
        }else{
            charSequence.push_back(a);
            int s= charSequence.size();
            for(int i = s-2 ; i>cursor; i--){
                charSequence[i+1] = charSequence[i];
            }
            charSequence[cursor+1]=a;
        }
         this->right();
    }
    public:
    void deleteChar(){
        if(this->cursor == charSequence.size()-1){
            charSequence.pop_back();
            
        }else{
            int s= charSequence.size();
            for(int i = cursor+1 ; i<s-1; i++){
                charSequence[i] = charSequence[i+1];
            }
            charSequence.pop_back();
        }
        if(this->cursor == charSequence.size()){
            this->left();
        }
    }
    public:
    void left(){
        int a = this->cursor;
        a--;
        if(a >-2){
            this->cursor = a;
        }
    }
    public:
    void right(){
        int a = this->cursor;
        a++;
        if(a <charSequence.size()){
            this->cursor = a;
        }
    }
    public:
    int getCursor(){
        int a = this->cursor;
        return a;
    }
    int end(){
        int a = this->charSequence.size()-1;
        return a;
    }
    int start(){
        return -1;
    }
    public:
    void print(){
        int s = this->charSequence.size();
        for(int i =0; i<s;i++){
            printf("%c",this->charSequence[i]);
        }
        printf("\n");
    }
};

void demo(){
    textEditor T;
    T.insert('a');
    T.insert('v');
    T.insert('n');
    T.insert('a');
    T.insert('s');
    T.insert('h');
    T.print();
    T.left();
    T.left();
    T.left();
    T.left();
    T.insert('I');
    T.print();
    T.left();
    T.deleteChar();
    T.insert('i');
    T.print();
    while(T.getCursor() != T.end()){
        T.right();
    }
    T.insert(' ');
    T.insert('!');
    T.print();
}
int main(){
    demo();
    return 0;
}