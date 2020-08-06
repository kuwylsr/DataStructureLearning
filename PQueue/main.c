#include <stdio.h>
#include <stdlib.h>
#define heapSize 40
//�����ȼ����еĸ���ʵ���У��������Ч��һ�����ݽṹ
//����һ���������ȫ������



typedef struct node  //����Ԫ�ص���������
{
    int title;    //������
    int pvalue; //��������ȼ�
} HElemType;

typedef struct     //����ѵĽṹ����
{
    HElemType elem[heapSize]; //����ѵ�Ԫ�ش洢����
    int curSize;   //����ѵ�ǰԪ�ظ���
} maxHeap;

//�����������͵Ķ���
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

void creatMaxHeap(maxHeap *H,int n);
//��һ�����������𲽹���С���ѵ��㷨
void siftDown(maxHeap *H,int strat,int m);
//������Զ�����"ɸѡ"�����㷨
int Remove(maxHeap *H,HElemType *x);
//����ѵ�ɾ���㷨
void InitQueue(LinkQueue Q);
//���г�ʼ�������ͷָ��Ͷ�βָ���ΪNULL
int EnQueue(LinkQueue Q,QElemType x);
//�����У�����Ԫ��x���뵽���еĶ�β����β��
int DeQueue (LinkQueue Q,QElemType *x);
//�����У�������пգ������˶ӣ���������0�������ò���x��ֵ������
int QueueEmpty(LinkQueue Q);
//�ж϶����Ƿ�Ϊ�գ����п���������1������������0
void Readfile(maxHeap *H);
//���ļ��ж�ȡ����
int main()
{
    maxHeap H;
    H.curSize=0;
    LinkQueue Q=(LinkQueue)malloc(sizeof(LinkQueue1));
    InitQueue(Q);
    Readfile(&H);
    HElemType p;
    QElemType sth;
    creatMaxHeap(&H,5);
    //�������������ɾ����㣬ɾ���Ľ�����������
    while(H.curSize!=0)
    {
        Remove(&H,&p);
        EnQueue(Q,p.title);
    }
    //������ų��ӣ���ִ�������˳��
    while(QueueEmpty(Q)!=1)
    {
        DeQueue(Q,&sth);
        printf("%d",sth);
    }
    return 0;
}
void creatMaxHeap(maxHeap *H,int n)
//��һ�����������𲽹�������ѵ��㷨
//�㷨��һ������Ӿֲ������壬�������ϵ���Ϊ�����
{
    int i;
    (*H).curSize=n; //���ƶ����飬������ǰ��С
    for(i=((*H).curSize-2)/2; i>=0; i--) //�Ե������������γɶ�
    {
        siftDown(H,i,(*H).curSize-1); //�ֲ���������ɸѡ
    }
}
void siftDown(maxHeap *H,int strat,int m)
//������Զ�����"ɸѡ"�����㷨
//���δ�����һ�� �����ĸ�����ţ�Ȼ���Զ�����"ɸѡ"����
{
    int i=strat,j;
    HElemType temp=(*H).elem[i];
    for(j=2*i+1; j<=m; j=2*j+1)
        //2*i+1�Ǹ���������ӣ�2*i+2�Ǹ������Ҷ��ӡ��ȱȽϸ������������ӣ��ٽ�ɸѡ���Ķ���������Ƚ�
    {
        if(j<m&&(*H).elem[j].pvalue<(*H).elem[j+1].pvalue)
            //���ȱȽϸ������������Ҷ��ӵ����ȼ���С��j�ı��ָ�����ȼ��ߵĽ��
        {
            j++;
        }
        else if(j<m&&((*H).elem[j].pvalue==(*H).elem[j+1].pvalue)&&(*H).elem[j].title>(*H).elem[j+1].title)
            //����������������Ҷ��ӵ����ȼ���ͬ���򽫱��ָ�������С�Ľ��
            j++;
        if(temp.pvalue>(*H).elem[j].pvalue)
            //���ɸѡ���Ķ��ӽ������ȼ�С�ڸ��������ȼ�����������
        {
            break;
        }
        else if(temp.pvalue==(*H).elem[j].pvalue&&(temp.title<(*H).elem[j].title))
            //���ɸѡ���Ķ��ӽ������ȼ����ڸ��������ȼ������Ŵ��ڸ����ı�ţ���������
            break;
        else
            //��ɸѡ���Ķ��ӽ������ȼ����ڸ��������ȼ��������ȼ���ͬ������С�ڸ�����ţ����以��λ��
        {
            (*H).elem[i]=(*H).elem[j];
            i=j;
        }
    }
    (*H).elem[i]=temp;
}
int Remove(maxHeap *H,HElemType *x)
//����ѵ�ɾ���㷨
{
    if((*H).curSize==0) //�ѿգ�����0
    {
        return 0;
    }
    *x=(*H).elem[0];
    (*H).elem[0]=(*H).elem[(*H).curSize-1]; //������Ԫ��������
    (*H).curSize--; //�����һ�����ɾ��
    siftDown(H,0,(*H).curSize-1); //�����ѣ�ʹ���Ϊ�����
    return 1;
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
void Readfile(maxHeap *H)
{
    FILE *fp;
    int i;
    fp=fopen("Data.txt","r");
    if(fp==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    for(i=0; !feof(fp); i++)
    {
        fscanf(fp,"%d",&((*H).elem[i].title));
        fscanf(fp,"%d",&((*H).elem[i].pvalue));
    }
    fclose(fp);
}
