#include <stdio.h>
#include <stdlib.h>

typedef int SElemType;
typedef struct node
{
    SElemType data;
    struct node *link;
}LinkNode, * LinkStack;

void InitStack(LinkStack *S)
//链式栈初始化：置栈顶指针为空
{
    *S=NULL;
}
int Push(LinkStack *S,SElemType x)
//进栈：将元素x插入到链式栈的栈顶，及链头
{
    LinkStack p=(LinkStack)malloc(sizeof(LinkNode));
    p->data=x;
    p->link=*S;
    *S=p;

    return 1;
}
int Pop(LinkStack *S,SElemType *x)
//退栈：若栈空，函数返回0，参数x的值不可用
//若栈不空，则函数返回1，并通过引用参数x返回被删栈顶元素的值
{
    if(*S==NULL)
    {
        return 0;
    }
    LinkNode *p=*S;
    *x=p->data;
    *S=p->link;
    free(p);
    return 1;
}
int GetTop(LinkStack *S,SElemType *x)
//读取栈顶：若栈不空，函数通过引用参数x返回栈顶元素的值
{
    if(*S==NULL)
    {
        return 0;
    }
    *x=(*S)->data;
    return 1;
}
int StackEmpty(LinkStack *S)
//判断栈是否为空：若栈为空，则函数返回1，否则函数返回0；
{
    return *S==NULL;
}
int StackSize(LinkStack *S)
//求栈的长度；计算栈元素个数
{
    LinkNode *p=*S;
    int k=0;
    while(p!=NULL)
    {
        p=p->link;
        k++;
    }
    return k;
}
void InitQueue(LinkStack *S1,LinkStack *S2)
{
   InitStack(S1);
   InitStack(S2);
}
int EnQueue(LinkStack *S1,SElemType x)
{
    Push(S1,x);
}
int DeQueue (LinkStack *S1,LinkStack *S2,SElemType  *x)
{
    while((*S1)!=NULL)
    {
        Pop(S1,x);
        Push(S2,*x);
    }
    if(*S2==NULL)
    {
        printf("无元素可出队！\n");
    }
    Pop(S2,x);
    if(*S2==NULL)
    {
        InitQueue(S1,S2);
    }
}
int GetFront(LinkStack *S1,LinkStack *S2,SElemType  *x)
{
    GetTop(S2,x);
}
int QueueEmpty(LinkStack *S2,LinkStack *S1)
{
    StackEmpty(S2);
    StackEmpty(S1);
//    return (*Q).front==NULL;
}
int QueueSize(LinkStack *S2)
{
    StackSize(S2);
}
int main()
{
    int x1,x2,x3,x4;
    LinkStack S1;
    LinkStack S2;
    InitQueue(&S1,&S2);
    EnQueue(&S1,6);
    EnQueue(&S1,0);
    EnQueue(&S1,3);
    printf("%d\n",QueueSize(&S1));
    DeQueue(&S1,&S2,&x1);
    DeQueue(&S1,&S2,&x2);
    GetFront(&S1,&S2,&x4);
    DeQueue(&S1,&S2,&x3);
    printf("%d\n%d\n%d\n",x1,x2,x4);
    printf("%d",QueueEmpty(&S2,&S1));
    return 0;
}
