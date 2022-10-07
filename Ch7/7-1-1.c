// 模拟Excel排序
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define MAXID 6
#define MAXNAME 8
#define MAXN 100000
struct Student{
    char id[MAXID + 1];
    char name[MAXNAME + 1];
    int grade;
}Record[MAXN];
int ComparId(const void* a, const void* b){
    return strcmp(((const struct Student*)a)->id, ((const struct Student*)b)->id);
}
int ComparName(const void* a, const void* b){
    int k = strcmp(((const struct Student*)a)->name, ((const struct Student*)b)->name);
    if(!k)
        k = strcmp(((const struct Student*)a)->id, ((const struct Student*)b)->id);
    return k; 
}
int ComparGrade(const void* a, const void* b){
    int k = ((const struct Student*)a)->grade - ((const struct Student*)b)->grade;
    if(!k)
        k = strcmp(((const struct Student*)a)->id, ((const struct Student*)b)->id);
    return k;
}
int main(){
    int N, C, i;
    scanf("%d%d", &N, &C);
    for(i = 0; i < N; i++)
        scanf("%s%s%d", Record[i].id, Record[i].name, &Record[i].grade);
    switch(C){
    case 1: qsort(Record, N, sizeof(struct Student), ComparId); break;
    case 2: qsort(Record, N, sizeof(struct Student), ComparName); break;
    case 3: qsort(Record, N, sizeof(struct Student), ComparGrade); break;
    }
    for(i = 0; i < N; i++)
        printf("%s %s %d\n", Record[i].id, Record[i].name, Record[i].grade);
}