#include<iostream>
#include<ios>
#include<iomanip>
#include<string>
#include<cstring>
#include<cmath>
#include<stack>
#include<queue>
#include<vector>
#include<climits>
#include<cctype>
using namespace std;
const int MAXN = 1e5;

void Permutation_Wrg(int L[], int Left, int Right);
void Permutation(int L[], int Left, int Right);


int main(){
    int n;
    cin >> n;
    int ar[10];
    for(int i = 0; i < n; i++)
        ar[i] = i + 1;
    //Permutation_Wrg(ar, 0, n - 1);
    Permutation(ar, 0, n - 1);
}

void RightShift(int L[], int Left, int i){
    int guard = L[i];
    for(int j = i; j > Left; j--)
        L[j] = L[j - 1];
    L[Left] = guard;
}
void LeftShift(int L[], int Left, int i){
    int guard = L[Left];
    for(int j = Left; j < i; j++)
        L[j] = L[j + 1];
    L[i] = guard;
}
void Permutation(int L[], int Left, int Right){
    if(Left == Right){
        for(int i = 0; i <= Right; i++)
            cout << L[i] << " ";
        cout << endl;
    }else
        for(int i = Left; i <= Right; i++){
            RightShift(L, Left, i);
            Permutation(L, Left + 1, Right);
            LeftShift(L, Left, i);
        }
}


void Swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp; 
}

void Permutation_Wrg(int L[], int Left, int Right){
    if(Left == Right){
        for(int i = 0; i <= Right; i++)
            cout << L[i] << " ";
        cout << endl;
    }else
        for(int i = Left; i <= Right; i++){
            Swap(L[Left], L[i]);
            Permutation_Wrg(L, Left + 1, Right);
            Swap(L[i], L[Left]);
        }
}