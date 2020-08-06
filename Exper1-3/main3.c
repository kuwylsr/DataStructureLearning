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
//���г�ʼ�������ͷָ��Ͷ�βָ���ΪNULL
{
    (*Q).front=(*Q).rear=NULL;
}
int EnQueue(LinkQueue Q,QElemType x)
//�����У�����Ԫ��x���뵽���еĶ�β����β��
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
//�����У�������пգ������˶ӣ���������0�������ò���x��ֵ������
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
//��ȡ��ͷԪ�ص�ֵ��������Ϊ�գ���������0�������ò���x��ֵ������
//�����в�Ϊ�գ���������1���Ҵ����ò���x�ɵõ��˳��Ķ�ͷԪ�ص�ֵ
{
    if((*Q).front==NULL)
    {
        return 0;
    }
    *x=(*Q).front->data;
    return 1;
}
int QueueEmpty(LinkQueue Q)
//�ж϶����Ƿ�Ϊ�գ����п���������1������������0
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
//��ջ����Ԫ��x���뵽��ʽջ��ջ��������ͷ
{
    EnQueue(Q2,x);
}
int Pop(LinkQueue Q1,LinkQueue Q2,QElemType *x)
//��ջ����ջ�գ���������0������x��ֵ������
//��ջ���գ���������1����ͨ�����ò���x���ر�ɾջ��Ԫ�ص�ֵ
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
//��ȡջ������ջ���գ�����ͨ�����ò���x����ջ��Ԫ�ص�ֵ
{
   GetFront(Q2,x);
}
int StackEmpty(LinkQueue Q2)
//�ж�ջ�Ƿ�Ϊ�գ���ջΪ�գ���������1������������0��
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
