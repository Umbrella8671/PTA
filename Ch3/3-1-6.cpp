//案例3-1.6 堆棧操作合法性

#include<iostream>
#include<string>
using namespace std;
int main(){
    int n, m;
    int Scount = 0;
    cin >> n >> m;
    string Oper;
    while(n--){
        Scount = 0;
        cin >> Oper;
        for(int i = 0; i < Oper.size(); i++){
            if(Oper[i] == 'S')    
                if(Scount < m)
                    Scount++;
                else
                    break;
            else    
                if(Scount > 0)
                    Scount--;
                else{
                    Scount--;
                    break;
                }

        }
        if(!Scount)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}