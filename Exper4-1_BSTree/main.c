#include <stdio.h>
#include <stdlib.h>


typedef int BSTElemType;
typedef struct tnode
{
    BSTElemType data;
    int num;
    struct tnode *lchild,*rchild;
} BSTNode,*BSTree;

//BSTNode *Search_recur(BSTree p,BSTElemType x)
//{
//    if((p)==NULL)
//    {
//        return NULL;
//    }
//    else if(x<(p)->data)
//    {
//        return Search(p->lchild,x);
//    }
//    else if(x>(p)->data)
//    {
//        return Search(p->rchild,x);
//    }
//    else
//    {
//        return p;
//    }
//}
BSTNode *Search(BSTree *BT,BSTElemType x,BSTree *father)
//非递归搜索算法
{
    BSTNode *p=*BT;
    *father=NULL;
    while(p!=NULL&&p->data!=x)  //寻找包含x的结点
    {
        *father=p;              //像下层继续寻找
        if(x<p->data)
        {
            p=p->lchild;
        }
        else
        {
            p=p->rchild;
        }
    }
    return p;
}
int Insert (BSTree *BT,BSTElemType x)
//向根为BT的二叉搜索树插入一个关键码为x的结点，插入成功函数返回1，否则返回0
{
    BSTNode *s,*p,*f;
    p=Search(BT,x,&f);  //寻找插入位置
    if(p!=NULL)   //查找成功，说明节点已经存在，让其个数加一
    {
        p->num++;
        return 0;
    }
    s=(BSTNode *)malloc(sizeof(BSTNode));  //否则创建新结点
    if(!s)
    {
        printf("space false !");
        exit(1);
    }
    s->data=x;
    s->num=1;
    s->lchild=NULL;
    s->rchild=NULL;
    if(f==NULL)  //原树为空树，结点为根结点
    {
        *BT=s;
    }
    else if(x<f->data)  //非空树，结点作为左子女插入
    {
        f->lchild=s;
    }
    else   //结点作为右子女插入
    {
        f->rchild=s;
    }
    return 1;
}
void createBST(BSTree *BT,BSTElemType finish)
//输入一个元素序列，建立一棵根为BT的二叉搜索树，输入序列以finish未结束符
{
    BSTElemType x;
    *BT=NULL;   //置空树
    scanf("%d",&x);  //输入数据
    while(x!=finish)   //finish是结束标志
    {
        Insert(BT,x);  //插入再输入数据
        scanf("%d",&x);
    }
}
int Remove(BSTree *BT,BSTElemType x)
//在BT为根的二叉搜索树中删除关键码为x的结点，删除成功返回1，否则返回0
{
    BSTNode *s,*p,*f;
    p=Search(BT,x,&f);  //寻找删除结点
    if(p==NULL)  //查询失败，不做删除
    {
        return 0;
    }
    if(p!=NULL&&p->num>1) //查询成功但结点个数大于1个，结点不删除，其个数减一
    {
        p->num--;
        return 1;
    }
    if(p->lchild!=NULL&&p->rchild!=NULL)   //被删结点*p有两个子女
    {
        s=p->rchild;          //找*p的中序后继*s
        f=p;
        while(s->lchild!=NULL)
        {
            f=s;
            s=s->lchild;
        }
        p->data=s->data;   //将s的数据传给*p
        p=s;
    }  //该结点成为被删除结点
    if(p->lchild!=NULL)  //单子女，记录非空子女
    {
        s=p->lchild;
    }
    else
    {
        s=p->rchild;
    }
    if(p==*BT)   //被删结点为根结点
    {
        *BT=s;
    }
    else if(s&&s->data<f->data)
    {
        f->lchild=s;
    }
    else
    {
        f->rchild=s;
    }
    free(p);   //释放被删结点
    return 1;
}
void PreOrder_recur(BSTNode *BT)
//按先序遍历以BT为树根的二叉树递归算法
{
    if(BT!=NULL)
//    空树BT=NULL是递归的结束条件
    {
        printf("%d(%d) ",BT->data,BT->num);
//    访问根结点
        PreOrder_recur(BT->lchild);
//    先序遍历根的左子树
        PreOrder_recur(BT->rchild);
//    先序遍历跟的右子树
    }
}
int Menu(void)
//菜单
{
    int s;
    printf("Management for item\n");
    printf("1.Insert!\n");
    printf("2.Remove!\n");
    printf("3.Display!\n");
    printf("4.Input the data!\n");
    printf("0.Exit\n");
    printf("Please Input your choice:");
    scanf("%d",&s);
    return s;
}
int main()
{
    int i,x,flag=0;
    BSTree BT=NULL;
    BSTNode *p,*father;
    while(1)
    {
        x=Menu();
        switch(x)
        {
        case 1:
            printf("The number you want to insert:\n");
            scanf(" %d",&x);
            Insert(&BT,x);
            printf("\n");
            break;
        case 2:
            printf("The number you want to remove:\n");
            scanf(" %d",&x);
            Remove(&BT,x);
            printf("\n");
            break;
        case 3:
            PreOrder_recur(BT);
            printf("\n");
            break;
        case 4:
            printf("Please input the data:(-1 is the flag of ending)\n");
            createBST(&BT,-1);
            printf("\n");
            printf("\n");
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("Foolish");
        }
    }
    return 0;
}
