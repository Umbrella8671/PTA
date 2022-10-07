// 出栈顺序合法性

#include<iostream>
#include<stack>
using namespace std;


const int MAXN = 1e3;

bool IsRight(int *ar, int m, int n){
    stack<int>s;
    int j = 0;
    int Size = 0;
    for(int i = 1; i <= n; i++){
        if(Size < m)
            Size++, s.push(i);
        else
            return false;
        while(!s.empty() && s.top() == ar[j])
            j++, Size--, s.pop();
    }
    if(s.empty())
        return true;
    else
        return false;
}
int main(){
    int m, n, k;
    cin >> m >> n >> k;
    int ar[MAXN]{0};
    while(k--){
        for(int i = 0; i < n; i++)
            cin >> ar[i];
        if(IsRight(ar, m, n))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}

// #include<iostream>
// using namespace std;
// const int MAXN = 1e3;
// int main(){
//     int m, n, k;
//     cin >> m >> n >> k;
//     int ar[MAXN]{0};
//     bool flag = false;
//     while(k--){
//         for(int i = 0; i < n; i++)
//             cin >> ar[i];
//         for(int i = 1; i < n; i++)
//             if(ar[i] - ar[i - 1] <= m)
//                 flag = true;
//             else{
//                 flag = false;
//                 break;
//             }
        
//     }
//     if(flag)
//         cout << "YES\n";
//     else
//         cout << "NO\n";
// }