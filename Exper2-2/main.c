#include <stdio.h>
#include <stdlib.h>
#define Max_tree 50
#define Stacksize 30
//工作栈的大小
#define Queuesize 30
//工作队列大小

typedef char TElemType;
typedef struct node
{
    TElemType data;
    struct node *lchild,*rchild;
}BiTNode,BiTNode1,* BinTree;
typedef BiTNode* SElemType;
//工作栈的元素类型
typedef BiTNode1* QElemType;
//工作队列的元素类型
void createBinTree_Pre(BinTree *T,TElemType pre[],int *n);
//根据二叉树的先序序列来构建二叉树
void PreOrder_recur(BiTNode *BT);
//按先序遍历以BT为树根的二叉树递归算法
void InOrder_recur(BiTNode *BT);
//按中序遍历以BT为树根的二叉树的递归算法
void PostOrder_recur(BiTNode *BT);
//按后序遍历以BT为树根的二叉树的递归算法
void PreOrder(BiTNode *BT);
//按先序遍历以BT为树根的二叉树的非递归算法
void InOrder(BiTNode *BT);
//按中序遍历以BT为树根的二叉树的非递归算法
void PostOrder(BiTNode *BT);
//按后序遍历以BT为树根的二叉树的非递归算法
void LevelOrder(BiTNode *BT);
//按层序遍历以BT为树根的二叉树算法
int main()
{
    BinTree root;
    int n=0;
    TElemType pre[Max_tree];
    printf("请输入先序序列(空结点为#)!\n");
    gets(pre);
    createBinTree_Pre(&root,pre,&n);
    printf("用递归算法先序遍历二叉树：");
    PreOrder_recur(root);
    printf("\n");
    printf("用递归算法中序遍历二叉树：");
    InOrder_recur(root);
    printf("\n");
    printf("用递归算法后序遍历二叉树：");
    PostOrder_recur(root);
    printf("\n");
    printf("用非递归算法先序遍历二叉树：");
    PreOrder(root);
    printf("\n");
    printf("用非递归算法中序遍历二叉树：");
    InOrder(root);
    printf("\n");
    printf("用非递归算法后序遍历二叉树：");
    PostOrder(root);
    printf("\n");
     printf("用层序遍历二叉树：");
    LevelOrder(root);
    printf("\n");
    return 0;
}
void createBinTree_Pre(BinTree *T,TElemType pre[],int *n)
//以递归的方式建立二叉树，pre[]是输入序列，以“;"结束，空结点的标识为’#‘
//引用参数n初始调用前赋值0，退出后n是输入统计
{
    TElemType ch=pre[*n];
//    读入一个结点的数据
    (*n)++;
    if(ch==';')
//    处理结束返回
    {
        return;
    }
    if(ch!='#')
//        建立非空子树
    {
        (*T)=(BinTree)malloc(sizeof(BiTNode));
//        建立根节点
        (*T)->data=ch;
        createBinTree_Pre(&((*T)->lchild),pre,n);
//        递归建立左子树
        createBinTree_Pre(&((*T)->rchild),pre,n);
//        递归建立右子树
    }
    else
//    否则建立空子树
    {
        (*T)=NULL;
    }
}
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
void PreOrder(BiTNode *BT)
//按先序遍历以BT为树根的二叉树的非递归算法
//此处选用顺序栈的静态存储结构
{
    SElemType S[Stacksize];
    int top=-1;
//    建立工作栈并初始化
    BiTNode *p=BT;
//    p是遍历指针，从根节点开始
    do
    {
        while(p!=NULL)
//        遍历指针进到左子女结点
        {
            printf("%c ",p->data);
//            访问
            S[++top]=p;
            p=p->lchild;
//            一路走一路进栈，想左下结点走下去
        }
        if(top>-1)
//        栈不空时退栈
        {
            p=S[top--];
//            退栈，退栈结点即为此子树的根结点
            p=p->rchild;
//            遍历指针进到右子女结点
        }
    }while(p!=NULL||top>-1);
}
void InOrder(BiTNode *BT)
//按中序遍历以BT为树根的二叉树的非递归算法
{
    SElemType S[Stacksize];
    int top=-1;
//    建立工作栈并初始化
    BiTNode *p=BT;
//    p是遍历指针，从根节点开始
    do
    {
        while(p!=NULL)
//        遍历指针进到左子女结点
        {
            S[++top]=p;
            p=p->lchild;
//            一路走一路进栈，想左下结点走下去
        }
        if(top>-1)
//        栈不空时退栈
        {
            p=S[top--];
//            退栈，退栈结点即为此子树的根结点
            printf("%c ",p->data);
//            访问
            p=p->rchild;
//            遍历指针进到右子女结点
        }
    }while(p!=NULL||top>-1);
}
void PostOrder(BiTNode *BT)
//按后序遍历以BT为树根的二叉树的非递归算法
{
    SElemType S[Stacksize];
    int top=-1;
//    建立工作栈并初始化
    BiTNode *p=BT;
    BiTNode *pre=NULL;
//    p是遍历指针，pre是前趋指针
    do
    {
        while(p!=NULL)
//        遍历指针进到左子女结点
        {
            S[++top]=p;
            p=p->lchild;
//            一路走一路进栈，想左下结点走下去
        }
        if(top>-1)
        {
            p=S[top];
//            用p记忆栈顶元素
            if(p->rchild!=NULL&&p->rchild!=pre)
//            p有右子女且未访问过
            {
                p=p->rchild;
            }
            else
            {
                printf("%c ",p->data);
//                访问
                pre=p;
                p=NULL;
//                记忆刚访问过的结点
                top--;

            }
        }
    }while(p!=NULL||top!=-1);
}
void LevelOrder(BiTNode *BT)
//按层序遍历以BT为树根的二叉树算法
{
    QElemType Q[Queuesize];
    int rear=0,front=0;
//    建立工作队列并初始化
    BiTNode *p=BT;
//    p是遍历指针，从队尾开始
    Q[rear++]=p;
    while(rear!=front)
    {
        p=Q[front];
        front=(front+1)%Queuesize;
//        从队列中退出一个结点
        printf("%c ",p->data);
//        访问
        if(p->lchild!=NULL)
//        若有左子女，进队
        {
            Q[rear]=p->lchild;
            rear=(rear+1)%Queuesize;
        }
        if(p->rchild!=NULL)
//        若有右子女，进队
        {
            Q[rear]=p->rchild;
            rear=(rear+1)%Queuesize;
        }
    }
}
//ABC##D#E###;
//ABDH##I##E##CF#J##G##;
