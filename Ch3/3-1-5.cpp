// 符号匹配

#include<iostream>
#include<stack>
using namespace std;
const int MAXN = 100;

enum Token{ret, lc, lbrc, lbrkt, lpr, rc, rbrc, rbrkt, rpr, others};

/*-------------堆栈的定义------------*/
typedef Token ElementType;
struct SNode{
    ElementType *Data;
    int top;
    int MaxSize;
};
typedef SNode* Stack;

Stack CreateStack(int MaxSize);
bool IsEmpty(Stack S);
void Push(Stack S, ElementType x);
ElementType Peek(Stack S);
void Pop(Stack S);
/*-----------堆栈的定义结束----------*/

bool IsEnd(int newline, char &c);
Token GetToken(char c);
bool IsPaired(Token t1, Token t2);
void PrintS(Token t);
int Check(Token &T1, Token &T2);


int main(){
    Token T1, T2;
    int error = Check(T1, T2);
    if(!error)
        cout << "YES\n";
    else{
        cout << "NO\n";
        switch(error){
        case 1: cout << "?-"; PrintS(T1); break;
        case 2: PrintS(T2); cout << "-?"; break;
        default: break;
        }
    }
}

Stack CreateStack(int MaxSize){
    Stack S = new SNode[MaxSize];
    S->Data = new ElementType[MaxSize];
    S->top = -1;
    S->MaxSize = MaxSize;
    return S;
}
bool IsEmpty(Stack S){
    return S->top == -1;
}
void Push(Stack S, ElementType x){
    S->Data[++(S->top)] = x;
}
ElementType Peek(Stack S){
    return S->Data[S->top];
}
void Pop(Stack S){
    S->top--;
}
int Check(Token &T1, Token &T2){
    Stack S = CreateStack(MAXN);
    int newline = 1, error = 0;
    Token t;
    char c;
    while(1){
        scanf("%c", &c);
        if(IsEnd(newline, c)) break;
        else{
            switch(t = GetToken(c)){
            case lc:
            case lbrc:
            case lbrkt:
            case lpr: Push(S, t); newline = 0; break;
            case rc:
            case rbrc:
            case rbrkt:
            case rpr:
                // 右半边不匹配
                if(IsEmpty(S)) error = 1;
                // 左半边不匹配
                else if(!IsPaired(t, Peek(S))) error = 2;
                else Pop(S); // 消去一对
                newline = 0; break;
            case ret: newline = 1; break;        
            default: newline = 0; break;
            }
        }
        if(error)
            break;
    }
    if(!error && !IsEmpty(S)) error = 2;
    T1 = t; T2 = Peek(S);
    return error;
}
bool IsEnd(int newline, char &c){
    if(newline && c == '.'){
        scanf("%c", &c);
        if(c == '\n')
            return true;
        else
            return false;
    }else
        return false;
}

Token GetToken(char c){
    switch (c){
    case '\n': return ret;
    case '{':  return lbrc;
    case '[':  return lbrkt;
    case '(':  return lpr;
    case '/':
        scanf("%c", &c);
        if(c == '*')
            return lc;
        else    
            return GetToken(c);
    case '}':  return rbrc;
    case ']':  return rbrkt;
    case ')':  return rpr;
    case '*':
        scanf("%c", &c);
        if(c == '/')
            return rc;
        else
            return GetToken(c);
    default:   return others;
    }
}

bool IsPaired(Token t1, Token t2){
    return (t1 - t2) == 4;
}

void PrintS(Token t){
    switch(t){
    case lc: cout << "/*"; break;
    case lbrc: cout << "{"; break;
    case lbrkt: cout << "["; break;
    case lpr: cout << "("; break;
    case rc: cout << "*/"; break;
    case rbrc: cout << "}"; break;
    case rbrkt: cout << "]"; break;
    case rpr: cout << ")"; break;
    default: break;
    }
}









