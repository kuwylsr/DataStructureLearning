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
//�㷨����n����������ݺ�e���ߵ���Ϣ������ͼG���ڽӱ��ʾ
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
//���ͼ
//dΪ0�������ͼ��dΪ1�������ͼ
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
    int i,j,v,n=G->numVertices;   //ͼ�ж�����
    Weight lowcost[maxnum];   //���������������㵽�������ڶ������̾���
    int nearvex[maxnum];    //����������������㵽���������ĸ��������С
    for(i=0; i<G->numVertices; i++)
    {
        lowcost[i]=G->Edge[u][i];
        nearvex[i]=0;
    }
    nearvex[u]=-1;   //����u�ӵ����������㼯�ϣ���-1��ʾ
    MSTEdgeNode e;
    Weight min;
    Weight max;
    T->n=0;
    for(i=0; i<G->numVertices; i++)  //ѭ��n-1�Σ�����n-1����
    {
        if(i!=u)
        {
            min=maxWeight;     //���������ⶥ�㵽�������ڶ�����С��
            max=minWeight;     //���������ⶥ�㵽�������ڶ�������
            v=0;
            for(j=0; j<G->numVertices; j++)   //ȷ����ǰ�߼�����λ��
            {
                if(nearvex[j]!=-1&&lowcost[j]<=min&&lowcost[j]>=max)
                {
                    v=j;
                    min=lowcost[j];
                }
            }
            if(v)           //v=0��ʾ��Ҳ�Ҳ���Ҫ��Ķ�����
            {
                e.v1.title=nearvex[v];
                e.v2.title=v;
                e.cost=lowcost[v];
                T->edgeValue[T->n++]=e;       //�����������߼���
                nearvex[v]=-1;                        //�������������㼯��
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
