// 得才论

#include <stdio.h>
#include <stdlib.h>


#define MAXN 100000

typedef struct Student{
    int num;
    int GradeA;
    int GradeB;
}Student;
int CompareStu(const void* a, const void* b){
    const Student* sa = (const Student*)a;
    const Student* sb = (const Student*)b;
    int suma, sumb, flag;
    suma = sa->GradeA + sa->GradeB;
    sumb = sb->GradeA + sb->GradeB;
    flag = sumb - suma;
    
    if(!flag){
        flag = sb->GradeA - sa->GradeA;
        if(!flag)
            flag = sa->num - sb->num;
    }
    return flag;
}
void PrintResults(Student *a, int N){
    for(int i = 0; i < N; i++)
        printf("%d %d %d\n", a[i].num, a[i].GradeA, a[i].GradeB);
}
int main(){
    int N, L, H;
    scanf("%d%d%d", &N, &L, &H);
    Student A[MAXN], B[MAXN], C[MAXN], D[MAXN];
    Student stu;
    int Cnt1 = 0, Cnt2 = 0, Cnt3 = 0, Cnt4 = 0;
    for(int i = 0; i < N; i++){
        scanf("%d%d%d", &stu.num, &stu.GradeA, &stu.GradeB);
        if(stu.GradeA >= L && stu.GradeB >= L){
            if(stu.GradeA >= H && stu.GradeB >= H)
                A[Cnt1++] = stu;
            else if(stu.GradeA >= H && stu.GradeB < H)
                B[Cnt2++] = stu;
            else if(stu.GradeA < H && stu.GradeB >= H)
                D[Cnt4++] = stu;
            else if(stu.GradeA >= stu.GradeB)
                C[Cnt3++] = stu;
            else
                D[Cnt4++] = stu;
        }
    }
    qsort(A, Cnt1, sizeof(Student), CompareStu);
    qsort(B, Cnt2, sizeof(Student), CompareStu);
    qsort(C, Cnt3, sizeof(Student), CompareStu);
    qsort(D, Cnt4, sizeof(Student), CompareStu);
    printf("%d\n", Cnt1 + Cnt2 + Cnt3 + Cnt4);
    PrintResults(A, Cnt1);
    PrintResults(B, Cnt2);
    PrintResults(C, Cnt3);
    PrintResults(D, Cnt4);
}