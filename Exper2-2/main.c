#include <stdio.h>
#include <stdlib.h>
#define Max_tree 50
#define Stacksize 30
//����ջ�Ĵ�С
#define Queuesize 30
//�������д�С

typedef char TElemType;
typedef struct node
{
    TElemType data;
    struct node *lchild,*rchild;
}BiTNode,BiTNode1,* BinTree;
typedef BiTNode* SElemType;
//����ջ��Ԫ������
typedef BiTNode1* QElemType;
//�������е�Ԫ������
void createBinTree_Pre(BinTree *T,TElemType pre[],int *n);
//���ݶ���������������������������
void PreOrder_recur(BiTNode *BT);
//�����������BTΪ�����Ķ������ݹ��㷨
void InOrder_recur(BiTNode *BT);
//�����������BTΪ�����Ķ������ĵݹ��㷨
void PostOrder_recur(BiTNode *BT);
//�����������BTΪ�����Ķ������ĵݹ��㷨
void PreOrder(BiTNode *BT);
//�����������BTΪ�����Ķ������ķǵݹ��㷨
void InOrder(BiTNode *BT);
//�����������BTΪ�����Ķ������ķǵݹ��㷨
void PostOrder(BiTNode *BT);
//�����������BTΪ�����Ķ������ķǵݹ��㷨
void LevelOrder(BiTNode *BT);
//�����������BTΪ�����Ķ������㷨
int main()
{
    BinTree root;
    int n=0;
    TElemType pre[Max_tree];
    printf("��������������(�ս��Ϊ#)!\n");
    gets(pre);
    createBinTree_Pre(&root,pre,&n);
    printf("�õݹ��㷨���������������");
    PreOrder_recur(root);
    printf("\n");
    printf("�õݹ��㷨���������������");
    InOrder_recur(root);
    printf("\n");
    printf("�õݹ��㷨���������������");
    PostOrder_recur(root);
    printf("\n");
    printf("�÷ǵݹ��㷨���������������");
    PreOrder(root);
    printf("\n");
    printf("�÷ǵݹ��㷨���������������");
    InOrder(root);
    printf("\n");
    printf("�÷ǵݹ��㷨���������������");
    PostOrder(root);
    printf("\n");
     printf("�ò��������������");
    LevelOrder(root);
    printf("\n");
    return 0;
}
void createBinTree_Pre(BinTree *T,TElemType pre[],int *n)
//�Եݹ�ķ�ʽ������������pre[]���������У��ԡ�;"�������ս��ı�ʶΪ��#��
//���ò���n��ʼ����ǰ��ֵ0���˳���n������ͳ��
{
    TElemType ch=pre[*n];
//    ����һ����������
    (*n)++;
    if(ch==';')
//    �����������
    {
        return;
    }
    if(ch!='#')
//        �����ǿ�����
    {
        (*T)=(BinTree)malloc(sizeof(BiTNode));
//        �������ڵ�
        (*T)->data=ch;
        createBinTree_Pre(&((*T)->lchild),pre,n);
//        �ݹ齨��������
        createBinTree_Pre(&((*T)->rchild),pre,n);
//        �ݹ齨��������
    }
    else
//    ������������
    {
        (*T)=NULL;
    }
}
void PreOrder_recur(BiTNode *BT)
//�����������BTΪ�����Ķ������ݹ��㷨
{
    if(BT!=NULL)
//    ����BT=NULL�ǵݹ�Ľ�������
    {
    printf("%c ",BT->data);
//    ���ʸ����
    PreOrder_recur(BT->lchild);
//    �����������������
    PreOrder_recur(BT->rchild);
//    �����������������
    }
}
void InOrder_recur(BiTNode *BT)
//�����������BTΪ�����Ķ������ĵݹ��㷨
{
    if(BT !=NULL)
//    ����BT=NULL�ǵݹ�Ľ�������
    {
        InOrder_recur(BT->lchild);
//    �����������������
        printf("%c ",BT->data);
//    ���ʸ����
        InOrder_recur(BT->rchild);
//    �����������������
    }
}
void PostOrder_recur(BiTNode *BT)
//�����������BTΪ�����Ķ������ĵݹ��㷨
{
    if(BT!=NULL)
//    ����BT=NULL�ǵݹ�Ľ�������
    {
        PostOrder_recur(BT->lchild);
//    �����������������
        PostOrder_recur(BT->rchild);
//    �����������������
        printf("%c ",BT->data);
//    ���ʸ����
    }
}
void PreOrder(BiTNode *BT)
//�����������BTΪ�����Ķ������ķǵݹ��㷨
//�˴�ѡ��˳��ջ�ľ�̬�洢�ṹ
{
    SElemType S[Stacksize];
    int top=-1;
//    ��������ջ����ʼ��
    BiTNode *p=BT;
//    p�Ǳ���ָ�룬�Ӹ��ڵ㿪ʼ
    do
    {
        while(p!=NULL)
//        ����ָ���������Ů���
        {
            printf("%c ",p->data);
//            ����
            S[++top]=p;
            p=p->lchild;
//            һ·��һ·��ջ�������½������ȥ
        }
        if(top>-1)
//        ջ����ʱ��ջ
        {
            p=S[top--];
//            ��ջ����ջ��㼴Ϊ�������ĸ����
            p=p->rchild;
//            ����ָ���������Ů���
        }
    }while(p!=NULL||top>-1);
}
void InOrder(BiTNode *BT)
//�����������BTΪ�����Ķ������ķǵݹ��㷨
{
    SElemType S[Stacksize];
    int top=-1;
//    ��������ջ����ʼ��
    BiTNode *p=BT;
//    p�Ǳ���ָ�룬�Ӹ��ڵ㿪ʼ
    do
    {
        while(p!=NULL)
//        ����ָ���������Ů���
        {
            S[++top]=p;
            p=p->lchild;
//            һ·��һ·��ջ�������½������ȥ
        }
        if(top>-1)
//        ջ����ʱ��ջ
        {
            p=S[top--];
//            ��ջ����ջ��㼴Ϊ�������ĸ����
            printf("%c ",p->data);
//            ����
            p=p->rchild;
//            ����ָ���������Ů���
        }
    }while(p!=NULL||top>-1);
}
void PostOrder(BiTNode *BT)
//�����������BTΪ�����Ķ������ķǵݹ��㷨
{
    SElemType S[Stacksize];
    int top=-1;
//    ��������ջ����ʼ��
    BiTNode *p=BT;
    BiTNode *pre=NULL;
//    p�Ǳ���ָ�룬pre��ǰ��ָ��
    do
    {
        while(p!=NULL)
//        ����ָ���������Ů���
        {
            S[++top]=p;
            p=p->lchild;
//            һ·��һ·��ջ�������½������ȥ
        }
        if(top>-1)
        {
            p=S[top];
//            ��p����ջ��Ԫ��
            if(p->rchild!=NULL&&p->rchild!=pre)
//            p������Ů��δ���ʹ�
            {
                p=p->rchild;
            }
            else
            {
                printf("%c ",p->data);
//                ����
                pre=p;
                p=NULL;
//                ����շ��ʹ��Ľ��
                top--;

            }
        }
    }while(p!=NULL||top!=-1);
}
void LevelOrder(BiTNode *BT)
//�����������BTΪ�����Ķ������㷨
{
    QElemType Q[Queuesize];
    int rear=0,front=0;
//    �����������в���ʼ��
    BiTNode *p=BT;
//    p�Ǳ���ָ�룬�Ӷ�β��ʼ
    Q[rear++]=p;
    while(rear!=front)
    {
        p=Q[front];
        front=(front+1)%Queuesize;
//        �Ӷ������˳�һ�����
        printf("%c ",p->data);
//        ����
        if(p->lchild!=NULL)
//        ��������Ů������
        {
            Q[rear]=p->lchild;
            rear=(rear+1)%Queuesize;
        }
        if(p->rchild!=NULL)
//        ��������Ů������
        {
            Q[rear]=p->rchild;
            rear=(rear+1)%Queuesize;
        }
    }
}
//ABC##D#E###;
//ABDH##I##E##CF#J##G##;
