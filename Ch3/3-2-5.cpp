// 堆栈模拟队列

#include<iostream>
#include<stack>
using namespace std;

unsigned int  n1, n2;
stack<int>s1, s2;
bool isfull(){
    if(s1.size() == n1 && s2.size())
        return true;
    else
        return false;
}
bool isempty(){
    if(s1.size() || s2.size())
        return false;
    else
        return true;
}
void AddQ(int item){
    if(s1.size() == n1){
        while(!s1.empty())
            s2.push(s1.top()), s1.pop();
        s1.push(item);
    }
    else
        s1.push(item);
        
}
int DeleteQ(){
    int digit;
    if(!s2.empty()){
        digit = s2.top(); s2.pop();
        return digit;
    }else{   
        while(!s1.empty())
            s2.push(s1.top()), s1.pop();
        digit = s2.top(), s2.pop();
        return digit;
    }
}
void simulate(int n1, int n2){
    char Oper;
    int digit;
    while(cin >> Oper && Oper != 'T'){
        if(Oper == 'A'){
            cin >> digit;
            if(isfull())
                cout << "ERROR:Full\n";
            else
                AddQ(digit);
        }else if(Oper == 'D'){
            if(isempty())
                cout << "ERROR:Empty\n";
            else
                cout << DeleteQ() << endl;
        }
        
    }
}
int main(){
    cin >> n1 >> n2;
    if(n1 > n2)
        swap(n1, n2);
    simulate(n1, n2);
}












