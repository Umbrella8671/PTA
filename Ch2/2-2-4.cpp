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
    int box[MAXN];
    int number[MAXN]{0};
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        box[i] = 100;
    }
    int sum = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            if(box[j] >= arr[i]){
                box[j] -= arr[i];
                number[i] = j + 1;
                break;
            }
        }
    for(int i = 0; i < n; i++)
        if(box[i] != 100)
            sum++;
    for(int i = 0; i < n; i++)
        cout << arr[i] << " " << number[i] << endl;
    cout << sum << endl;
}
