#include<iostream>
#include<string>
#include<cstring>
#include<cmath>
#include<stack>
#include<queue>
#include<vector>
using namespace std;
const int MAXN = 1e5;

void Sum(int *S, int *K, int A, int N);
void Sum(int *S, int A, int N);
int main(){
    int A, N;
    cin >> A >> N;
    int S[MAXN]{0}, K[MAXN]{0};
    Sum(S, A, N);
    if(S[N])
        cout << S[N];
    for(int i = N - 1; i >= 0; i--)
            cout << S[i];
}

void Sum(int *S, int *K, int A, int N){
    if(!N){
        cout << "0\n";
        return;
    }
    int C, i, j;
    for(i = 0; i < N; i++)
        K[i] = A;
    C = 0;
    for(i = 0; i < N; i++){
        for(j = 0; j <= i; j++){
            S[j] += (K[j] + C);
            C = S[j] / 10;
            S[j] %= 10;
        }
    }
    if(C)
        S[N] = C;
}

void Sum(int *S, int A, int N){
    if(!N){
        cout << "0\n";
        return;
    }
    int C, i, j;
    C = 0;
    for(i = 0; i < N; i++){
        S[i] += (((N - i) * A) + C);
        C = S[i] / 10;
        S[i] %= 10;
    }
    if(C)
        S[N] = C;
}