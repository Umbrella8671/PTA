#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100000
#define NotFound -1

typedef int Position;
typedef int ElementType;
typedef struct LNode* List;

struct LNode{
    ElementType Data[MAXSIZE];
    Position Last;   
};

Position BinarySearch(List L, ElementType x);
Position BinarySearch_(List L, ElementType x);
Position BS(List L, ElementType x, Position Left, Position Right);

int main(){
    List L = NULL;
    L = (List) malloc(sizeof(struct LNode));
    int n;
    scanf("%d", &n);
    int i;
    for(i = 0; i < n; i++)
        scanf("%d", &L->Data[i]);
    L->Last = n - 1;
    printf("%d %d\n", BinarySearch(L, 31), BinarySearch_(L, 31));
    
}


Position BinarySearch(List L, ElementType x){
    Position Left = 0, Right = L->Last;
    Position mid;

    while(Left < Right){
        mid = (Left + Right) / 2;
        if(L->Data[mid] < x)
            Left = mid + 1;
        else if(L->Data[mid] > x)
            Right = mid - 1;
        else
            return mid;
    }
    return NotFound;
}
Position BinarySearch_(List L, ElementType x){
    return BS(L, x, 0, L->Last);
}

Position BS(List L, ElementType x, Position Left, Position Right){
    if(Left > Right)
        return NotFound;
    int mid = (Left + Right) / 2;
    if(L->Data[mid] < x)
        return BS(L, x, mid, Right);
    else if(L->Data[mid] > x)
        return BS(L, x, Left, mid);
    else
        return mid;
}
