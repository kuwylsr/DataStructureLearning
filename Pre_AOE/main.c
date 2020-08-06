#include <stdio.h>
#include <stdlib.h>
#define maxVertices 30 //图中最大定点数目
#define maxEdges 450   //图中最大边的数目
#define impossibleValue '#'



typedef int Weight;
typedef char VType; //顶点数据的数据类型
typedef struct
{
    int v1,v2;
    Weight key;
}Edge;

typedef struct Enode //边结点的结构定义
{
    int dest;                  //边的另一个结点的位置
    Weight cost;
    struct Enode *link; //下一条边链指针
}EdgeNode;
typedef struct Vnode //顶点结构的定义
{
    VType data;             //顶点的名字
    struct Enode *adj;   //边链表的头指针
}VertexNode;
typedef struct    //图的定义
{
    VertexNode VerticesList[maxVertices];  //顶点表（各边链表的头结点）
    int numVertices;    //图中实际顶点的个数
    int numEdges;            //图中实际边的条数
}ALGraph;
void getVertexPos(ALGraph *G,VType v,int *x)
//根据顶点的值v查找顶点序号。
{
    int i=0;
    while(i<G->numVertices&&G->VerticesList[i].data!=v)
    {
        i++;
    }
    if(i<G->numVertices)
    {
        *x=i;
    }
    else
    {
        *x=-1;
    }
}
int NumberOfVertices(ALGraph *G)
//函数返回图中当前已有的顶点个数
{
    return G->numVertices;
}
int NumberOfEdges(ALGraph *G)
//函数返回图中当前已有的边个数
{
    return G->numEdges;
}
int FirstNeighbor(ALGraph *G,int v)
//给出顶点v的第一个邻接顶点，如果找不到则返回函数-1
{
    if(v!=-1)
    {
        EdgeNode *p=G->VerticesList[v].adj;
        if(p!=NULL)
        {
            return p->dest;
        }
    }
        return -1;
}
int NextNeighbor(ALGraph *G,int v,int w)
//给出顶点v的邻接顶点w的下一个邻接顶点，如果找不到则返回函数-1
{
    if(v!=-1)
    {
        EdgeNode *p=G->VerticesList[v].adj;
        while(p!=NULL&&p->dest!=w)
        {
              p=p->link;
        }
        if(p!=NULL&&p->link!=NULL)
        {
            return p->link->dest;
        }
    }
        return -1;
}
VType getvalue(ALGraph *G,int v)
//取出顶点v的数据值
{
    if(v!=-1)
    {
        return G->VerticesList[v].data;
    }
    else
    {
        return impossibleValue;
    }
}
void createALGraph (ALGraph *G)
//算法输入n个顶点的数据和e条边的信息，建立图G的邻接表表示
//d为0，建立无向图，d为1建立有向图
{
    FILE *fp;
    fp=fopen("Graph.txt","r");
    if(fp==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    int i,j,k;
    VType val,e1,e2;
    Weight c;
    EdgeNode *q,*p;
    G->numVertices=11;  //图的顶点数目
    G->numEdges=12;             //图的边的数目
    for(i=0;i<G->numVertices;i++)  //为顶点表赋值，建立顶点表
    {
        fscanf(fp," %c",&val);
        G->VerticesList[i].data=val;
        G->VerticesList[i].adj=NULL;
    }
    i=0;
    while(i<G->numEdges)  //建立各顶点的边链表
    {
        fscanf(fp," %c,%c,%d",&e1,&e2,&c);
        getVertexPos(G,e1,&j);
        getVertexPos(G,e2,&k);
        if(j!=-1&&k!=-1)
        {
            p=G->VerticesList[j].adj;         //顶点j的边链表头指针
            while(p!=NULL&&p->dest!=k)
            {
                p=p->link;
            }
            if(p==NULL)       //图中没有重边，加入新边
            {
                q=(EdgeNode *)malloc(sizeof(EdgeNode));
                q->dest=k;
                q->cost=c;
                q->link=G->VerticesList[j].adj;    //前插，链入顶点k的边链表
                G->VerticesList[j].adj=q;
                i++;
            }
        }
    }
}
void printALGraph(ALGraph *G)
//输出图
{
    int i;
    EdgeNode *p;
    printf("The number of vertices:\n%d\n",G->numVertices);
    printf("The value of vertex:\n");
    for(i=0;i<G->numVertices;i++)
    {
        printf("%c ",G->VerticesList[i].data);
    }
    printf("\n");
    printf("The number of edges:%d\n",G->numEdges);
    for(i=0;i<G->numVertices;i++)
    {
        for(p=G->VerticesList[i].adj;p!=NULL;p=p->link)
        {
            printf("(%d, %d)%d ",i,p->dest,p->cost);
        }
        printf("\n");
    }
}
void CriticalPath (ALGraph *G,Edge cp[],int *n)
//算法对带权图G计算关键路径。数组cp返回关键活动，n为关键活动个数
{
    int j,i,k,m=-1,u,v,top=-1;
    Weight w;
    EdgeNode *p;
    Edge ed;
    int ind[maxVertices];  //入度数组
    for(i=0;i<G->numVertices;i++)
    {
        ind[i]=0;
    }
    for(i=0;i<G->numVertices;i++)
    {
        for(p=G->VerticesList[i].adj;p!=NULL;p=p->link)
        {
            ind[p->dest]++;    //统计各顶点入度
        }
    }
    Weight Ve[maxVertices],Vl[maxVertices];  //各事件最早和最迟开始时间
    Weight Ae[maxEdges],Al[maxEdges];         //各活动最早和最迟开始时间
    for(i=0;i<G->numVertices;i++)
    {
        Ve[i]=0;
    }

    for(i=0;i<G->numVertices;i++)     //所有入度为0的顶点进栈
    {
        if(!ind[i])
        {
            ind[i]=top;
            top=i;
        }
    }

    while(top!=-1)     //正向计算Ve[]
    {
        u=top;
        top=ind[top];     //退栈u
        ind[u]=m;              //反向拉链
        m=u;

        for(p=G->VerticesList[u].adj;p!=NULL;p=p->link)
        {
            w=p->cost;
            j=p->dest;
            if(Ve[u]+w>Ve[j])       //计算Ve
            {
                Ve[j]=Ve[u]+w;
            }
            if(--ind[j]==0)   //邻接顶点入度减1
            {
                ind[j]=top;   //顶点入度减至0进栈
                top=j;
            }
        }
    }
    for(i=0;i<G->numVertices;i++)
    {
        Vl[i]=Ve[m];
    }
    while(m!=-1)            //逆向计算Vl[]
    {
        v=ind[m];           //逆拓扑排序
        m=v;
        if(m==-1)
        {
            break;
        }
        for(p=G->VerticesList[v].adj;p!=NULL;p=p->link)
        {
            k=p->dest;
            w=p->cost;
            if(Vl[k]-w<Vl[v])
            {
                Vl[v]=Vl[k]-w;
            }
        }
    }
    k=0;
    for(i=0;i<G->numVertices;i++)           //求各活动的Ae和Al
    {
        for(p=G->VerticesList[i].adj;p!=NULL;p=p->link)
        {
            Ae[k]=Ve[i];
            Al[k]=Vl[p->dest]-p->cost;
            ed.v1=i;
            ed.v2=p->dest;
            ed.key=p->cost;
            cp[k++]=ed;
        }
    }
    (*n)=0;
    while((*n)<k)       //计算并保存关键活动
    {
        if(Ae[(*n)]==Al[(*n)])
        {
            (*n)++;
        }
        else
        {
            for(j=(*n)+1;j<k;j++)
            {
                cp[j-1]=cp[j];
                Ae[j-1]=Ae[j];
                Al[j-1]=Al[j];
            }
            k--;
        }
    }
}
int main()
{
    ALGraph G;
    Edge cp[11];
    int n,i,time=0;
    createALGraph(&G);
    printALGraph(&G);
    CriticalPath(&G,cp,&n);
    printf("The critical path :\n");
    for(i=0;i<n;i++)
    {
        printf("%d -> %d\n",cp[i].v1,cp[i].v2);
        time+=cp[i].key;
    }
    printf("The last time is:\n%d",time);

    return 0;
}
