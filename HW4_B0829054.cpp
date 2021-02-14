#include<iostream>
#include"time.h"
using namespace std;
class node{
    friend class pol;
    public:
        int coef;
        int exp;
        node *next;
};
class pol{
    public:
        pol();
        void add(int coef,int exp);
        void returnpol();
        friend pol operator*(pol &one,pol &two);
    private:
        node *head;
        node *tail;
};
pol::pol(){
    head=new node;
    tail=head;
    head->next=NULL;
}
void pol::returnpol(){
    node *current=head->next;
    if(current->exp==0){
        cout<<current->coef;
    }
    else if(current->exp==1){
        cout<<current->coef<<"x";
    }
    else{
        cout<<current->coef<<"x^"<<current->exp;
    }//第一個
    current=current->next;
    while(current!=NULL){
        if(current->exp==0){
            if(current->coef>=0){
                cout<<"+"<<current->coef;
            }
            else{
                cout<<current->coef;
            }
        }
        else if(current->exp==1){
            if(current->coef>=0){
                cout<<"+"<<current->coef<<"x";
            }
            else{
                cout<<current->coef<<"x";
            }
        }
        else{
            if(current->coef>=0){
                cout<<"+"<<current->coef<<"x^"<<current->exp;
            }
            else{
                cout<<current->coef<<"x^"<<current->exp;
            }
        }
        current=current->next;
    }
}
void pol::add(int coef,int exp){
    node *newnode=new node;
    newnode->coef=coef;
    newnode->exp=exp;
    tail->next=newnode;
    tail=newnode;
    tail->next = NULL;
}
pol operator*(pol &one,pol &two){
    pol mulpol;
    int coef,exp;
    node *current_a=one.head->next;
    while(current_a!=NULL){
        node *current_b=two.head->next;
        while(current_b!=NULL){
            coef=current_a->coef*current_b->coef;
            exp=current_a->exp+current_b->exp;
            //放入新pol
            node *current_mul=mulpol.head->next;
            //讓current_mul尋找是否有次方相同
            while(1){
                if(current_mul!=NULL){
                    if(exp>current_mul->exp){//若exp>current_mul則差一個新節點在前
                        node *find=mulpol.head;
                        while(1){
                            if(find->next==current_mul){
                                node *newnode=new node;
                                newnode->next=current_mul;
                                find->next=newnode;
                                newnode->coef=coef;
                                newnode->exp=exp;
                                break;
                            }
                            else{
                                find=find->next;
                            }
                        }
                        break;
                    }
                    else if(current_mul->exp==exp){
                       current_mul->coef+=coef;
                        break;
                    }
                    else{
                        current_mul=current_mul->next;
                    }
                }
                else{
                    mulpol.add(coef,exp);
                    break;
                }
            }
            current_b=current_b->next;
        }
        current_a=current_a->next;
    }
    return mulpol;
}
int main(){
    int m,n;
    int coef,exp;
    float total;
    pol one,two,three;
    clock_t start,end;
    cin>>m;
    for(int i=0;i<m;i++){
        cin>>coef>>exp;
        if(coef==0){
            continue;
        }
        else{
            one.add(coef,exp);
        }
    }
    one.returnpol();
    cout<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>coef>>exp;
        if(coef==0){
            continue;
        }
        else{
            two.add(coef,exp);
        }
    }
    two.returnpol();
    cout<<endl;
    start=clock();
    three=one*two;
    end=clock();
    total=(float)(end-start)/CLOCKS_PER_SEC;
    three.returnpol();
    cout<<endl<<total;
}