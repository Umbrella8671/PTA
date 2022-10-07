// 多项式乘法

#include<iostream>
using namespace std;


typedef struct Node* PtrToNode;
struct Node{
    int Coef;
    int Expon;
    PtrToNode Next;
};
typedef PtrToNode Polynomial;

void Insert(Polynomial& ply, PtrToNode &add){
    if(!ply->Next)
        ply->Next = add;
    else{
        PtrToNode p = ply->Next, pre = ply;
        while(p){
            if(p->Expon == add->Expon){
                p->Coef = p->Coef + add->Coef;
                if(!p->Coef){
                    PtrToNode temp = p;
                    pre->Next = p->Next;
                    delete temp;
                }
                return;
            }
            else if(p->Expon > add->Expon){
                pre = p;
                p = p->Next;
            }
            else
                break;
        }
        if(!p)
            pre->Next = add;
        else{
            add->Next = pre->Next;
            pre->Next = add;
        }
    }
}

Polynomial MultiPly(Polynomial ply1, Polynomial ply2){
    PtrToNode p1 = ply1->Next, p2 = ply2->Next;
    Polynomial ply = new Node;
    ply->Next = nullptr;
    ply->Coef = 0;
    ply->Expon = 0;
    PtrToNode p3 = ply;
    int Coef = 0, Expon = 0;
    while(p1){
        while(p2){
            Coef = p1->Coef * p2->Coef;
            Expon = p1->Expon + p2->Expon;
            p2 = p2->Next;
            PtrToNode add = new Node;
            add->Coef = Coef; add->Expon = Expon; add->Next = nullptr;
            Insert(ply, add);
        }
        p2 = ply2->Next;
        p1 = p1->Next;
    }
    return ply;
}

Polynomial ReadInput(){
    int m;
    cin >> m;
    Polynomial ply = new Node;
    ply->Next = nullptr;
    PtrToNode p = ply;
    while(m--){
        int Coef, Expon;
        cin >> Coef >> Expon;
        PtrToNode add = new Node;
        add->Coef = Coef; add->Expon = Expon; add->Next = nullptr;
        p->Next = add;
        p = p->Next;
    }
    return ply;
}
void PrintPolynomial(Polynomial ply){
    if(!ply->Next){
        cout << 0 << " " << 0 << endl;
    }
    else{
        PtrToNode p = ply->Next;
        cout << p->Coef << " " << p->Expon;
        p = p->Next;
        while(p){
            cout << " " << p->Coef << " " << p->Expon;
            p = p->Next;
        }
        cout << endl;
    }
}

int main(){
    Polynomial ply1 = ReadInput();
    Polynomial ply2 = ReadInput();
    Polynomial ply = MultiPly(ply1, ply2);
    PrintPolynomial(ply);
}