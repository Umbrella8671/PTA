// 树同构
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string>
using namespace std;

#define MAX_SIZE 1000

typedef struct Node{
    char data;
    int lchild;
    int rchild;
}Node;

typedef Node Tree[MAX_SIZE];

Tree t1, t2;

int FindRoot(Tree &t){
    int n;
    cin >> n;
    if(n == 0)
        return 12;
    cin.get();
    int i;
    for(i = 0; i < n; i++){
        string str;
        getline(cin, str);
        t[i].data = str[0];
        t[i].lchild = str[2] != '-' ? str[2] - '0' : 12;
        t[i].rchild = str[4] != '-' ? str[4] - '0' : 12; 
    }
    bool check[15]{false};
    for(i = 0; i < n; i++)
        check[t[i].lchild] = check[t[i].rchild] = true;
    for(i = 0; i < n; i++)
        if(!check[i])
            break;
    return i;
}

bool judge(int root1, int root2){
    if(root1 == 12 && root2 == 12)
        return true;
    else if(t1[root1].data == t2[root2].data)
        return (judge(t1[root1].lchild, t2[root2].lchild) || judge(t1[root1].lchild, t2[root2].rchild))
            && (judge(t1[root1].rchild, t2[root2].rchild) || judge(t1[root1].rchild, t2[root2].lchild));
    else 
        return false;
}
int main(){
    int root1 = FindRoot(t1);
    int root2 = FindRoot(t2);
    if(judge(root1, root2))
        cout << "Yes\n";
    else
        cout << "No\n";
}