// 漢諾塔非遞歸實現

#include<iostream>
#include<stack>
using namespace std;

struct Block{
    int n;
    char a, b, c;
    Block(int n1, char a1, char b1, char c1)
        : n(n1), a(a1), b(b1), c(c1){}
};
void Hanoi(int n);

int main(){
    int n;
    cin >> n;
    Hanoi(n);
}

void Hanoi(int n){
    stack<Block>S;
    Block Elem(n, 'a', 'b', 'c');
    S.push(Elem);
    while(!S.empty()){
        Elem = S.top(); S.pop();
        if(Elem.n == 1)
            cout << Elem.a << "->" << Elem.c << endl;
        else{
            S.push(Block(Elem.n - 1, Elem.b, Elem.a, Elem.c));
            S.push(Block(1, Elem.a, Elem.b, Elem.c));
            S.push(Block(Elem.n - 1, Elem.a, Elem.c, Elem.b));
        }
    }
}