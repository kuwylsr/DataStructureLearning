#include <stdio.h>
#include <stdlib.h>
#define maxVertices 30 //ͼ����󶨵���Ŀ
#define maxEdges 450   //ͼ�����ߵ���Ŀ
#define impossibleValue '#'



typedef int Weight;
typedef char VType; //�������ݵ���������
typedef struct
{
    int v1,v2;
    Weight key;
}Edge;

typedef struct Enode //�߽��Ľṹ����
{
    int dest;                  //�ߵ���һ������λ��
    Weight cost;
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
void createALGraph (ALGraph *G)
//�㷨����n����������ݺ�e���ߵ���Ϣ������ͼG���ڽӱ��ʾ
//dΪ0����������ͼ��dΪ1��������ͼ
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
    G->numVertices=11;  //ͼ�Ķ�����Ŀ
    G->numEdges=12;             //ͼ�ıߵ���Ŀ
    for(i=0;i<G->numVertices;i++)  //Ϊ�����ֵ�����������
    {
        fscanf(fp," %c",&val);
        G->VerticesList[i].data=val;
        G->VerticesList[i].adj=NULL;
    }
    i=0;
    while(i<G->numEdges)  //����������ı�����
    {
        fscanf(fp," %c,%c,%d",&e1,&e2,&c);
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
                q->cost=c;
                q->link=G->VerticesList[j].adj;    //ǰ�壬���붥��k�ı�����
                G->VerticesList[j].adj=q;
                i++;
            }
        }
    }
}
void printALGraph(ALGraph *G)
//���ͼ
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
//�㷨�Դ�ȨͼG����ؼ�·��������cp���عؼ����nΪ�ؼ������
{
    int j,i,k,m=-1,u,v,top=-1;
    Weight w;
    EdgeNode *p;
    Edge ed;
    int ind[maxVertices];  //�������
    for(i=0;i<G->numVertices;i++)
    {
        ind[i]=0;
    }
    for(i=0;i<G->numVertices;i++)
    {
        for(p=G->VerticesList[i].adj;p!=NULL;p=p->link)
        {
            ind[p->dest]++;    //ͳ�Ƹ��������
        }
    }
    Weight Ve[maxVertices],Vl[maxVertices];  //���¼��������ٿ�ʼʱ��
    Weight Ae[maxEdges],Al[maxEdges];         //����������ٿ�ʼʱ��
    for(i=0;i<G->numVertices;i++)
    {
        Ve[i]=0;
    }

    for(i=0;i<G->numVertices;i++)     //�������Ϊ0�Ķ����ջ
    {
        if(!ind[i])
        {
            ind[i]=top;
            top=i;
        }
    }

    while(top!=-1)     //�������Ve[]
    {
        u=top;
        top=ind[top];     //��ջu
        ind[u]=m;              //��������
        m=u;

        for(p=G->VerticesList[u].adj;p!=NULL;p=p->link)
        {
            w=p->cost;
            j=p->dest;
            if(Ve[u]+w>Ve[j])       //����Ve
            {
                Ve[j]=Ve[u]+w;
            }
            if(--ind[j]==0)   //�ڽӶ�����ȼ�1
            {
                ind[j]=top;   //������ȼ���0��ջ
                top=j;
            }
        }
    }
    for(i=0;i<G->numVertices;i++)
    {
        Vl[i]=Ve[m];
    }
    while(m!=-1)            //�������Vl[]
    {
        v=ind[m];           //����������
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
    for(i=0;i<G->numVertices;i++)           //������Ae��Al
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
    while((*n)<k)       //���㲢����ؼ��
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
