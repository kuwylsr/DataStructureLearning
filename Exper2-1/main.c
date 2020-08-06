#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define Max_tree 50

typedef char TElemType;
typedef struct node1
{
    TElemType data;
    struct node *lchild,*rchild;
}BiTNode,* BinTree;
struct node
{
    int lc;
    int rc;
    char ch;
};
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
void createBinTree_pre_In_recur(BinTree *t,TElemType pre[],TElemType in[],int s1,int t1,int s2,int t2);
//�ɶ�������ǰ����������й����������ĵݹ��㷨
int check(TElemType pre[],TElemType in[]);
//������кϷ���
int main()
{
    int m;
    TElemType pre[Max_tree],in[Max_tree];
    do
    {
        printf("��������ȷ�����У�\n");
        printf("������һ��������������:\n");
        gets(pre);
        printf("������һ��������������:\n");
        gets(in);
    }while(check(pre,in)==0);
    BinTree root;
    int s1=0,t1=strlen(pre)-1,s2=0,t2=strlen(in)-1;
    createBinTree_pre_In_recur(&root,pre,in,s1,t1,s2,t2);
    printf("���������������");
    PreOrder_recur(root);
    printf("\n");
    printf("���������������");
    InOrder_recur(root);
    printf("\n");
    printf("���������������");
    PostOrder_recur(root);
    printf("\n");
    return 0;
}
void createBinTree_pre_In_recur(BinTree *t,TElemType pre[],TElemType in[],int s1,int t1,int s2,int t2)
//�ɶ�������ǰ����������й���������
{
    if(s1<=t1)
    {
        int i;
        *t=(BinTree)malloc(sizeof(BiTNode));
//        ���������
        (*t)->data=pre[s1];
        (*t)->lchild=NULL;
        (*t)->rchild=NULL;
        for(i=s2; i<=t2; i++)
        {
            if(in[i]==pre[s1])
//            �����������в��Ҹ�
            {
                break;
            }
        }
            createBinTree_pre_In_recur(&((*t)->lchild),pre,in,s1+1,s1+i-s2,s2,i-1);
            createBinTree_pre_In_recur(&((*t)->rchild),pre,in,s1+i-s2+1,t1,i+1,t2);
    }
}
int check(TElemType pre[],TElemType in[])
//������кϷ���
{
    int i,j,k=0;
    if(strlen(pre)!=strlen(in))
        return 0;
    else
    {
        for(i=0; i<strlen(pre)-1; i++)
        {
            for(j=0; j<strlen(in); j++)
            {
                if(pre[i]==in[j])
                    break;
                if(j==strlen(in)-1)
                {
                    k=1;
                    return 0;
                }
            }
        }
        if(k==0)
            return 1;
    }
}
//ABHFDECKG
//HBDFAEKCG
