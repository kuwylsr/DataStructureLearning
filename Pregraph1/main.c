#include <stdio.h>
#include <stdlib.h>
#define maxnum 11
#define maxWeight 32767
#define impossibleValue '#'
#define impossibleWeight -1

typedef char VType;
typedef int Weight;
typedef struct
{
    int numVertices;
    int numEdges;
    VType *VerticesList[maxnum];
    Weight Edge[maxnum][maxnum];
}MGraph;
void getVertexPos(MGraph *G,VType v,int *x)
//根据顶点的值v查找顶点序号。
{
    int i;
    for(i=0;i<G->numVertices;i++)
    {
        if(G->VerticesList[i]==v)
        {
            *x=i;
            break;
        }
        else
        {
            *x=-1;
        }
    }
}
int NumberOfVertices(MGraph *G)
//函数返回图中当前已有的顶点个数
{
    return G->numVertices;
}
int NumberOfEdges(MGraph *G)
//函数返回图中当前已有的边个数
{
    return G->numEdges;
}
int FirstNeighbor(MGraph *G,int v)
//给出顶点v的第一个邻接顶点，如果找不到则返回函数-1
{
    int j;
    if(v!=-1)
    {
        for(j=0;j<G->numVertices;j++)
        {
            if(G->Edge[v][j]>0&&G->Edge[v][j]<maxWeight)
            {
                return j;
            }
        }
    }
    return -1;
}
int NextNeighbor(MGraph *G,int v,int w)
//给出顶点v的邻接顶点w的下一个邻接顶点，如果找不到则返回函数-1
{
    int j;
    if(v!=-1&&w!=-1)
    {
        for(j=w+1;j<G->numVertices;j++)
        {
            if(G->Edge[v][j]>0&&G->Edge[v][j]<maxWeight)
            {
                return j;
            }
        }
    }
    return -1;
}
VType getvalue(MGraph *G,int v)
//取出顶点v的数据值
{
    if(v!=-1)
    {
        return G->VerticesList[v];
    }
    else
    {
        return impossibleValue;
    }
}
Weight getweight(MGraph *G,int v,int w)
//取边(v,w)的权值
{
    if(v!=-1&&w!=-1)
    {
        return G->Edge[v][w];
    }
    else
    {
        return impossibleWeight;
    }
}
void createMGraph (MGraph *G)
//算法输入n个顶点的数据和e条边的信息，建立图G的邻接表表示
//d为0，建立无向图，d为1建立有向图
{
    G->VerticesList[0]="man,wolf,sheep,cabbage|nothing";
    G->VerticesList[1]="man,wolf,sheep|cabbage";
    G->VerticesList[2]="man,wolf,cabbage|sheep";
    G->VerticesList[3]="man,sheep,cabbage|wolf";
    G->VerticesList[4]="man,sheep|wolf,cabbage";
    G->VerticesList[5]="wolf,cabbage|man,sheep";
    G->VerticesList[6]="wolf,cabbage|man,sheep,cabbage";
    G->VerticesList[7]="sheep|man,wolf,cabbage";
    G->VerticesList[8]="cabbage|man,wolf,sheep";
    G->VerticesList[9]="nothing|man,wolf,sheep,cabbage";
    int i,j;
    int n=G->numVertices;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i==j)
            {
                G->Edge[i][j]=0;
            }
            else
            {
                G->Edge[i][j]=maxWeight;
            }
        }
    }
    G->Edge[0][5]=G->Edge[5][0]=1;
    G->Edge[1][6]=G->Edge[6][1]=1;
    G->Edge[1][7]=G->Edge[7][1]=1;
    G->Edge[2][5]=G->Edge[5][2]=1;
    G->Edge[2][6]=G->Edge[6][2]=1;
    G->Edge[2][8]=G->Edge[8][2]=1;
    G->Edge[3][7]=G->Edge[7][3]=1;
    G->Edge[3][8]=G->Edge[8][3]=1;
    G->Edge[4][7]=G->Edge[7][4]=1;
    G->Edge[4][9]=G->Edge[9][4]=1;
}
void printMGraph(MGraph *G,int d)
//输出图
//d为0输出无向图，d为1输出有向图
{
    int i,j,s,n,e;
    Weight w;
    n=G->numVertices;
    e=G->numEdges;
    printf("The number of vertices:\n%d\n",n);
    printf("The value of vertex:\n");
    for(i=0;i<n;i++)
    {
        printf("%d:%s \n",i,G->VerticesList[i]);
    }
    printf("\n");
    printf("The number of edges:\n%d\n",e);
    for(i=0;i<n;i++)
    {
        if(d==0)
        {
            s=i;
        }
        else
        {
            s=0;
        }
        for(j=s;j<n;j++)
        {
            w=G->Edge[i][j];
            if(w>0&&w<maxWeight)
            {
                printf("(%d,%d),%d\n",i,j,w);
            }
        }
    }
}
void ShorttestPath(MGraph *G,int v,Weight dist[],int path[])
//MGraph是一个带权有向图。
//算法返回两个数组：dist[j],0<=j<n,存放当前求到的从顶点v到顶点j的最短路径长度
//path[j],0<=j<n,存放求到的最短路径
{
    int i,j,k;
    int n=NumberOfVertices(G);
    Weight w,min;
    int S[maxnum];  //最短路径的顶点集
    for(i=0;i<n;i++)
    {
        dist[i]=G->Edge[v][i];
        S[i]=0;
        if(i!=v&&dist[i]<maxWeight)
        {
            path[i]=v;
        }
        else
        {
            path[i]=-1;
        }
    }
    S[v]=1;
    dist[v]=0;
    for(i=0;i<n-1;i++)
    {
        min=maxWeight;
        int u=v;
        for(j=0;j<n;j++)
        {
            if(!S[j]&&dist[j]<min)
            {
                u=j;
                min=dist[j];
            }
            S[u]=1;
        }
        for(k=0;k<n;k++)
        {
            w=G->Edge[u][k];
            if(!S[k]&&w<maxWeight&&dist[u]+w<dist[k])
            {
                dist[k]=dist[u]+w;
                path[k]=u;
            }
        }
    }
}
void printShortestPath(MGraph *G,int v,Weight dist[],int path[],int i)
{
    int j,k,h;
    int d[maxnum];
    if(i!=v)
    {
        j=i;
        k=0;
        while(j!=v)
        {
            d[k++]=j;
            j=path[j];
        }
        d[k++]=v;
        printf("到顶点[%s]的最短路径为: \n",G->VerticesList[i]);
        while(k>0)
        {
            h=k;
            h--;
            printf("%d:%s \n",d[h],G->VerticesList[d[--k]]);
        }
        printf("\n最短路径的长度为：%d\n",dist[i]);
    }
}
int main()
{
    MGraph G;
    G.numVertices=maxnum-1;
    G.numEdges=maxnum-1;
    Weight dist[maxnum];
    int path[maxnum];
    createMGraph(&G);
    printMGraph(&G,0);
    ShorttestPath(&G,0,dist,path);
    printShortestPath(&G,0,dist,path,9);
    return 0;
}
