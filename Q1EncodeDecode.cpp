#include <bits/stdc++.h>
using namespace std;

class Cipher{

    private:
    vector<int> Encoder{};

    private:
    bool verifyInputEncoder(vector <int> &input){
        int s = input.size();
        int b[s];
        for(int i = 0; i< s; i++){
            if(input[i] <0 || input[i] >(s-1)){return false;}
            b[i] = 0;
        }
        for(int i = 0; i< s; i++){
            b[input[i]]++;
            if(b[input[i]] > 2){return false;}
        }
         for(int i = 0; i< s; i++){
            if(b[i] != 1){return false;}
        }
        return true;
    }
    private:
    vector<int> getTailEncoder(int tailSize){
        int EncoderSize = this->Encoder.size();
        vector<int> tailEncoder{};
        for(int i = 0; i< EncoderSize;i++){
            if( this->Encoder[i]< tailSize){
                tailEncoder.push_back(this->Encoder[i]);
            }
        }
        return tailEncoder;
    }


    public:
    void setEncoder(vector <int> &input){
        if(this->verifyInputEncoder(input)){
            this -> Encoder = input;
        }else{
            throw " Invalid input encoder";
        }
    }
    vector<char> encode(vector<char> &v){
        int EncoderSize = this->Encoder.size();
        if(EncoderSize == 0 || EncoderSize == 1){return v;}
        char temp[EncoderSize];
        int streamSize = v.size();
        int tailSize = streamSize - EncoderSize*(streamSize/EncoderSize);
        for(int i = 0 ; i< (streamSize-tailSize) ; i += EncoderSize){
            //encode
            for(int j = 0; j < EncoderSize; j++){
                temp[j] = v[i+Encoder[j]];
            }
            //copy back;
            for(int j = 0; j < EncoderSize; j++){
                v[i+j] = temp[j];
            }
        }
        //encode tail
        vector<int> tailEncoder = this->getTailEncoder(tailSize);
        int offset = streamSize-tailSize;
        for(int i = 0; i< tailSize ; i ++){
            //(streamSize-tailSize) 
            temp[i] = v[offset+tailEncoder[i]];
        }
        //copy back;
        for(int i = 0; i< tailSize ; i ++){
            v[offset+i] = temp[i];
        }
        return v;
    }
    public:
    vector<char> decode(vector<char> &v){
        int EncoderSize = this->Encoder.size();
        if(EncoderSize == 0 || EncoderSize == 1){return v;}
        char temp[EncoderSize];
        int streamSize = v.size();
        int tailSize = streamSize - EncoderSize*(streamSize/EncoderSize);
        for(int i = 0 ; i< (streamSize-tailSize) ; i += EncoderSize){
            //decode
            for(int j = 0; j < EncoderSize; j++){
                temp[Encoder[j]] = v[i+j];
            }
            //copy back;
            for(int j = 0; j < EncoderSize; j++){
                v[i+j] = temp[j];
            }
        }
        //decode tail
        vector<int> tailEncoder = this->getTailEncoder(tailSize);
        int offset = streamSize-tailSize;
        for(int i = 0; i< tailSize ; i ++){
            //(streamSize-tailSize) 
            temp[tailEncoder[i]] = v[offset+i];
        }
        //copy back;
        for(int i = 0; i< tailSize ; i ++){
            v[offset+i] = temp[i];
        }
        return v;
    }

};


void demo(string input){
    Cipher X;
    vector <int> Encoder{9,8,5,4,7,6,3,2,1,0,12,10,11,17,14,15,16,13};
    X.setEncoder(Encoder);
    vector<char> char_v(input.begin(), input.end());
    X.encode(char_v);
    string encode_str(char_v.begin(), char_v.end());
    cout<<" Encoded String  :" << encode_str <<"\n";
    X.decode(char_v);
    string decoded_str(char_v.begin(), char_v.end());
    cout <<" Decoded String  :"<< decoded_str <<"\n";
}

int main(){
    demo("I like this assignment. I'm not very sure if my implementation is the most optimized. But it just works!");
    return 0;
}