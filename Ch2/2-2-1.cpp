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
const int MAXN = 1e2;

int main(){
    int ar[MAXN]{0};
    int N;
    cin >> N;
    for(int i = 0; i < N; i++)
        cin >> ar[i];
    int maxn = 0;
    int cnt = 0;
    int sum = 0;
    int cnt_2 = 0;
    for(int i = 0; i < N; i++){
        switch(ar[i] % 3){
        case 0:
            if(ar[i] > maxn)
                maxn = ar[i];
            break;
        case 1:
            cnt++;
            break;
        case 2:
            sum += ar[i];
            cnt_2++;
            break;
        }
    }
    double average = (double)sum / cnt_2; 
    if(maxn)
        cout << maxn << " ";
    else    
        cout << "NONE ";
    if(cnt)
        cout << cnt << " ";
    else
        cout << "NONE ";
    if(sum)
        cout << fixed << setprecision(1) << average << endl;
    else
        cout << "NONE\n";    
}