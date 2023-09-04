#include <iostream>
#include <vector>
using namespace std;

struct computation{
    computation* left;
    computation* right;
    char op;
    float value;
    string variable_name;
    bool isExternal;
    bool isSymbolic;
    computation(float input){
        value = input;
        isExternal = true;
        isSymbolic = false;
    }
    computation(string input){
        variable_name = input;
        isExternal = true;
        isSymbolic = true;
    }
    computation(computation* &a,char inputOP,computation* &b){
        left = a;
        right =b;
        op = inputOP;
        isExternal = false;
    }
    float reduce(){
        while(isSymbolic){
            try{
                string inputf = "0";
                cout<<"input "<<variable_name<<" :\n";
                getline (cin, inputf);
                this->value = stof(inputf);
                isSymbolic = false;
                return value;
            }
            catch(const std::exception& e)
            {
                isSymbolic = true;
            }
        }
        if(isExternal){return value;}
        else{
            float a = left->reduce();
            float b = right->reduce();
            if(op == '+'){
                return a+b;
            }
            if(op == '-'){
                return a-b;
            }
            if(op == '/'){
                return a/b;
            }
            return a*b;
        }
    }
    void print(){
        if(isExternal){
            if(isSymbolic){
                cout<<variable_name;
            }else{
                cout<<value;
            }
        }else{
            printf("(");
            this->left->print();
            printf("%c",this->op);
            this->right->print();
            printf(")");
        }
    }
    void printPostOrder(){
        if(isExternal){
            if(isSymbolic){
                cout<<variable_name;
            }else{
                cout<<value;
            }
        }else{
           
            printf("(");
            this->left->printPostOrder();
            printf(",");
            this->right->printPostOrder();
            printf(")");
            printf("%c",this->op);
        }
    }
    void printPreorder(){
        if(isExternal){
            if(isSymbolic){
                cout<<variable_name;
            }else{
                cout<<value;
            }
        }else{
            printf("%c",this->op);
            printf("(");
            this->left->printPreorder();
            printf(",");
            this->right->printPreorder();
            printf(")");
        }
    }
};

void printVector(vector<int> &v){
    for(auto i: v){
        cout<<i<<" ";
    }
    cout <<"\n";
}
vector <int> getOperatorPositions(string &input){
    vector <int> rv{};
    int s = input.size();
    for(int i = 0; i<s; i++){
        if(input[i]=='+'||input[i]=='-'||input[i]=='*'||input[i]=='/'){
            rv.push_back(i);
        }
    }
    return rv;
}

vector <int> getBracketCountVector(string &input,int startIndex, int endIndex){
    vector <int> rv{};
    int bracketCount = 0;
    int s = input.size();
    for(int i = startIndex; i<= endIndex; i++){
        if(input[i] == '(' || input[i] == '{'){
            bracketCount++;
        }
        if(input[i] == ')' || input[i] == '}'){
            bracketCount--;
        }
        rv.push_back(bracketCount);
    }
    return rv;
}

int getOperatorIndex(string &input,int startindex,int endindex,vector<int> &operatorPositions){
    vector <int> bracketCounts = getBracketCountVector(input,startindex,endindex);
    vector <int> validOpIndexes{};
    for(auto i:operatorPositions){
        if(i >startindex && i<endindex){
            validOpIndexes.push_back(i);
        }
    }
    if(validOpIndexes.size() > 0){
        int opIndexWithMinBracketCount = validOpIndexes[0];
        for(int i = 1; i<validOpIndexes.size(); i++){
            if(bracketCounts[(validOpIndexes[i]-startindex)] < bracketCounts[(opIndexWithMinBracketCount-startindex)]){
                opIndexWithMinBracketCount = validOpIndexes[i];
            }
        }
        return opIndexWithMinBracketCount;
    }else{
        return -1;
    }
}
string stripSpaces(string input){
    vector <char> v{};
    for(auto i:input){
        if(i != ' '){
            v.push_back(i);
        }
    }
    string s(v.begin(),v.end());
    return s;
}
string stripBrackets(string input){
    vector <char> v{};
    for(auto i:input){
        if(i != '(' && i!= ')' && i != '{' && i != '}'){
            v.push_back(i);
        }
    }
    string s(v.begin(),v.end());
    return s;
}
computation* parseExpressionRecursive(string &input, int startIndex, int endIndex,vector<int> &operatorPositions){
    int opIndex = getOperatorIndex(input,startIndex,endIndex,operatorPositions);
    
    if(opIndex == -1){
        string s(input.begin()+startIndex,input.begin()+endIndex+1);
        string s_witoutBrackets = stripBrackets(s);
        try
        {
            float f = stof(s_witoutBrackets);
            computation* r = new computation(f);
            return r;
        }
        catch(const std::exception& e)
        {
            computation* r = new computation(s_witoutBrackets);
            return r;
        }
        
    }else{

        computation* left = parseExpressionRecursive(input,startIndex,opIndex-1,operatorPositions);
        computation* right = parseExpressionRecursive(input,opIndex+1,endIndex,operatorPositions);
        computation* r = new computation(left,input[opIndex],right);
        return r;
    }

}
computation* parseExpression(string &input){
    string s = stripSpaces(input);
    vector<int> opPositions = getOperatorPositions(s);
    computation* rootNode = parseExpressionRecursive(s,0,input.size()-1,opPositions);
    return rootNode;
}
// This code supports symbolic evaluation too 
// for example(25+(a+b+c+(x+y+z)/t)) can be evaluated , programs asks for the input in the console, this works as it is associative
// But the program doesnt know the precedence order between +,-,/,* it shall evaluate sequentially from back . Please use brackets in that case.
int main(){
    system("CLS");
    string inputExpr = "0";
    printf("Input an expression:\n");
    getline (cin, inputExpr);
    computation* c= parseExpression(inputExpr);
    float f = c->reduce();
    cout<<"Evaluated value:"<<f<<"\n";
    return 0;
}
