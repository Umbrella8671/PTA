#include <iostream>
using namespace std;
const int MAXN = 4;
double operation(double x, double y, char op)
{
    switch(op){
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '*':
        return x * y;
    default:
        if(y)
            return (double)x / y;
        return 0;
    }
}

//((s1 op1 s2) op2 s3) op3 s4
double model1(int s[], char op1, char op2, char op3){
    double x = operation(s[0], s[1], op1);
    double y = operation(x, s[2], op2);
    return operation(y, s[3], op3);
}

//(s1 op1 s2) op2 (s3 op3 s4)
double model2(int s[], char op1, char op2, char op3){
    double x = operation(s[0], s[1], op1);
    double y = operation(s[2], s[3], op3);
    return operation(x, y, op2);
}

//(s1 op1 (s2 op2 s3)) op3 s4
double model3(int s[], char op1, char op2, char op3){
    double x = operation(s[1], s[2], op2);
    double y = operation(s[0], x, op1);
    return operation(y, s[3], op3);
}

//s1 op1 ((s2 op2 s3) op3 s4)
double model4(int s[], char op1, char op2, char op3){
    double x = operation(s[1], s[2], op2);
    double y = operation(x, s[3], op3);
    return operation(s[0], y, op1);
}

// s1 op1 (s2 op2 (s3 op3 s4))
double model5(int s[], char op1, char op2, char op3){
    double x = operation(s[2], s[3], op3);
    double y = operation(s[1], x, op2);
    return operation(s[0], y, op3);
}

bool Cal(int s[], char op[]){
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            for(int k = 0; k < 4; k++)
                if(model1(s, op[i], op[j], op[k]) == 24){
                    cout << "((" << s[0] << op[i] << s[1] << ")" << op[j] << s[2] << ")" << op[k] << s[3] << endl;
                    return true;
                }
                else if(model2(s, op[i], op[j], op[k]) == 24){
                    cout << "(" << s[0] << op[i] << s[1] << ")" << op[j] << "(" << s[2] << op[k] << s[3] << ")" << endl;
                    return true;
                }
                else if(model3(s, op[i], op[j], op[k]) == 24){
                    cout << "(" << s[0] << op[i] << "(" << s[1] << op[j] << s[2] << ")" << ")" << op[k] << s[3] << endl;
                    return true;
                }
                else if(model4(s, op[i], op[j], op[k]) == 24){
                    cout << s[0] << op[i] << "((" << s[1] << op[j] << s[2] << ")" << op[k] << s[3] << ")" << endl;
                    return true;
                }
                else if(model5(s, op[i], op[j], op[k]) == 24){
                    cout << s[0] << op[i] << "(" << s[1] << op[j] << "(" << s[2] << op[k] << s[3] << "))" << endl; 
                    return true;
                }
    return false;
}

void solve(int* data, char *op){
    int s[MAXN]{0};
    bool ret = false;
    for(int i = 0; i < MAXN; i++){
        for(int j = 0; j < MAXN; j++){
            if(j == i)
                continue;
            for(int k = 0; k < MAXN; k++){
                if(k == i || k == j)
                    continue;
                for(int l = 0; l < MAXN; l++){
                    if(l == i || l == j || l == k)
                        continue;
                    s[0] = data[i]; s[1] = data[j];
                    s[2] = data[k]; s[3] = data[l];
                    ret = Cal(s, op);
                    if(ret)
                        break;
                }
                if(ret)
                    break;
            }
            if(ret)
                break;
        }
        if(ret)
            break;
    }   
    if(!ret)
        cout << "-1\n";      
}
int main(){
    int data[MAXN]{0};
    char op[]{'+', '-', '*', '/'};
    for(int i = 0; i < MAXN; i++)
        cin >> data[i];
    solve(data, op);    
}