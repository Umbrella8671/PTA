// PTA排名汇总

#include <stdio.h>
#include <stdlib.h>
#define MAXN 30000

typedef struct{
    long long int number;
    int score;
    int Snumber;
    int curnumber;
    int newnumber;
}Student;

int ComPareStudent(const void* a, const void* b){
    const Student* sa = (const Student*)a;
    const Student* sb = (const Student*)b;
    int flag = sb->score - sa->score;
    if(!flag)
        flag = sa->number > sb->number ? 1 : -1;
    return flag;
}

int main(){
    int N, K, i, j, total = 0;
    Student A[MAXN];
    scanf("%d", &N);
    j = 1;
    while(j <= N){
        scanf("%d", &K);
        
        for(i = total; i < total + K; i++){
            scanf("%lld%d", &A[i].number, &A[i].score);
            A[i].Snumber = j;
        }
        qsort(A + total, K, sizeof(Student), ComPareStudent);
        A[total].curnumber = 1;
        for(i = total + 1; i < total + K; i++){
            if(A[i].score == A[i - 1].score)
                A[i].curnumber = A[i - 1].curnumber;
            else
                A[i].curnumber = i - total + 1;
        }
        total += K;
        ++j;
    }
    printf("%d\n", total);
    qsort(A, total, sizeof(Student), ComPareStudent);
    A[0].newnumber = 1;
    for(i = 1; i < total; i++)
        if(A[i].score == A[i - 1].score)
                A[i].newnumber = A[i - 1].newnumber;
        else
            A[i].newnumber = i + 1;
    for(i = 0; i < total; i++)
        printf("%013lld %d %d %d\n", A[i].number, A[i].newnumber, A[i].Snumber, A[i].curnumber);
}

