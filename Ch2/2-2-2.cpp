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
    int ar[MAXN]{0};
    int N;
    double sum = 0;
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> ar[i];
        sum += ar[i];
    }
    double Dx;
    double Avg = sum / N;
    sum = 0;
    for(int i = 0; i < N; i++)
        sum += pow(ar[i] - Avg, 2.0);
    Avg = sum / N;
    cout << showpoint << setprecision(6) << sqrt(Avg) << endl;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
    int n, i, a[10000];
    double avg, sum = 0;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    avg = sum / n;
    sum = 0;
    for (i = 0; i < n; i++)
    {
        sum += pow(a[i] - avg, 2.0);
    }
    avg = sum / n;
    printf("%.5lf", sqrt(avg));
    return 0;
}
