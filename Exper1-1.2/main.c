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
int getVertexPos(MGraph *G,VType v,int *x)
//���ݶ����ֵv���Ҷ�����š�
{
    int i;
    for(i=0;i<G->numVertices;i++)
    {
        if(G->VerticesList[i]==v)
        {
            *x=i;
        }
    }
    if(*x!=i)
    {
        *x=-1;
    }
}
int NumberOfVertices(MGraph *G)
//��������ͼ�е�ǰ���еĶ������
{
    return G->numVertices;
}
int NumberOfEdges(MGraph *G)
//��������ͼ�е�ǰ���еı߸���
{
    return G->numEdges;
}
int FirstNeighbor(MGraph *G,int v)
//��������v�ĵ�һ���ڽӶ��㣬����Ҳ����򷵻غ���-1
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
//��������v���ڽӶ���w����һ���ڽӶ��㣬����Ҳ����򷵻غ���-1
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
//ȡ������v������ֵ
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
//ȡ��(v,w)��Ȩֵ
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
void createMGraph (MGraph *G,int n,int e,int d)
//�㷨����n����������ݺ�e���ߵ���Ϣ������ͼG���ڽӱ��ʾ
//dΪ0����������ͼ��dΪ1��������ͼ
{
    G->numVertices=n;
    G->numEdges=e;
    int i,j,k;
    VType val,e1,e2;
    Weight cost;
    for(i=0;i<G->numVertices;i++)
    {
        scanf(" %c",&val);
        G->VerticesList[i]=val;
        for(j=0;j<G->numVertices;j++)
        {
            if(i==j)
            {
                G->Edge[i][j]=0;
            }
            else
            {
                G->numEdges[i][j]=maxWeight;
            }
        }
    }
    k=0;
    while(k<G->numEdges)
    {
        scanf(" %c,%c,%d",&e1,&e2,&cost);
        getVertexPos(G,e1,i);
        getVertexPos(G,e2,j);
        if(i!=-1&&j!=-1)
        {
            G->Edge[i][j]=cost;
            if(d==0)
            {
                G->Edge[j][i]=cost;
            }
            k++;
        }
        else
        {
            printf("False information of vs!\n");
            printf("Please input again!\n");
        }
    }
}
void printMGraph(MGraph *G,int d)
//���ͼ
//dΪ0�������ͼ��dΪ1�������ͼ
{
    int i,j,s,n,e;
    Weight w;
    n=G->numVertices;
    e=G->numEdges;
    printf("The number of vertices:\n%d\n",G->numVertices);
    printf("The value of vertex:\n");
    for(i=0;i<n;i++)
    {
        printf("%d,%c ",i,G->VerticesList[i]);
    }
    printf("\n");
    printf("The number of edges:%d\n",G->numEdges);
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
int main()
{
    printf("Hello world!\n");
    return 0;
}
