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
int createBinTree_pre_In(TElemType pre[],Inm in[]);
//由二叉树的前序和中序序列构建二叉树的非递归算法
int check(TElemType pre[],TElemType in[]);
//检查序列合法性
int i=0;
int main()
{
    int j,root,k;
    int m=1;
    TElemType pre[Max_tree];
//    存储前序序列
    Inm in[Max_tree];
//    结构体数组类型来存储中序序列
    while(m==1)
    {
        printf("请输入一个正确序列！\n");
        printf("请输入一棵树的先序序列:\n");
        gets(pre);
        printf("请输入一棵树的中序序列:\n");
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
//    初始化in[]
    BiTNode *C[i-1];
//    建立指向树结点类型的指针数组
    root=createBinTree_pre_In(pre,in);

//    将用静态二叉链表存储的树来用结点表示，将指针数组的指针连起来形成树
    for(j=0;j<i-1;j++)
//    为数组中每个指针开辟空间并根据静态二叉链表对数据域赋值
    {
        C[j]=(BinTree)malloc(sizeof(BiTNode));
        C[j]->data=in[j].ch;
    }

//    将数组中每个结点根据静态二叉链表连接
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
    printf("先序遍历二叉树：");
    PreOrder_recur(C[root]);
    printf("\n");
    printf("中序遍历二叉树：");
    InOrder_recur(C[root]);
    printf("\n");
    printf("后序遍历二叉树：");
    PostOrder_recur(C[root]);
    printf("\n");
    return 0;
}
int createBinTree_pre_In(TElemType pre[],Inm in[])
//由二叉树的前序和中序序列构建二叉树的非递归算法
{
    Stack S;
    int i1,j,k,root;
    S.top=-1;
//    初始化栈
    for(i1=0;i1<i-1;i1++)
    {
        j=0;
        while(in[j].ch!=pre[i1])
//        找到先序序列元素对应的中序序列的下标
        {
            j++;
        }
        if(i1==0)
//        找到根节点在中序in[]中对应的下标
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
//            若下标比栈顶元素小，压栈
            {
                in[S.Data[S.top]].lc=j;
//                连接到左子树
                S.top++;
                S.Data[S.top]=j;
            }
            else
            {
                while(j>S.Data[S.top]&&S.top!=-1)
//                若下标比栈顶元素大，弹出，直到小于等于为止
                {
                    k=S.Data[S.top];
//                    记录下标
                    S.top--;
                }
                in[k].rc=j;
//                连接到右子树
                S.top++;
                S.Data[S.top]=j;
            }
        }
    }
    return root;
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
