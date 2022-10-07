// 直捣黄龙
#include <stdio.h>
#include <stdlib.h>

#define MAXN 201
#define INF 65535

int G[MAXN][MAXN];
int Enmy[MAXN];

void Init(){
    for(int i = 0; i < MAXN; i++)
        for(int j = 0; j < MAXN; j++)
            G[i][j] = INF;    
}
int FindMin(int N, int Dist[], int Collected[]){
    int Min, MinV, i;
    Min = INF;
    for(i = 0; i < N; i++)
        if(!Collected[i] && Dist[i] < Min){
            Min = Dist[i];
            MinV = i;
        }
    if(Min < INF) return MinV;
    else return -1;
}
void Dijstra(int N, int S, int D, int *RoadNum, int *MinDist, int *MaxEnmyNum, int Path[]){
    int Collected[MAXN], Dist[MAXN], RoadCnt[MAXN], EnmyCnt[MAXN], CityCnt[MAXN];
    int V, W;
    for(V = 0; V < N; V++){
        Dist[V] = G[S][V];
        Collected[V] = 0;
        Path[V] = S;
    }
    Collected[S] = 1;
    Dist[S] = 0;
    RoadCnt[S] = 1;
    EnmyCnt[S] = 0;
    CityCnt[S] = 1;
    while(1){
        V = FindMin(N, Dist, Collected);
        if(V == -1) break;
        Collected[V] = 1;
        for(W = 0; W < N; W++)
            if(!Collected[W] && G[V][W] < INF){
                if(Dist[W] > Dist[V] + G[V][W]){
                    Dist[W] = Dist[V] + G[V][W];
                    CityCnt[W] = CityCnt[V] + 1;
                    EnmyCnt[W] = EnmyCnt[V] + Enmy[V];
                    RoadCnt[W] = RoadCnt[V];
                    Path[W] = V;
                }else if(Dist[W] == Dist[V] + G[V][W]){
                    RoadCnt[W] += RoadCnt[V];
                    if(CityCnt[W] < CityCnt[V] + 1){
                        CityCnt[W] = CityCnt[V] + 1;
                        EnmyCnt[W] = EnmyCnt[V] + Enmy[V];
                        Path[W] = V;
                    }else if(CityCnt[W] == CityCnt[V] + 1
                        && EnmyCnt[W] < EnmyCnt[V]){
                            EnmyCnt[W] = EnmyCnt[V] + Enmy[V];
                            Path[W] = V;
                        }
                }
            }
    }
    *RoadNum = RoadCnt[D];
    *MinDist = Dist[D];
    *MaxEnmyNum = EnmyCnt[D];
}

int main(){
    
}