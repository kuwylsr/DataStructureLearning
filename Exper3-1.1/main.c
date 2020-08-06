#include <stdio.h>
#include <stdlib.h>
#define maxVertices 30 //图中最大定点数目
#define maxEdges 450   //图中最大边的数目

#define impossibleValue '#'

typedef char VType; //顶点数据的数据类型
typedef struct Enode //边结点的结构定义
{
    int dest;                  //边的另一个结点的位置
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
void createALGraph (ALGraph *G,int n,int e,int d)
//算法输入n个顶点的数据和e条边的信息，建立图G的邻接表表示
//d为0，建立无向图，d为1建立有向图
{
    int i,j,k;
    VType val,e1,e2;
    EdgeNode *q,*p;
    G->numVertices=n;  //图的顶点数目
    G->numEdges=e;             //图的边的数目
    printf("Please input the value of vertices:\n");
    for(i=0;i<G->numVertices;i++)  //为顶点表赋值，建立顶点表
    {
        scanf(" %c",&val);
        G->VerticesList[i].data=val;
        G->VerticesList[i].adj=NULL;
    }
    i=0;
    while(i<G->numEdges)  //建立各顶点的边链表
    {
        printf("Input the one edges :\n");
        scanf(" %c,%c",&e1,&e2);
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
                q->link=G->VerticesList[j].adj;    //前插，链入顶点k的边链表
                G->VerticesList[j].adj=q;
                if(d==0)
                {
                    q=(EdgeNode *)malloc(sizeof(EdgeNode));
                    q->dest=j;
                    q->link=G->VerticesList[k].adj;
                    G->VerticesList[k].adj=q;
                }
                i++;
            }
            else
            {
                printf("the edge has exist!\n");
                printf("Please input again!\n");
            }
        }
        else
        {
            printf("False information of vs!\n");
            printf("Please input again!\n");
        }
    }
}
void printALGraph(ALGraph *G,int d)
//输出图
//d为0输出无向图，d为1输出有向图
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
            if(d==0&&p->dest<i)
            {
                continue;
            }
            printf("(%d, %d) ",i,p->dest);
        }
        printf("\n");
    }
}
void DFS_Traversal(ALGraph *G)
//对图G进行深度优先遍历的主过程（递归）
{
    int i;
    int n=NumberOfVertices(G);
    int visited[maxVertices];
    for(i=0;i<n;i++)
    {
        visited[i]=0;
    }
    for(i=0; i<n; i++)
    {
        if(!visited[i])
        {
            printf("从%c开始的一支\n",G->VerticesList[i]);
            DFS_recur(G,i,visited);
            printf("\n");
        }
    }
    printf("\n");
}
void DFS_recur(ALGraph *G,int v,int visited[])
//从顶点位置v出发，以深度优先的次序访问所有可读入的尚未访问过的顶点
//算法中用到一个辅助数组visited，对即访问过的顶点作访问标记
{
    printf("->%c",getvalue(G,v));
    visited[v]=1;
    int w=FirstNeighbor(G,v);
    while(w!=-1)
    {
        if(!visited[w])
        {
            DFS_recur(G,w,visited);
        }
        w=NextNeighbor(G,v,w);
    }
}
void DFS2_Traversal(ALGraph *G)
//对图G进行深度优先遍历的主过程（非递归）
{
    int i;
    int n=G->numVertices;
    int visited[maxVertices];
    for(i=0;i<n;i++)
    {
        visited[i]=0;
    }
    for(i=0;i<n;i++)
    {
        if(!visited[i])
        {
            printf("从%c开始的一支\n",G->VerticesList[i]);
            DFS2(G,i,visited);
            printf("\n");
        }
    }
}
void DFS2(ALGraph *G,int v,int visited[])
//从顶点位置v出发，以深度优先的次序访问所有可读入的尚未访问过的顶点
//算法中用到一个辅助数组visited以及一个数组栈，对即访问过的顶点作访问标记
{
    int stack[100];
    int top=-1;
    EdgeNode *j;
    int n=G->numVertices;
    printf("->%c",G->VerticesList[v]);
    visited[v]=1;
    stack[++top]=v;//将元素i压栈
    while(top!=-1)
    {
        v=stack[top];//取出栈顶元素（相当于当前游标的移动）
                              //压栈后，取栈顶相当于向深处遍历；
                              //弹栈后，取栈顶相当于回到上个结点
        int w=FirstNeighbor(G,v);
        while(w!=-1)
        {
            if(!visited[w])//如果与该节点相邻的结点未被访问
            {
                printf("->%c",G->VerticesList[w]);
                visited[w]=1;
                stack[++top]=w;
                break;//该点入栈,相当于向深处遍历
            }
            w=NextNeighbor(G,v,w);
        }
        if(w==-1)
        {
            top--;//相当于当前节点的所有分支都被遍历过了，于是弹栈
                      //相当于返回上一结点
        }
    }
    printf("\n");
}
void BFS_Traversal(ALGraph *G)
//对图G进行广度优先遍历的主过程（非递归）
{
    int i;
    int visited[maxVertices];
    int n=G->numVertices;
    printf("广度遍历结果：\n");
    for(i=0;i<n;i++)
    {
        visited[i]=0;
    }
    for(i=0;i<n;i++)
    {
        if(!visited[i])
        {
            printf("从%c开始的一支\n",G->VerticesList[i]);
            BFS(G,i,visited);
            printf("\n");
        }
    }
}
void BFS(ALGraph *G, int k,int visited[])
//和树的层序遍历类似
{
    int i,j,h;
    int n=G->numVertices;
    int Queue[100];
    int front=0,rear=0;//简易的队列
    printf("->%c",G->VerticesList[k]);//访问Vk
    visited[k]=1;
    Queue[rear++]=k;//简易的入队操作
    while(front!=rear)
    {//队空时搜索结束
        i=Queue[front++];//简易的出队操作
         int w=FirstNeighbor(G,i);
        while(w!=-1)
        {
            if(!visited[w])
            {
                printf("->%c",G->VerticesList[w]);
                visited[w]=1;
                Queue[rear++]=w;//vj入队
            }
            w=NextNeighbor(G,i,w);
        }
    }
}
//void BFS_Traverse(ALGraph *G)
////算法实现图G的广度优先搜索。其中使用了一个队列vexno。
//{
//    int i,j,w;
//    int n=NumberOfVertices(G);
//    EdgeNode *p;
//    int visited[maxVertices];
//    for(i=0;i<n;i++)
//    {
//        visited[i]=0;
//    }
//    int vexno[maxVertices];
//    int front=0;
//    int rear=0;
//    for(i=0;i<n;i++)
//    {
//        if(!visited[i])
//        {
//            printf("->%c",getvalue(G,i));
//            visited[i]=1;
//            vexno[rear++]=i;
//            while(front<rear)
//            {
//                j=vexno[front++];
//                w=FirstNeighbor(G,j);
//                while(w!=-1)
//                {
//                    if(!visited[w])
//                    {
//                        printf("->%c",getvalue(G,w));
//                        visited[w]=1;
//                        vexno[rear++]=w;
//                    }
//                    w=NextNeighbor(G,j,w);
//                }
//            }
//        }
//    }
//}
int main()
{
    ALGraph G;
    int n,e,d;
    printf("Please input the number of vertices :\n");
    scanf("%d",&n);
    printf("Please input the number of edges :\n");
    scanf("%d",&e);
    printf("Whether the graph is digraph or not:\n");
    scanf("%d",&d);
    createALGraph(&G,n,e,d);
    printALGraph(&G,d);
    printf("The result of the DFS(recur):\n");
    DFS_Traversal(&G);
    printf("The result of the DFS2:\n");
    DFS2_Traversal(&G);
    printf("The result of the BFS:\n");
    BFS_Traversal(&G);
    return 0;
}
