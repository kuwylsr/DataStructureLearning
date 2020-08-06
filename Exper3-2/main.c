/*
建立实际问题和完全图的一一对应关系，
假设V={ v0,v1,v2,.......vn-1,vn}，其中v0表示第一年初，vi(i=1,2,3.....,n)表示第i年末，
E={(vi,vj)|i=0,1,......,n-1,n;j=1,2,......,n-1,n}是连接点vi到vj的边，
把每条边都赋一个权，这个代表了使用某种方案时，在这些年内的净经费用，
例如：（vi，vj）这条边的权，就代表了某种设备从第i年使用到第j年所发生的购置费加上维修费的净值.
这样就把一个实际问题和一个赋权的有向完全图之间建立了一个同构关系，
求解设备更新净费用最少的问题，就等价于在所建立的网络图中求最短路，
*/
#include <stdio.h>
#include <stdlib.h>
#define maxVertices 30
#define maxEdges 900
#define maxWeight 32767
#define impossibleValue '#'
#define impossibleWeight -1

typedef char VType;
typedef int Weight;
typedef struct
{
    int numVertices;
    int numEdges;
    VType VerticesList[maxVertices];
    Weight Edge[maxVertices][maxVertices];
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
void createMGraph (MGraph *G,int n,int e,int d,int price[],int repair[])
//算法输入n个顶点的数据和e条边的信息，建立图G的邻接表表示
//d为0，建立无向图，d为1建立有向图
{
    G->numVertices=n;
    G->numEdges=e;
    int i,j,k;
    VType val,e1,e2;
    printf("Please input the value of vertices:\n");
    for(i=0;i<n;i++)
    {
        scanf(" %c",&val);
        G->VerticesList[i]=val;
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

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(G->VerticesList[i]<G->VerticesList[j])
            {
                    G->Edge[i][j]=price[i];
                    for(k=0;k<j-i;k++)
                    {
                        G->Edge[i][j]+=repair[k];
                    }
            }
        }
    }
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
        printf("%d,%c ",i,G->VerticesList[i]);
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
void printShortestPath(MGraph *G,int v,Weight dist[],int path[],int i)
{
    int j,k;
    int d[maxVertices];
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
        printf("到顶点[%C]的最短路径为: ",G->VerticesList[i]);
        while(k>0)
        {
            printf("%c ",G->VerticesList[d[--k]]);
        }
        printf("\n最短路径的长度为：%d\n",dist[i]);
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
    int S[maxVertices];  //最短路径的顶点集
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

int main()
{
    MGraph G;
    int n,e=0,num_year,i;
    printf("请输入共有几年：\n");
    scanf("%d",&num_year);
    int price[num_year];
    printf("请输入%d年年初设备的价格：\n",num_year);
    for(i=0;i<num_year;i++)
    {
        scanf("%d",&price[i]);
    }
    printf("请输入每个使用时间段的维修费用：\n");
    int repair[num_year];

    for(i=0;i<num_year;i++)
    {
        scanf("%d",&repair[i]);
    }
    n=num_year+1;
    for(i=1;i<=num_year;i++)
    {
        e=e+i;
    }
    Weight dist[e];
    int path[e];
    createMGraph(&G,n,e,1,price,repair);
    printMGraph(&G,1);
    ShorttestPath(&G,0,dist,path);
    printShortestPath(&G,0,dist,path,5);
    return 0;
}

