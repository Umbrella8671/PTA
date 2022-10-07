// 前缀表达式求值

#include<iostream> 
#include<stack>
#include<cstring>
#include<cctype>
#include<cmath>
#include<string>
using namespace std;
const int MAXN = 1e3;



int main(){
    string expr;
    getline(cin, expr);
    stack<double>sd;
    double ans = 0.0;
    double num = 0;
    for(int i = expr.size() - 1; i >= 0; i--){
        if(isdigit(expr[i])){
            num = expr[i] - '0';
            int ex = 10;
            for(--i; i >=0; --i){
                if(isdigit(expr[i]) || expr[i] == '.'){
                    if(isdigit(expr[i])){
                        num += (expr[i] - '0') * ex;
                        ex *= 10;
                    }else{
                        num /= ex;
                        ex = 1;
                    }
                }else if(expr[i] == '-')
                    num = -num;
                else
                    break;
            }
            sd.push(num);
        }
        else if(expr[i] == ' ')
            continue;
        else{
            double x = sd.top(); sd.pop();
            double y = sd.top(); sd.pop();
            switch(expr[i]){
            case '+': ans = x + y; break;
            case '-': ans = x - y; break;
            case '*': ans = x * y; break;
            case '/': 
                if(y == 0){
                    cout << "ERROR\n";
                    return 0;
                }
                else
                    ans = x / y; 
            }
            sd.push(ans);
        } 
    }
    cout.setf(ios_base::fixed);
    cout.precision(1);
    cout << sd.top() << endl;
}