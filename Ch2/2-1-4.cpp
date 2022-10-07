#include<iostream>
#include<ios>
#include<iomanip>
#include<string>
#include<cstring>
#include<cmath>
#include<stack>
#include<queue>
#include<vector>
using namespace std;
const int MAXN = 1e5;

double fn(double x, int n){
    if(n == 1)
        return x;
    else
        return (x * (1 - fn(x, n - 1)));
}
int main(){
    double x;
    int n;
    cout << fixed << setprecision(2);
    cin >> x >> n;
    cout << fn(x, n) << endl;
}