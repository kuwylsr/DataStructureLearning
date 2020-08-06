#include <stdio.h>
#include <stdlib.h>
#define heapSize 40
//在优先级队列的各种实现中，堆是最高效的一种数据结构
//堆是一种特殊的完全二叉树



typedef struct node  //堆中元素的数据类型
{
    int title;    //任务标号
    int pvalue; //任务的优先级
} HElemType;

typedef struct     //大根堆的结构定义
{
    HElemType elem[heapSize]; //大根堆的元素存储数组
    int curSize;   //大根堆当前元素个数
} maxHeap;

//队列数据类型的定义
typedef int  QElemType;
typedef struct Node
{
    QElemType data;
    struct Node *Link;
} LinkNode;
typedef struct
{
    LinkNode *front;
    LinkNode *rear;
} LinkQueue1,*LinkQueue;

void creatMaxHeap(maxHeap *H,int n);
//从一个输入序列逐步构建小根堆的算法
void siftDown(maxHeap *H,int strat,int m);
//大根堆自顶向下"筛选"调整算法
int Remove(maxHeap *H,HElemType *x);
//大根堆的删除算法
void InitQueue(LinkQueue Q);
//队列初始化：令队头指针和队尾指针均为NULL
int EnQueue(LinkQueue Q,QElemType x);
//进队列：将新元素x插入到队列的队尾（链尾）
int DeQueue (LinkQueue Q,QElemType *x);
//出队列：如果队列空，不能退队，函数返回0；且引用参数x的值不可用
int QueueEmpty(LinkQueue Q);
//判断队列是否为空：队列空则函数返回1，否则函数返回0
void Readfile(maxHeap *H);
//从文件中读取数据
int main()
{
    maxHeap H;
    H.curSize=0;
    LinkQueue Q=(LinkQueue)malloc(sizeof(LinkQueue1));
    InitQueue(Q);
    Readfile(&H);
    HElemType p;
    QElemType sth;
    creatMaxHeap(&H,5);
    //将大根堆中依次删除结点，删除的结点的任务号入队
    while(H.curSize!=0)
    {
        Remove(&H,&p);
        EnQueue(Q,p.title);
    }
    //将任务号出队，即执行任务的顺序
    while(QueueEmpty(Q)!=1)
    {
        DeQueue(Q,&sth);
        printf("%d",sth);
    }
    return 0;
}
void creatMaxHeap(maxHeap *H,int n)
//从一个输入序列逐步构建大根堆的算法
//算法将一个数组从局部到整体，自下向上调整为大根堆
{
    int i;
    (*H).curSize=n; //复制堆数组，建立当前大小
    for(i=((*H).curSize-2)/2; i>=0; i--) //自底向上逐步扩大形成堆
    {
        siftDown(H,i,(*H).curSize-1); //局部自上向下筛选
    }
}
void siftDown(maxHeap *H,int strat,int m)
//大根堆自顶向下"筛选"调整算法
//传参传进来一个 子树的根结点标号，然后自顶向下"筛选"调整
{
    int i=strat,j;
    HElemType temp=(*H).elem[i];
    for(j=2*i+1; j<=m; j=2*j+1)
        //2*i+1是根结点的左儿子，2*i+2是根结点的右儿子。先比较根结点的两个儿子，再将筛选过的儿子与根结点比较
    {
        if(j<m&&(*H).elem[j].pvalue<(*H).elem[j+1].pvalue)
            //首先比较根结点的两个左右儿子的优先级大小将j的标号指向优先级高的结点
        {
            j++;
        }
        else if(j<m&&((*H).elem[j].pvalue==(*H).elem[j+1].pvalue)&&(*H).elem[j].title>(*H).elem[j+1].title)
            //如果根结点的两个左右儿子的优先级相同，则将标号指向任务号小的结点
            j++;
        if(temp.pvalue>(*H).elem[j].pvalue)
            //如果筛选过的儿子结点的优先级小于根结点的优先级，则不做处理
        {
            break;
        }
        else if(temp.pvalue==(*H).elem[j].pvalue&&(temp.title<(*H).elem[j].title))
            //如果筛选过的儿子结点的优先级等于根结点的优先级且其标号大于根结点的标号，则不做处理
            break;
        else
            //当筛选过的儿子结点的优先级大于根结点的优先级或者优先级相同但其标号小于根结点标号，则将其互换位置
        {
            (*H).elem[i]=(*H).elem[j];
            i=j;
        }
    }
    (*H).elem[i]=temp;
}
int Remove(maxHeap *H,HElemType *x)
//大根堆的删除算法
{
    if((*H).curSize==0) //堆空，返回0
    {
        return 0;
    }
    *x=(*H).elem[0];
    (*H).elem[0]=(*H).elem[(*H).curSize-1]; //将最后的元素填到根结点
    (*H).curSize--; //将最后一个结点删除
    siftDown(H,0,(*H).curSize-1); //调整堆，使其成为大根堆
    return 1;
}
void InitQueue(LinkQueue Q)
//队列初始化：令队头指针和队尾指针均为NULL
{
    (*Q).front=(*Q).rear=NULL;
}
int EnQueue(LinkQueue Q,QElemType x)
//进队列：将新元素x插入到队列的队尾（链尾）
{

    LinkNode *s=(LinkNode *)malloc(sizeof(LinkNode));
    s->data=x;
    s->Link=NULL;
    if((*Q).rear==NULL)
    {
        (*Q).front=(*Q).rear=s;
    }
    else
    {
        (*Q).rear->Link=s;
        (*Q).rear=s;
    }
}
int DeQueue (LinkQueue Q,QElemType *x)
//出队列：如果队列空，不能退队，函数返回0；且引用参数x的值不可用
{
    if((*Q).front==NULL)
    {
        return 0;
    }
    LinkNode *p=(*Q).front;
    *x=p->data;
    (*Q).front=p->Link;
    free(p);
    if((*Q).front==NULL)
    {
        (*Q).rear=NULL;
    }
    return 1;
}
int QueueEmpty(LinkQueue Q)
//判断队列是否为空：队列空则函数返回1，否则函数返回0
{
    return (*Q).front==NULL;
}
void Readfile(maxHeap *H)
{
    FILE *fp;
    int i;
    fp=fopen("Data.txt","r");
    if(fp==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    for(i=0; !feof(fp); i++)
    {
        fscanf(fp,"%d",&((*H).elem[i].title));
        fscanf(fp,"%d",&((*H).elem[i].pvalue));
    }
    fclose(fp);
}
