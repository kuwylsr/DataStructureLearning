#include <stdio.h>
#include <stdlib.h>
#define heapSize 40

typedef struct node
{
    int title;
    int pvalue;
}HElemType,temp;

typedef struct
{
    HElemType elem[heapSize];
    int curSize;
}maxHeap;

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

void Insert(maxHeap *H,HElemType x);
HElemType DeleteMax(maxHeap *H);
void InitQueue(LinkQueue Q);
//���г�ʼ�������ͷָ��Ͷ�βָ���ΪNULL
int EnQueue(LinkQueue Q,QElemType x);
//�����У�����Ԫ��x���뵽���еĶ�β����β��
int DeQueue (LinkQueue Q,QElemType *x);
//�����У�������пգ������˶ӣ���������0�������ò���x��ֵ������
int QueueEmpty(LinkQueue Q);
//�ж϶����Ƿ�Ϊ�գ����п���������1������������0
void Readfile(maxHeap *H,HElemType temp);
int main()
{
    int i,k;
    maxHeap H;
    H.curSize=0;
    LinkQueue Q=(LinkQueue)malloc(sizeof(LinkQueue1));
    InitQueue(Q);
    HElemType p,temp;
    Readfile(&H,temp);
    QElemType sth;
    while(H.curSize!=0)
    {
        p=DeleteMax(&H);
        EnQueue(Q,p.title);
    }
    while(QueueEmpty(Q)!=1)
    {
        DeQueue(Q,&sth);
        printf("%d",sth);
    }
    return 0;
}

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
int QueueEmpty(LinkQueue Q)
//�ж϶����Ƿ�Ϊ�գ����п���������1������������0
{
    return (*Q).front==NULL;
}
void Readfile(maxHeap *H,HElemType temp)
{
    FILE *fp;
    int i;
    fp=fopen("Data1.txt","r");
    if(fp==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    for(i=0;!feof(fp);i++)
    {
        fscanf(fp,"%d",&(temp.title));
        fscanf(fp,"%d",&(temp.pvalue));
        Insert(H,temp);
    }
    fclose(fp);
}
void Insert(maxHeap *H,HElemType x)
{
    int i;
    if((*H).curSize!=0)
    {
        i=(*H).curSize+1;
        while((i!=1)&&(x.pvalue>(*H).elem[i/2].pvalue))
        {
            (*H).elem[i].pvalue=(*H).elem[i/2].pvalue;
            (*H).elem[i].title=(*H).elem[i/2].title;
            i=i/2;
        }
        (*H).elem[i].pvalue=x.pvalue;
        (*H).elem[i].title=x.title;
    }
    else
    {
        (*H).elem[0].pvalue=x.pvalue;
        (*H).elem[0].title=x.title;
        (*H).curSize+=1;
    }
}
HElemType DeleteMax(maxHeap *H)
{
    int parent=1,child=2;
    HElemType element,tmp;
    if((*H).curSize!=0)
    {
        element=(*H).elem[1];
        tmp=(*H).elem[(*H).curSize--];
        while(child<=(*H).curSize)
        {
            if((child<(*H).curSize)&&(*H).elem[child].pvalue<(*H).elem[child+1].pvalue)
                child++;
            if(tmp.pvalue>=(*H).elem[child].pvalue)
                break;
            (*H).elem[parent].pvalue=(*H).elem[child].pvalue;
            (*H).elem[parent].title=(*H).elem[child].title;
            parent=child;
            child*=2;
        }
        (*H).elem[parent].pvalue=tmp.pvalue;
        (*H).elem[parent].title=tmp.title;
        return element;
    }
}
