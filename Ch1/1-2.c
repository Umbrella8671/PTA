#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXSIZE 10000
#define NotFound -1

typedef int Position;
typedef int ElementType;
typedef struct LNode* List;
struct LNode{
    ElementType Data[MAXSIZE];
    Position Last;   
};

bool Insert(List L, ElementType x);
Position Search(List L, ElementType x);
int main(){
    List L = (List) malloc(sizeof(struct LNode));
    int n, x;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%d", &L->Data[i]);
    L->Last = n - 1;
    scanf("%d", &x);
    if(Insert(L, x))
        printf("true\n");
    else
        printf("false\n");
    
    for(int i = 0; i <= L->Last; i++)
        printf("%d ", L->Data[i]);

}



bool Insert(List L, ElementType x){
    if(L->Last == MAXSIZE - 1)
        return false;
    
    int i = 0;
    
    //for(i = 0; L->Data[i] > x; i++);

    i = Search(L, x);
    if(L->Data[i] == x)
        return false;
    
    int k;
    for(k = L->Last; k >= i; k--)
        L->Data[k + 1] = L->Data[k];
    L->Data[i] = x;
    L->Last++;
    return true;
}
Position Search(List L, ElementType x){
    Position Left = 0, Right = L->Last;
    Position mid;

    while(Left < Right){
        mid = (Left + Right) / 2;
        if(L->Data[mid] > x)
            Left = mid + 1;
        else if(L->Data[mid] < x)
            Right = mid - 1;
        else
            return mid;
    }
    return Left + 1;
}