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
//按先序遍历以BT为树根的二叉树递归算法
{
    if(BT!=NULL)
//    空树BT=NULL是递归的结束条件
    {
    printf("%c ",BT->data);
//    访问根结点
    PreOrder_recur(BT->lchild);
//    先序遍历根的左子树
    PreOrder_recur(BT->rchild);
//    先序遍历跟的右子树
    }
}
void InOrder_recur(BiTNode *BT)
//按中序遍历以BT为树根的二叉树的递归算法
{
    if(BT !=NULL)
//    空树BT=NULL是递归的结束条件
    {
        InOrder_recur(BT->lchild);
//    中序遍历根的左子树
        printf("%c ",BT->data);
//    访问根结点
        InOrder_recur(BT->rchild);
//    中序遍历跟的右子树
    }
}
void PostOrder_recur(BiTNode *BT)
//按后序遍历以BT为树根的二叉树的递归算法
{
    if(BT!=NULL)
//    空树BT=NULL是递归的结束条件
    {
        PostOrder_recur(BT->lchild);
//    后序遍历根的左子树
        PostOrder_recur(BT->rchild);
//    后序遍历跟的右子树
        printf("%c ",BT->data);
//    访问根结点
    }
}
void createBinTree_pre_In_recur(BinTree *t,TElemType pre[],TElemType in[],int s1,int t1,int s2,int t2);
//由二叉树的前序和中序序列构建二叉树的递归算法
int check(TElemType pre[],TElemType in[]);
//检查序列合法性
int main()
{
    int m;
    TElemType pre[Max_tree],in[Max_tree];
    do
    {
        printf("请输入正确的序列！\n");
        printf("请输入一棵树的先序序列:\n");
        gets(pre);
        printf("请输入一棵树的中序序列:\n");
        gets(in);
    }while(check(pre,in)==0);
    BinTree root;
    int s1=0,t1=strlen(pre)-1,s2=0,t2=strlen(in)-1;
    createBinTree_pre_In_recur(&root,pre,in,s1,t1,s2,t2);
    printf("先序遍历二叉树：");
    PreOrder_recur(root);
    printf("\n");
    printf("中序遍历二叉树：");
    InOrder_recur(root);
    printf("\n");
    printf("后序遍历二叉树：");
    PostOrder_recur(root);
    printf("\n");
    return 0;
}
void createBinTree_pre_In_recur(BinTree *t,TElemType pre[],TElemType in[],int s1,int t1,int s2,int t2)
//由二叉树的前序和中序序列构建二叉树
{
    if(s1<=t1)
    {
        int i;
        *t=(BinTree)malloc(sizeof(BiTNode));
//        创建根结点
        (*t)->data=pre[s1];
        (*t)->lchild=NULL;
        (*t)->rchild=NULL;
        for(i=s2; i<=t2; i++)
        {
            if(in[i]==pre[s1])
//            在中序序列中查找根
            {
                break;
            }
        }
            createBinTree_pre_In_recur(&((*t)->lchild),pre,in,s1+1,s1+i-s2,s2,i-1);
            createBinTree_pre_In_recur(&((*t)->rchild),pre,in,s1+i-s2+1,t1,i+1,t2);
    }
}
int check(TElemType pre[],TElemType in[])
//检查序列合法性
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
