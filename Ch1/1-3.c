#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXSIZE 100000

int function1(int *arr1, int *arr2, int n){
    int i = 0, j = 0, k = 0;
    int ans;
    for(k = 0; k <= n - 2; k++)
        if(arr1[i] <= arr2[j])
            i++;
        else
            j++;
    ans = arr1[i] <= arr2[j] ? arr1[i] : arr2[j];
    return ans;
}

int function2(int *arr1, int *arr2, int n){
    int low1 = 0, high1 = n - 1, mid1;
    int low2 = 0, high2 = n - 1, mid2;

    while(low1 < high1 && low2 < high2){
        mid1 = (low1+high1) / 2;
        mid2 = (low2+high2) / 2;
        if(arr1[mid1] == arr2[mid2])
            return arr1[mid1];
        if(arr1[mid1] < arr2[mid2]){
            if((low1 + high1) % 2 == 0){
                low1 = mid1;
                high2 = mid2;
            }
            else{
                low1 = mid1 + 1;
                high2 = mid2;
            }
        }
        else{
            if((low2 + high2) % 2 == 0){
                high1 = mid1;
                low2 = mid2;
            }
            else{
                low2 = mid2 + 1;
                high1 = mid1;
            }
        }
    }
    mid1 = low1, mid2 = low2;
    return arr1[mid1] < arr2[mid2] ? arr1[mid1] : arr2[mid2];
}

int main(){
    int n;
    int arr1[MAXSIZE];
    int arr2[MAXSIZE];
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &arr1[i]);
    for(int i = 0; i < n; i++)
        scanf("%d", &arr2[i]);
    printf("%d\n", function2(arr1, arr2, n));
}


int searchMid(int a[],int b[],int n) {
    int low1 = 0, low2 = 0, high1 = n - 1, high2 = n - 1;
    while (low1 < high1&&low2 < high2) {
        int mid1 = (low1 + high1) / 2;
        int mid2 = (low2 + high2) / 2;
        if (a[mid1] == b[mid2]) {
            return a[mid1];
        };
        if (a[mid1] < b[mid2]) {
            if ((low1 + high1) % 2 == 0) {
                low1 = mid1;
                high2 = mid2;
            }
            else {
                low1 = mid1 + 1;
                high2 = mid2 ;
            }
        }
        else {
            if ((low1 + high1) % 2 == 0) {
                high1 = mid1;
                low2 = mid2;
            }
            else {
            //加1，保证取得的数列长度一样
                high1 = mid1;
                low2 = mid2 +1;
            }
        }
    };
    
}
