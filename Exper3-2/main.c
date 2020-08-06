/*
����ʵ���������ȫͼ��һһ��Ӧ��ϵ��
����V={ v0,v1,v2,.......vn-1,vn}������v0��ʾ��һ�����vi(i=1,2,3.....,n)��ʾ��i��ĩ��
E={(vi,vj)|i=0,1,......,n-1,n;j=1,2,......,n-1,n}�����ӵ�vi��vj�ıߣ�
��ÿ���߶���һ��Ȩ�����������ʹ��ĳ�ַ���ʱ������Щ���ڵľ������ã�
���磺��vi��vj�������ߵ�Ȩ���ʹ�����ĳ���豸�ӵ�i��ʹ�õ���j���������Ĺ��÷Ѽ���ά�޷ѵľ�ֵ.
�����Ͱ�һ��ʵ�������һ����Ȩ��������ȫͼ֮�佨����һ��ͬ����ϵ��
����豸���¾��������ٵ����⣬�͵ȼ�����������������ͼ�������·��
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
void createMGraph (MGraph *G,int n,int e,int d,int price[],int repair[])
//�㷨����n����������ݺ�e���ߵ���Ϣ������ͼG���ڽӱ��ʾ
//dΪ0����������ͼ��dΪ1��������ͼ
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
        printf("������[%C]�����·��Ϊ: ",G->VerticesList[i]);
        while(k>0)
        {
            printf("%c ",G->VerticesList[d[--k]]);
        }
        printf("\n���·���ĳ���Ϊ��%d\n",dist[i]);
    }
}
void ShorttestPath(MGraph *G,int v,Weight dist[],int path[])
//MGraph��һ����Ȩ����ͼ��
//�㷨�����������飺dist[j],0<=j<n,��ŵ�ǰ�󵽵ĴӶ���v������j�����·������
//path[j],0<=j<n,����󵽵����·��
{
    int i,j,k;
    int n=NumberOfVertices(G);
    Weight w,min;
    int S[maxVertices];  //���·���Ķ��㼯
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
    printf("�����빲�м��꣺\n");
    scanf("%d",&num_year);
    int price[num_year];
    printf("������%d������豸�ļ۸�\n",num_year);
    for(i=0;i<num_year;i++)
    {
        scanf("%d",&price[i]);
    }
    printf("������ÿ��ʹ��ʱ��ε�ά�޷��ã�\n");
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

