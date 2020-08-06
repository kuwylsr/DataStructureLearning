#include <stdio.h>
#include <stdlib.h>

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
int GetFront(LinkQueue Q,QElemType *x)
//读取队头元素的值：若队列为空，则函数返回0，且引用参数x的值不可用
//若队列不为空，函数返回1，且从引用参数x可得到退出的队头元素的值
{
    if((*Q).front==NULL)
    {
        return 0;
    }
    *x=(*Q).front->data;
    return 1;
}
int QueueEmpty(LinkQueue Q)
//判断队列是否为空：队列空则函数返回1，否则函数返回0
{
    return (*Q).front==NULL;
}
int QueueSize(LinkQueue Q)
{
    LinkNode *p=(*Q).front;
    int k=0;
    while(p!=NULL)
    {
        p=p->Link;
        k++;
    }
    return k;
}
void InitStack(LinkQueue Q2)
{
    InitQueue(Q2);
}
int Push(LinkQueue Q2,QElemType x)
//进栈：将元素x插入到链式栈的栈顶，及链头
{
    EnQueue(Q2,x);
}
int Pop(LinkQueue Q1,LinkQueue Q2,QElemType *x)
//退栈：若栈空，函数返回0，参数x的值不可用
//若栈不空，则函数返回1，并通过引用参数x返回被删栈顶元素的值
{
    int y;
    while((*Q2).front!=(*Q2).rear)
    {
        DeQueue(Q2,x);
        EnQueue(Q1,*x);
    }
    DeQueue(Q2,x);
    y=*x;
    while((*Q1).front!=NULL)
    {
        DeQueue(Q1,x);
        EnQueue(Q2,*x);
    }
    return y;
}
int GetTop(LinkQueue Q2,QElemType *x)
//读取栈顶：若栈不空，函数通过引用参数x返回栈顶元素的值
{
   GetFront(Q2,x);
}
int StackEmpty(LinkQueue Q2)
//判断栈是否为空：若栈为空，则函数返回1，否则函数返回0；
{
    return (*Q2).front==NULL;
}
int StackSize(LinkQueue Q2)
{
    QueueSize(Q2);
}
int main()
{
    int x1,x2,x3,x4;
    LinkQueue Q1=(LinkQueue)malloc(sizeof(LinkQueue1));
    LinkQueue Q2=(LinkQueue)malloc(sizeof(LinkQueue1));
    InitStack(Q2);
    InitStack(Q1);
    Push(Q2,6);
    Push(Q2,0);
    Push(Q2,3);
    printf("%d\n",StackSize(Q2));
    x1=Pop(Q1,Q2,&x1);
    x2=Pop(Q1,Q2,&x2);
    GetTop(Q2,&x4);
//    x3=Pop(Q1,Q2,&x3);
    printf("%d\n%d\n%d\n",x1,x2,x4);
    printf("%d",StackEmpty(Q2));
    return 0;
}
