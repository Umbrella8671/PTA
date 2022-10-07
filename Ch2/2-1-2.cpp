#include<iostream>
#define Swap(a, b) a ^= b, b ^= a, a ^= b

using namespace std;
const int MAXSIZE = 1e5;

void LeftShift(int*, int, int);
int main(){
    int n, m;
    int ar[MAXSIZE]{0};
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        cin >> ar[i];
    m %= n;
    LeftShift(ar, n, m);
    for(int i = 0; i < n; i++)
        cout << ar[i] << " ";
    cout << endl;
}
void LeftShift(int* ar, int n, int m){
    if(m > 0 && m < n){
        for(int i = 0, j = n - 1; i < j; i++, j--)
            Swap(ar[i], ar[j]);
        for(int i =  0, j = n - m - 1; i < j; i++, j--)
            Swap(ar[i], ar[j]);
        for(int i = n - m, j = n - 1; i < j; i++, j--)
            Swap(ar[i], ar[j]);
    }
}