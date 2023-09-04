#include <bits/stdc++.h>
using namespace std;

struct node
{
    int data;
    node* previous;
    node* next;
    node(int d){
        data = d;
        previous = this;
        next = this;
    }
};

class CircularList{
    private:
    node* cursor;
    int size;

    public:
    CircularList(){
        this->cursor = nullptr;
        this->size = 0;
    }
    void moveFront(){
        if(size != 0){
            this->cursor = this->cursor->next;
        }  
    }
    void moveBack(){
        if(size != 0){
            this->cursor = this->cursor->previous;
        }
    }
    int getSize(){
        return this->size;
    }
    void insert(int d){
        node* n = new node(d);
        if(this->size == 0){
            this->cursor = n;
        }else{
            n->next = this->cursor->next;
            n->previous = this->cursor;
            this->cursor->next->previous = n;
            this->cursor->next = n;
        }
        size++;
        this->moveFront();

    }
    void remove(){
        if(this->size > 0){
            node* n =  this->cursor;
            if(size == 1){
                this->cursor = nullptr;           
            }else{
                n->previous->next =  n->next;
                n->next->previous = n->previous;
                this->cursor = n->previous;
            }
            size--;
            free(n);
        }    
    }
    int getCursor(){
        int r = this->cursor->data;
        return r;
    }
    void print(){
        for(int i = 0; i<this->size; i++){
            printf("%d->",this->getCursor());
            this->moveFront();
        }
        printf("\n");
    }
    bool equals(CircularList &c2){
        if(this->getSize() != c2.getSize()){
            return false;
        }
        node* initialCursor = this->cursor;
        for(int i = 0; i< this->size;i++){
            int equal_count = 0;
            for(int j = 0;j<this->size;j++){
                if(this->getCursor() == c2.getCursor()){
                    equal_count++;
                    this->moveFront();
                    c2.moveFront();
                }else{
                    this->cursor = initialCursor;
                    while(equal_count--){c2.moveBack();}
                    break;
                }
            }
            if(equal_count == this->size){return true;}
            c2.moveFront(); 
        }
        return false;
    }
};

void demo(){
    CircularList C1;
    C1.insert(1);
    C1.insert(2);
    C1.insert(3);
    C1.insert(4);
    C1.insert(5);
    C1.insert(6);

    CircularList C2;
    C2.insert(5);
    C2.insert(6);
    C2.insert(1);
    C2.insert(2);
    C2.insert(3);
    C2.insert(4);

    if(C1.equals(C2)){
        printf("equal\n");
    }else{
        printf("not equal\n");
    }
    C1.print();
    C2.print();
}

int main(){
    demo();
    return 0;
}