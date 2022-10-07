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
const int MAXN = 10000;
bool Is_Prime[MAXN];

int num;
void Search(int Remainder){
    int i = 0, p = 0, k = 0;
    for(i = 2; i * i <= num; i++){
        while(Remainder % i == 0){
            p = i;
            k++;
            Remainder /= i;
        }
        if(p)
            break;;
    } 
    if(p){
        if(Remainder != 1){
            if(k != 1)
                cout << p << "^" << k << "*";
            else
                cout << p << "*";
            Search(Remainder);
        }
        else{
            if(k != 1)
                cout << p << "^" << k;
            else
                cout << p;
        }
    }
    else
        cout << Remainder;
    
}

int main(){
    long N;
    cin >> N;
    cout << N << "=";
    num = N;
    Search(N);
    cout << endl;
}