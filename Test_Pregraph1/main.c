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
//���ݶ����ֵv���Ҷ�����š�
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
void createMGraph (MGraph *G)
//�㷨����n����������ݺ�e���ߵ���Ϣ������ͼG���ڽӱ��ʾ
//dΪ0����������ͼ��dΪ1��������ͼ
{
    G->VerticesList[0]="man,wolf,sheep,cabbage|nothing";
    G->VerticesList[1]="man,wolf,sheep|cabbage";
    G->VerticesList[2]="man,wolf,cabbage|sheep";
    G->VerticesList[3]="man,sheep,cabbage|wolf";
    G->VerticesList[4]="man,sheep|wolf,cabbage";
    G->VerticesList[5]="wolf,cabbage|man,sheep";
    G->VerticesList[6]="wolf|cabbage,man,sheep";
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
//���ͼ
//dΪ0�������ͼ��dΪ1�������ͼ
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
void DFS_Traversal(MGraph *G,int x,int y,int path[])
//��ͼG����������ȱ����������̣��ݹ飩

{
    int i;
    int n=NumberOfVertices(G);
    int visited[maxnum];
    for(i=0; i<n; i++)
    {
        visited[i]=0;
    }
    DFS_recur(G,x,y,visited,path);
    printf("\n");
}
void DFS_recur(MGraph *G,int v,int y,int visited[],int path[])
//�Ӷ���λ��v��������������ȵĴ���������пɶ������δ���ʹ��Ķ���
//�㷨���õ�һ����������visited���Լ����ʹ��Ķ��������ʱ��
{
    visited[v]=1;
    int w=FirstNeighbor(G,v);
    while(w!=-1&&FirstNeighbor(G,w)!=y)
    {
        if(!visited[w])
        {
            path[v]=w;
            DFS_recur(G,w,y,visited,path);
        }
        w=NextNeighbor(G,v,w);
    }
    path[w]=y;
}

int main()
{
    MGraph G;
    int x=0,y=9,i=x;
    G.numVertices=maxnum-1;
    G.numEdges=maxnum-1;
    int path[500];
    createMGraph(&G);
    printMGraph(&G,0);
    printf("The path is:\n");
    DFS_Traversal(&G,x,y,path);
    printf("0:%s\n",G.VerticesList[0]);
    while(path[i]!=y)
    {
        printf("%d:%s\n",path[i],G.VerticesList[path[i]]);
        i=path[i];
    }
    printf("9:%s\n",G.VerticesList[9]);
    return 0;
}
