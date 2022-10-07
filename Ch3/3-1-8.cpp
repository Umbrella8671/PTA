//表達式轉換

#include<iostream>
#include<stack>
#include<string>
#include<cctype>
using namespace std;
int const MAXN = 100;
typedef enum{lpr, rpr, plus, minus, times, divide, eos, operand}Precedence;
bool IsSign(const string &expr, int i);
char GetOp(string &expr, int &i, char *Postfix, int &j);
Precedence GetToken(char op);
void ToPostfix(string &Expr);

int main(){
    string s;
    cin >> s;
    ToPostfix(s);
}

void ToPostfix(string &Expr){
    int i = 0, j = 0, L = 0;
    char Postfix[MAXN * 2];
    char op;
    Precedence Token;
    stack<char>S;
    L = Expr.size();
    for(i = 0; i < L; i++){
        op = GetOp(Expr, i, Postfix, j);
        Token = GetToken(op);
        if(Token == operand) continue;
        switch(Token){
        case lpr: S.push('('); break;
        case rpr:
            while(S.top() != '(')
                Postfix[j++] = S.top(), S.pop();
            Postfix[j++] = ' ';
            S.pop(); break;
        default:
            while(!S.empty() && S.top() != '(' && Token <= GetToken(S.top())){
                Postfix[j++] = S.top(); S.pop();
                Postfix[j++] = ' ';
            }
            S.push(op);
            break;
        }
    }
    while(!S.empty()){
        Postfix[j++] = S.top(), S.pop();
        Postfix[j++] = ' ';
    }
    Postfix[j] = '\0';
    cout << Postfix << endl;
}
bool IsSign(const string &expr, int i){
    if(!i || (!isdigit(expr[i - 1]) && (expr[i - 1] != ')')))
        return true;
    else    return false;
}
char GetOp(string &expr, int &i, char *Postfix, int &j){
    if(isdigit(expr[i])){
        while(isdigit(expr[i]) || expr[i] == '.')
            Postfix[j++] = expr[i++];
        Postfix[j++] = ' ';
        i--;
        return '0';
    }
    switch(expr[i]){
    case '+':
        if(IsSign(expr, i)){
            i++;
            return GetOp(expr, i, Postfix, j);
        }
        else return '+';
    case '-':
        if(IsSign(expr, i)){
            Postfix[j++] = '-';
            i++;
            return GetOp(expr, i, Postfix, j);
        }
        else return '-';
    default:    return expr[i];    
    }
}
Precedence GetToken(char op){
    switch(op){
    case '(': return lpr;
    case ')': return rpr;
    case '+': return Precedence::plus;
    case '-': return Precedence::minus;
    case '*': return times;
    case '/': return divide;
    case '\0': return eos;
    default: return operand;
    }
}
