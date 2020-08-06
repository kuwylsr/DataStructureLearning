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
//�ǵݹ������㷨
{
    BSTNode *p=*BT;
    *father=NULL;
    while(p!=NULL&&p->data!=x)  //Ѱ�Ұ���x�Ľ��
    {
        *father=p;              //���²����Ѱ��
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
//���ΪBT�Ķ�������������һ���ؼ���Ϊx�Ľ�㣬����ɹ���������1�����򷵻�0
{
    BSTNode *s,*p,*f;
    p=Search(BT,x,&f);  //Ѱ�Ҳ���λ��
    if(p!=NULL)   //���ҳɹ���˵���ڵ��Ѿ����ڣ����������һ
    {
        p->num++;
        return 0;
    }
    s=(BSTNode *)malloc(sizeof(BSTNode));  //���򴴽��½��
    if(!s)
    {
        printf("space false !");
        exit(1);
    }
    s->data=x;
    s->num=1;
    s->lchild=NULL;
    s->rchild=NULL;
    if(f==NULL)  //ԭ��Ϊ���������Ϊ�����
    {
        *BT=s;
    }
    else if(x<f->data)  //�ǿ����������Ϊ����Ů����
    {
        f->lchild=s;
    }
    else   //�����Ϊ����Ů����
    {
        f->rchild=s;
    }
    return 1;
}
void createBST(BSTree *BT,BSTElemType finish)
//����һ��Ԫ�����У�����һ�ø�ΪBT�Ķ���������������������finishδ������
{
    BSTElemType x;
    *BT=NULL;   //�ÿ���
    scanf("%d",&x);  //��������
    while(x!=finish)   //finish�ǽ�����־
    {
        Insert(BT,x);  //��������������
        scanf("%d",&x);
    }
}
int Remove(BSTree *BT,BSTElemType x)
//��BTΪ���Ķ�����������ɾ���ؼ���Ϊx�Ľ�㣬ɾ���ɹ�����1�����򷵻�0
{
    BSTNode *s,*p,*f;
    p=Search(BT,x,&f);  //Ѱ��ɾ�����
    if(p==NULL)  //��ѯʧ�ܣ�����ɾ��
    {
        return 0;
    }
    if(p!=NULL&&p->num>1) //��ѯ�ɹ�������������1������㲻ɾ�����������һ
    {
        p->num--;
        return 1;
    }
    if(p->lchild!=NULL&&p->rchild!=NULL)   //��ɾ���*p��������Ů
    {
        s=p->rchild;          //��*p��������*s
        f=p;
        while(s->lchild!=NULL)
        {
            f=s;
            s=s->lchild;
        }
        p->data=s->data;   //��s�����ݴ���*p
        p=s;
    }  //�ý���Ϊ��ɾ�����
    if(p->lchild!=NULL)  //����Ů����¼�ǿ���Ů
    {
        s=p->lchild;
    }
    else
    {
        s=p->rchild;
    }
    if(p==*BT)   //��ɾ���Ϊ�����
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
    free(p);   //�ͷű�ɾ���
    return 1;
}
void PreOrder_recur(BSTNode *BT)
//�����������BTΪ�����Ķ������ݹ��㷨
{
    if(BT!=NULL)
//    ����BT=NULL�ǵݹ�Ľ�������
    {
        printf("%d(%d) ",BT->data,BT->num);
//    ���ʸ����
        PreOrder_recur(BT->lchild);
//    �����������������
        PreOrder_recur(BT->rchild);
//    �����������������
    }
}
int Menu(void)
//�˵�
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
