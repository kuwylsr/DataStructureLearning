#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define maxnum 100
#define maxWeight 1000
#define minWeight 10
#define impossibleValue '#'
#define impossibleWeight -1

typedef double WeightType;
typedef struct
{
    int x,y;
    int title;
} point;
typedef struct
{
    point v1,v2;
    WeightType cost;
} MSTEdgeNode;
typedef struct
{
    MSTEdgeNode edgeValue[4950];
    int n;
} MinSpanTree;


typedef double Weight;
typedef point VType;
typedef struct
{
    int numVertices;
    int numEdges;
    VType VerticesList[maxnum];
    Weight Edge[maxnum][maxnum];
} MGraph;

void createMGraph (MGraph *G)
//算法输入n个顶点的数据和e条边的信息，建立图G的邻接表表示
{
    FILE *fp;
    int i,j,n;
    fp=fopen("Bridge.txt","r");
    if(fp==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    fscanf(fp,"%d",&n);
    G->numVertices=n;
    G->numEdges=(n*(n-1))/2;
    for(i=0; i<n; i++)
    {
        fscanf(fp,"%d,%d",&G->VerticesList[i].x,&G->VerticesList[i].y);
        G->VerticesList[i].title=i;
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(i==j)
            {
                G->Edge[i][j]=0;
            }
            else
            {
                G->Edge[i][j]=sqrt((G->VerticesList[i].x-G->VerticesList[j].x)*(G->VerticesList[i].x-G->VerticesList[j].x)+(G->VerticesList[i].y-G->VerticesList[j].y)*(G->VerticesList[i].y-G->VerticesList[j].y));
                G->Edge[j][i]=G->Edge[i][j];
            }
        }
    }
    fclose(fp);
}
void printMGraph(MGraph *G)
//输出图
//d为0输出无向图，d为1输出有向图
{
    int i,j,s,n,e;
    Weight w;
    n=G->numVertices;
    e=G->numEdges;
    printf("The number of vertices:\n%d\n",n);
    printf("The value of vertex:\n");
    for(i=0; i<n; i++)
    {
        printf("%d:(%d,%d) \n",i,G->VerticesList[i].x,G->VerticesList[i].y);
    }
    printf("\n");
    printf("The number of edges:\n%d\n",e);
    printf("The value of edges:\n");
    for(i=0; i<n; i++)
    {
        s=i;
        for(j=s; j<n; j++)
        {
            w=G->Edge[i][j];
            if(w>0&&w<maxWeight)
            {
                printf("((%d,%d),(%d,%d)),%lf\n",G->VerticesList[i].x,G->VerticesList[i].y,G->VerticesList[j].x,G->VerticesList[j].y,w);
            }
        }
    }
}
void Prim (MGraph *G,int u,MinSpanTree *T)
{
    int i,j,v,n=G->numVertices;   //图中顶点数
    Weight lowcost[maxnum];   //保存生成树外各结点到生成树内顶点的最短距离
    int nearvex[maxnum];    //保存生成树外各顶点到生成树内哪个顶点距离小
    for(i=0; i<G->numVertices; i++)
    {
        lowcost[i]=G->Edge[u][i];
        nearvex[i]=0;
    }
    nearvex[u]=-1;   //顶点u加到生成树定点集合，用-1表示
    MSTEdgeNode e;
    Weight min;
    Weight max;
    T->n=0;
    for(i=0; i<G->numVertices; i++)  //循环n-1次，加入n-1条边
    {
        if(i!=u)
        {
            min=maxWeight;     //求生成树外顶点到生成树内顶点最小边
            max=minWeight;     //求生成树外顶点到生成树内顶点最大边
            v=0;
            for(j=0; j<G->numVertices; j++)   //确定当前边及顶点位置
            {
                if(nearvex[j]!=-1&&lowcost[j]<=min&&lowcost[j]>=max)
                {
                    v=j;
                    min=lowcost[j];
                }
            }
            if(v)           //v=0表示再也找不到要求的顶点了
            {
                e.v1.title=nearvex[v];
                e.v2.title=v;
                e.cost=lowcost[v];
                T->edgeValue[T->n++]=e;       //加入生成树边集合
                nearvex[v]=-1;                        //加入生成树顶点集合
                for(j=0; j<G->numVertices; j++)
                {
                    if(nearvex[j]!=-1&&G->Edge[v][j]<lowcost[j])
                    {
                        lowcost[j]=G->Edge[v][j];
                        nearvex[j]=v;
                    }
                }
            }
        }
    }
}
int main()
{
    MGraph G;
    MinSpanTree T;
    createMGraph(&G);
    printMGraph(&G);
    Prim(&G,0,&T);
    int i,j;
    double sum=0;
    printf("\n");
    if(T.n<G.numVertices-1)
    {
        printf("no");
    }
    else
    {
        printf("The plan of building bridge:\n");
        for(i=0; i<T.n; i++)
        {
            printf("(%d,%d)%lf\n",T.edgeValue[i].v1.title,T.edgeValue[i].v2.title,T.edgeValue[i].cost);
            sum+=T.edgeValue[i].cost;
        }
        printf("\nThe least expense is:\n%lf Yuan",sum*100);
    }
    return 0;
}
