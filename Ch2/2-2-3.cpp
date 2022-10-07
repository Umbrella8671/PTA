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


int main(){
    int arr[MAXN]{0};
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    int sum = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            if(j != i)
                sum += (arr[i] * 10 + arr[j]);
        }
    cout << sum << endl;
}
