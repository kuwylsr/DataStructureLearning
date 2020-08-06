#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#define Max_tree 50

typedef char TElemType;
typedef struct node
{
    TElemType data;
    struct node *lchild,*rchild;
}BiTNode,* BinTree;
typedef struct Node
{
    int lc;
    int rc;
    char ch;
}Inm;
typedef struct
{
    char Data[Max_tree];
    int top;
}Stack;
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
int createBinTree_pre_In(TElemType pre[],Inm in[]);
//�ɶ�������ǰ����������й����������ķǵݹ��㷨
int check(TElemType pre[],TElemType in[]);
//������кϷ���
int i=0;
int main()
{
    int j,root,k;
    int m=1;
    TElemType pre[Max_tree];
//    �洢ǰ������
    Inm in[Max_tree];
//    �ṹ�������������洢��������
    while(m==1)
    {
        printf("������һ����ȷ���У�\n");
        printf("������һ��������������:\n");
        gets(pre);
        printf("������һ��������������:\n");
        do
        {
            scanf("%c",&in[i].ch);
            i++;
        }
        while(in[i-1].ch!='\n');
        m=check(pre,in);
    }
     for(k=0;k<i-1;k++)
    {
        in[k].lc=-1;
        in[k].rc=-1;
    }
//    ��ʼ��in[]
    BiTNode *C[i-1];
//    ����ָ����������͵�ָ������
    root=createBinTree_pre_In(pre,in);

//    ���þ�̬��������洢�������ý���ʾ����ָ�������ָ���������γ���
    for(j=0;j<i-1;j++)
//    Ϊ������ÿ��ָ�뿪�ٿռ䲢���ݾ�̬���������������ֵ
    {
        C[j]=(BinTree)malloc(sizeof(BiTNode));
        C[j]->data=in[j].ch;
    }

//    ��������ÿ�������ݾ�̬������������
    for(j=0;j<i-1;j++)
    {
        if(in[j].lc==-1)
        {
            C[j]->lchild=NULL;
        }
        else
        {
             C[j]->lchild=C[in[j].lc];
        }
        if(in[j].rc==-1)
        {
            C[j]->rchild=NULL;
        }
       else
       {
           C[j]->rchild=C[in[j].rc];
       }
    }
    printf("���������������");
    PreOrder_recur(C[root]);
    printf("\n");
    printf("���������������");
    InOrder_recur(C[root]);
    printf("\n");
    printf("���������������");
    PostOrder_recur(C[root]);
    printf("\n");
    return 0;
}
int createBinTree_pre_In(TElemType pre[],Inm in[])
//�ɶ�������ǰ����������й����������ķǵݹ��㷨
{
    Stack S;
    int i1,j,k,root;
    S.top=-1;
//    ��ʼ��ջ
    for(i1=0;i1<i-1;i1++)
    {
        j=0;
        while(in[j].ch!=pre[i1])
//        �ҵ���������Ԫ�ض�Ӧ���������е��±�
        {
            j++;
        }
        if(i1==0)
//        �ҵ����ڵ�������in[]�ж�Ӧ���±�
        {
            root=j;
        }
        if(S.top==-1)
        {
            S.top++;
            S.Data[S.top]=j;
        }
        else
        {
            if(j<S.Data[S.top])
//            ���±��ջ��Ԫ��С��ѹջ
            {
                in[S.Data[S.top]].lc=j;
//                ���ӵ�������
                S.top++;
                S.Data[S.top]=j;
            }
            else
            {
                while(j>S.Data[S.top]&&S.top!=-1)
//                ���±��ջ��Ԫ�ش󣬵�����ֱ��С�ڵ���Ϊֹ
                {
                    k=S.Data[S.top];
//                    ��¼�±�
                    S.top--;
                }
                in[k].rc=j;
//                ���ӵ�������
                S.top++;
                S.Data[S.top]=j;
            }
        }
    }
    return root;
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
