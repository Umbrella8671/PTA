// 一元多项式求导

#include<iostream>
using namespace std;


typedef struct Node* PtrToNode;
struct Node{
    int Coef;
    int Expon;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;
Polynomial ReadInput(){
    int m;
    Polynomial ply = new Node;
    ply->Next = nullptr;
    PtrToNode p = ply;
    int Coef, Expon;
    while(cin >> Coef >> Expon){
        if(!Coef && !Expon)
            break;
        PtrToNode add = new Node;
        add->Coef = Coef; add->Expon = Expon; add->Next = nullptr;
        p->Next = add;
        p = p->Next;
    }
    return ply;
}

Polynomial Derivation(Polynomial ply){
    PtrToNode p = ply->Next;
    while(p){
        p->Coef = p->Coef * p->Expon;
        p->Expon = p->Expon - 1;
        p = p->Next;
    }
    return ply;
}
void PrintPolynomial(Polynomial ply){
    if(!ply->Next){
        cout << 0 << " " << 0 << endl;
    }
    else{
        int cnt = 0;
        PtrToNode p = ply->Next;
        if(p->Coef){
            cnt++;
            cout << p->Coef << " " << p->Expon;
        }
        p = p->Next;
        while(p){
            if(p->Coef){
                cout << " " << p->Coef << " " << p->Expon;
                cnt++;
            }
            p = p->Next;
        }
        if(!cnt)
            cout << "0 0";
        cout << endl;
    }
}
int main(){
    Polynomial ply = ReadInput();
    Derivation(ply);
    PrintPolynomial(ply);
}
