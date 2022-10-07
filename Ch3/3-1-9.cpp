// 銀行業務隊列簡單模擬

#include<iostream>
#include<queue>
using namespace std;
int main(){
    queue<int>Q1;
    queue<int>Q2;
    int n;
    cin >> n;
    int num;
    for(int i = 0; i < n; i++){
        cin >> num;
        if(num % 2)
            Q1.push(num);
        else
            Q2.push(num);
    }
    if(!Q1.empty()){
        cout << Q1.front();
        Q1.pop();
    }else{
        cout << Q2.front();
        Q2.pop();
    }
    while(!Q1.empty() && !Q2.empty()){
        cout << " " << Q1.front(); Q1.pop();
        cout << " " << Q2.front(); Q2.pop();
        if(!Q1.empty()){
            cout << " " << Q1.front(); Q1.pop();
        }
    }
    while(!Q1.empty())
        cout << " " << Q1.front(), Q1.pop();
    while(!Q2.empty())
        cout << " " << Q2.front(), Q2.pop();
    cout << endl;
}