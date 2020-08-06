#include <stdio.h>
#include <stdlib.h>

typedef int SElemType;
typedef struct node
{
    SElemType data;
    struct node *link;
}LinkNode, * LinkStack;

void InitStack(LinkStack *S)
//��ʽջ��ʼ������ջ��ָ��Ϊ��
{
    *S=NULL;
}
int Push(LinkStack *S,SElemType x)
//��ջ����Ԫ��x���뵽��ʽջ��ջ��������ͷ
{
    LinkStack p=(LinkStack)malloc(sizeof(LinkNode));
    p->data=x;
    p->link=*S;
    *S=p;

    return 1;
}
int Pop(LinkStack *S,SElemType *x)
//��ջ����ջ�գ���������0������x��ֵ������
//��ջ���գ���������1����ͨ�����ò���x���ر�ɾջ��Ԫ�ص�ֵ
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
//��ȡջ������ջ���գ�����ͨ�����ò���x����ջ��Ԫ�ص�ֵ
{
    if(*S==NULL)
    {
        return 0;
    }
    *x=(*S)->data;
    return 1;
}
int StackEmpty(LinkStack *S)
//�ж�ջ�Ƿ�Ϊ�գ���ջΪ�գ���������1������������0��
{
    return *S==NULL;
}
int StackSize(LinkStack *S)
//��ջ�ĳ��ȣ�����ջԪ�ظ���
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
        printf("��Ԫ�ؿɳ��ӣ�\n");
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
