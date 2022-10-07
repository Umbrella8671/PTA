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
#include<algorithm>
using namespace std;
const int MAXN = 1e4;

int Term[MAXN]{0};
int Count = 0;
int n = 0;
void Search(int Remainder, int Start, int nTerm){
    if(!Remainder){
        Count++;
        if(Count % 4 != 1)
            cout << ";";
        cout << n << "="; 
        for(int i = 0; i < nTerm - 1; i++)
            cout << Term[i] << "+";
        cout << Term[nTerm - 1];
        if(Count % 4 == 0){
            cout << "\n";
            Count = 0;
        }
    }
    for(int i = Start; i <= Remainder; i++){
        Term[nTerm] = i;
        Search(Remainder - i, i, nTerm + 1);
    }
}

int main(){
    cin >> n;
    Search(n, 1, 0);
}