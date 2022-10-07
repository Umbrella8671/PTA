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
const int MAXN = 1e2;


void allocation(int ans[], int Pnum, int D, int P){
    int Count = Pnum / 2;
    int max = 0;
    bool Hashmap[MAXN]{false};
    int index = P - Pnum;
    ans[index] = D;
    while(Count){
        for(int i = index + 1; i < P; i++){
            if(ans[i] == max){
                if(!Hashmap[i]){
                    ans[i]++;
                    Count--;
                    Hashmap[i] = true;
                }
            }
            if(!Count)
                break;
        }
        max++;
    }
    for(int i = index + 1; i < P; i++)
        if(Hashmap[i])
            ans[index] -= ans[i];
        else
            ans[i] = 0;
}
int main(){
    int ans[MAXN]{0};
    int D, P;
    cin >> D >> P;
    ans[P - 1] = D;
    ans[P - 2] = 0;
    for(int i = 2; i <= P - 1; i++)
        allocation(ans, i + 1, D, P);
    cout << ans[0] << "\n";
}
