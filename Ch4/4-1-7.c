// 文件传输，并查集

#include <stdio.h>

#define MaxSize 10000

void Initialization(int s[], int n){
    for(int i = 0; i < n; i++)
        s[i] = -1;
}
void Union(int s[], int root1, int root2){
    if(s[root1] < s[root2]){
        s[root1] += s[root2];
        s[root2] = root1;
    }else{
        s[root2] += s[root1];
        s[root1] = root2;
    }
}

int Find(int s[], int x){
    if(s[x] < 0)
        return x;
    else
        return s[x] = Find(s, s[x]);
}

void Input_connection(int s[]){
    int u, v, root1, root2;
    scanf("%d%d", &u, &v);
    root1 = Find(s, u - 1);
    root2 = Find(s, v - 1);
    if(root1 != root2)
        Union(s, root1, root2);
}
void Check_connection(int s[]){
    int u, v, root1, root2;
    scanf("%d%d", &u, &v);
    root1 = Find(s, u - 1);
    root2 = Find(s, v - 1);
    if(root1 != root2)
        printf("no\n");
    else
        printf("yes\n");
}
void Check_network(int s[], int n){
    int Cnt = 0;
    for(int i = 0; i < n; i++)
        if(s[i] < 0)
            Cnt++;
    if(Cnt == 1)
        printf("The network is connected.\n");
    else
        printf("There are %d components.\n", Cnt);
}
int main(){
    int s[MaxSize], n;
    scanf("%d", &n);
    Initialization(s, n);
    char in;
    do{
        scanf("%c", &in);
        switch(in){
        case 'I': Input_connection(s); break;
        case 'C': Check_connection(s); break;
        case 'S': Check_network(s, n); break;
        }
    }while(in != 'S');
}