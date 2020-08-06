#include <stdio.h>
#include <stdlib.h>
#define maxVertices 30 //ͼ����󶨵���Ŀ
#define maxEdges 450   //ͼ�����ߵ���Ŀ

#define impossibleValue '#'

typedef char VType; //�������ݵ���������
typedef struct Enode //�߽��Ľṹ����
{
    int dest;                  //�ߵ���һ������λ��
    struct Enode *link; //��һ������ָ��
}EdgeNode;
typedef struct Vnode //����ṹ�Ķ���
{
    VType data;             //���������
    struct Enode *adj;   //�������ͷָ��
}VertexNode;
typedef struct    //ͼ�Ķ���
{
    VertexNode VerticesList[maxVertices];  //��������������ͷ��㣩
    int numVertices;    //ͼ��ʵ�ʶ���ĸ���
    int numEdges;            //ͼ��ʵ�ʱߵ�����
}ALGraph;
void getVertexPos(ALGraph *G,VType v,int *x)
//���ݶ����ֵv���Ҷ�����š�
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
//��������ͼ�е�ǰ���еĶ������
{
    return G->numVertices;
}
int NumberOfEdges(ALGraph *G)
//��������ͼ�е�ǰ���еı߸���
{
    return G->numEdges;
}
int FirstNeighbor(ALGraph *G,int v)
//��������v�ĵ�һ���ڽӶ��㣬����Ҳ����򷵻غ���-1
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
//��������v���ڽӶ���w����һ���ڽӶ��㣬����Ҳ����򷵻غ���-1
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
//ȡ������v������ֵ
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
//�㷨����n����������ݺ�e���ߵ���Ϣ������ͼG���ڽӱ��ʾ
//dΪ0����������ͼ��dΪ1��������ͼ
{
    int i,j,k;
    VType val,e1,e2;
    EdgeNode *q,*p;
    G->numVertices=n;  //ͼ�Ķ�����Ŀ
    G->numEdges=e;             //ͼ�ıߵ���Ŀ
    printf("Please input the value of vertices:\n");
    for(i=0;i<G->numVertices;i++)  //Ϊ�����ֵ�����������
    {
        scanf(" %c",&val);
        G->VerticesList[i].data=val;
        G->VerticesList[i].adj=NULL;
    }
    i=0;
    while(i<G->numEdges)  //����������ı�����
    {
        printf("Input the one edges :\n");
        scanf(" %c,%c",&e1,&e2);
        getVertexPos(G,e1,&j);
        getVertexPos(G,e2,&k);
        if(j!=-1&&k!=-1)
        {
            p=G->VerticesList[j].adj;         //����j�ı�����ͷָ��
            while(p!=NULL&&p->dest!=k)
            {
                p=p->link;
            }
            if(p==NULL)       //ͼ��û���رߣ������±�
            {
                q=(EdgeNode *)malloc(sizeof(EdgeNode));
                q->dest=k;
                q->link=G->VerticesList[j].adj;    //ǰ�壬���붥��k�ı�����
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
//���ͼ
//dΪ0�������ͼ��dΪ1�������ͼ
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
//��ͼG����������ȱ����������̣��ݹ飩
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
            printf("��%c��ʼ��һ֧\n",G->VerticesList[i]);
            DFS_recur(G,i,visited);
            printf("\n");
        }
    }
    printf("\n");
}
void DFS_recur(ALGraph *G,int v,int visited[])
//�Ӷ���λ��v��������������ȵĴ���������пɶ������δ���ʹ��Ķ���
//�㷨���õ�һ����������visited���Լ����ʹ��Ķ��������ʱ��
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
//��ͼG����������ȱ����������̣��ǵݹ飩
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
            printf("��%c��ʼ��һ֧\n",G->VerticesList[i]);
            DFS2(G,i,visited);
            printf("\n");
        }
    }
}
void DFS2(ALGraph *G,int v,int visited[])
//�Ӷ���λ��v��������������ȵĴ���������пɶ������δ���ʹ��Ķ���
//�㷨���õ�һ����������visited�Լ�һ������ջ���Լ����ʹ��Ķ��������ʱ��
{
    int stack[100];
    int top=-1;
    EdgeNode *j;
    int n=G->numVertices;
    printf("->%c",G->VerticesList[v]);
    visited[v]=1;
    stack[++top]=v;//��Ԫ��iѹջ
    while(top!=-1)
    {
        v=stack[top];//ȡ��ջ��Ԫ�أ��൱�ڵ�ǰ�α���ƶ���
                              //ѹջ��ȡջ���൱�����������
                              //��ջ��ȡջ���൱�ڻص��ϸ����
        int w=FirstNeighbor(G,v);
        while(w!=-1)
        {
            if(!visited[w])//�����ýڵ����ڵĽ��δ������
            {
                printf("->%c",G->VerticesList[w]);
                visited[w]=1;
                stack[++top]=w;
                break;//�õ���ջ,�൱���������
            }
            w=NextNeighbor(G,v,w);
        }
        if(w==-1)
        {
            top--;//�൱�ڵ�ǰ�ڵ�����з�֧�����������ˣ����ǵ�ջ
                      //�൱�ڷ�����һ���
        }
    }
    printf("\n");
}
void BFS_Traversal(ALGraph *G)
//��ͼG���й�����ȱ����������̣��ǵݹ飩
{
    int i;
    int visited[maxVertices];
    int n=G->numVertices;
    printf("��ȱ��������\n");
    for(i=0;i<n;i++)
    {
        visited[i]=0;
    }
    for(i=0;i<n;i++)
    {
        if(!visited[i])
        {
            printf("��%c��ʼ��һ֧\n",G->VerticesList[i]);
            BFS(G,i,visited);
            printf("\n");
        }
    }
}
void BFS(ALGraph *G, int k,int visited[])
//�����Ĳ����������
{
    int i,j,h;
    int n=G->numVertices;
    int Queue[100];
    int front=0,rear=0;//���׵Ķ���
    printf("->%c",G->VerticesList[k]);//����Vk
    visited[k]=1;
    Queue[rear++]=k;//���׵���Ӳ���
    while(front!=rear)
    {//�ӿ�ʱ��������
        i=Queue[front++];//���׵ĳ��Ӳ���
         int w=FirstNeighbor(G,i);
        while(w!=-1)
        {
            if(!visited[w])
            {
                printf("->%c",G->VerticesList[w]);
                visited[w]=1;
                Queue[rear++]=w;//vj���
            }
            w=NextNeighbor(G,i,w);
        }
    }
}
//void BFS_Traverse(ALGraph *G)
////�㷨ʵ��ͼG�Ĺ����������������ʹ����һ������vexno��
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
