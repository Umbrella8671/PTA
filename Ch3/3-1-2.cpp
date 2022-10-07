//最长连续递增子序列3-1-2.cpp

// #include<iostream>
// using namespace std;
// const int MAXN = 1e5;
// int main(){
//     int ar[MAXN]{0};
//     int n;
//     cin >> n;
//     for(int i = 0; i < n; i++)
//         cin >> ar[i];
//     int maxlen = 1, cnt = 1, start = 0, temp = 0;
//     for(int i = 1; i < n; i++){
//         if(ar[i] > ar[i - 1])
//             cnt++;
//         else{
//             if(cnt > maxlen){
//                 if(start < temp)
//                     start = temp;
//                 maxlen = cnt;
//             }
//             temp = i;
//             cnt = 1;
//         }
//     }
//     if(cnt > maxlen)
//         maxlen = cnt;
//     for(int i = start; i < start + maxlen; i++)
//         cout << ar[i] << " ";
// }


// 教材题解


#include<iostream>
using namespace std;

const int MAXSIZE = 1e5;

typedef int ElementType;
typedef int Position;

typedef struct LNode* List;

struct LNode{
    ElementType Data[MAXSIZE];
    Position last;
};

List ReadInput(){
    List L = new LNode;
    int N;
    cin >> N;
    for(L->last = 0; L->last < N; L->last++)
        cin >> L->Data[L->last];
    L->last--;
    return L;
}
void PrintResult(List L, Position Left, Position Right){
    Position i;
    cout << L->Data[Left];
    for(i = Left + 1; i <= Right; i++)
        cout << " " << L->Data[i];
    cout << endl;
}

int main(){
    List L = ReadInput();
    Position Left, Right, thisL, thisR, i;
    int maxLen, thisLen;
    Left = Right = thisL = thisR = 0;
    maxLen = thisLen = 1;
    for(i = 1; i < L->last; i++)
        if(L->Data[i] > L->Data[i - 1]){
            thisLen++;
            thisR++;
        } 
        else{
            if(thisLen > maxLen){
                maxLen = thisLen;
                Left = thisL;
                Right = thisR;
            }
            thisLen = 1;
            thisL = thisR = i;
        }
    if(thisLen > maxLen){
        maxLen = thisLen;
        Left = thisL;
        Right = thisR;
    }
    PrintResult(L, Left, Right);
}