#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxsize 200000
#define N 20000
typedef int Datatype;  //����Ԫ�����Ͷ���

void Swap(Datatype Data_arr[],int n,int i,int j)
//���������±�i��j������
{
    if(i>=0&&i<n&&j>=0&&j<n)
    {
        Datatype temp=Data_arr[i];
        Data_arr[i]=Data_arr[j];
        Data_arr[j]=temp;
    }
}
int Partition(Datatype Data_arr[],int low,int high)
//�����㷨
//������һ�ˣ�ÿ�����Ȼ�׼С�Ľ�������ߣ��������ػ�׼�ƶ�����λ��
{
    int i,k=low;
    Datatype pivot=Data_arr[low];      //��׼Ԫ��
    for(i=low+1;i<=high;i++)       //һ��ɨ���������н��л���
    {
        if(Data_arr[i]<pivot)   //��⵽������С�ڻ�׼��Ԫ��
        {
            k++;
            if(k!=i)    //��С�ڻ�׼��Ԫ�ؽ��������ȥ
            {
                Swap(Data_arr,N,i,k);
            }
        }
    }
    Data_arr[low]=Data_arr[k];
    Data_arr[k]=pivot;     //����׼Ԫ�ؾ�λ
    return k;     //���ػ�׼Ԫ��λ��
}
void QuickSort(Datatype Data_arr[],int left,int right)
//�����Ż��Ŀ�������β�ݹ飩�������Ż�һ���ɱ�����ʵʩ��
//��һ�εݹ�֮�����p��û���ô��ˣ�Ҳ����˵�ڶ��εݹ�����õ������ƽṹ����
{
    while(left<right)
    {
        int pivotpos=Partition(Data_arr,left,right);
        QuickSort(Data_arr,left,pivotpos-1);
        left=pivotpos+1;
    }
//    if(left<right)
//    {
//        int pivotpos=Partition(Data_arr,left,right);
//        QuickSort(Data_arr,left,pivotpos-1);
//        QuickSort(Data_arr,pivotpos+1,right);
//    }
}
void median3(Datatype Data_arr[],int left,int right)
//�˺����ڱ���ˣ��Ҷ˺��м������ȡ��ֵ�������������
{
    int mid=(left+right)/2;
    int k1,k2;
    if(Data_arr[left]<=Data_arr[mid])
    {
        k1=left;
        k2=mid;
    }
    else   //������˺��м��ѡ��С�ʹ�С
    {
        k1=mid;
        k2=left;
    }
    if(Data_arr[right]<Data_arr[k1])
    {
        k2=k1;
        k1=right;
    }
    else if(Data_arr[right]<Data_arr[k2])       //�ٴ��Ҷ�����С����С�Ƚ�
    {
        k2=right;
    }
    if(k2!=left)         //��С�߽�����left
    {
        Swap(Data_arr,N,k2,left);
    }
}
void InsertSort(Datatype Data_arr[])
//��������
//���ν�Ԫ�ذ���������뵽�������鵱��
{
    Datatype temp;
    int i,j;
    for(i=1;i<=N-1;i++)
    {
        if(Data_arr[i]<Data_arr[i-1])       //����Ѱ�Ҳ���λ�ã���������ԭλ
        {
            temp;Data_arr[i];    //�ݴ������Ԫ��
            for(j=i-1;j>=0&&temp<Data_arr[j];j--)
            {
                Data_arr[j+1]=Data_arr[j];   //����Ѱ��temp����λ��
            }
            Data_arr[j+1]=temp;    //����
        }
    }
}
void QuickSort_insert(Datatype Data_arr[],int M)
//���еݹ��������
//pivotpos�ǻ��ֽ�����Ѵ���������ֳ������֣���ߵ�Ԫ�������붼С���������ұߵĶ����ڻ��ߵ�����
{
    if(N<=M)
    {
        InsertSort(Data_arr);
    }
    else
    {
        QuickSort(Data_arr,0,N-1);
    }
}
Read_data(Datatype Data_arr[])
{
    FILE *fp;
    int i;
     fp=fopen("Data.txt","r");
    if(fp==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    for(i=0;i<N;i++)
    {
//        Data_arr[i]=rand()%(N+1);
//        fprintf(fp,"%d ",Data_arr[i]);
            fscanf(fp,"%d ",&Data_arr[i]);
    }
}#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxsize 200000
#define N 20000
typedef int Datatype;  //����Ԫ�����Ͷ���

void Swap(Datatype Data_arr[],int n,int i,int j)
//���������±�i��j������
{
    if(i>=0&&i<n&&j>=0&&j<n)
    {
        Datatype temp=Data_arr[i];
        Data_arr[i]=Data_arr[j];
        Data_arr[j]=temp;
    }
}
int Partition(Datatype Data_arr[],int low,int high)
//�����㷨
//������һ�ˣ�ÿ�����Ȼ�׼С�Ľ�������ߣ��������ػ�׼�ƶ�����λ��
{
    int i,k=low;
    Datatype pivot=Data_arr[low];      //��׼Ԫ��
    for(i=low+1;i<=high;i++)       //һ��ɨ���������н��л���
    {
        if(Data_arr[i]<pivot)   //��⵽������С�ڻ�׼��Ԫ��
        {
            k++;
            if(k!=i)    //��С�ڻ�׼��Ԫ�ؽ��������ȥ
            {
                Swap(Data_arr,N,i,k);
            }
        }
    }
    Data_arr[low]=Data_arr[k];
    Data_arr[k]=pivot;     //����׼Ԫ�ؾ�λ
    return k;     //���ػ�׼Ԫ��λ��
}
void QuickSort(Datatype Data_arr[],int left,int right)
//�����Ż��Ŀ�������β�ݹ飩�������Ż�һ���ɱ�����ʵʩ��
//��һ�εݹ�֮�����p��û���ô��ˣ�Ҳ����˵�ڶ��εݹ�����õ������ƽṹ����
{
    while(left<right)
    {
        int pivotpos=Partition(Data_arr,left,right);
        QuickSort(Data_arr,left,pivotpos-1);
        left=pivotpos+1;
    }
//    if(left<right)
//    {
//        int pivotpos=Partition(Data_arr,left,right);
//        QuickSort(Data_arr,left,pivotpos-1);
//        QuickSort(Data_arr,pivotpos+1,right);
//    }
}
void median3(Datatype Data_arr[],int left,int right)
//�˺����ڱ���ˣ��Ҷ˺��м������ȡ��ֵ�������������
{
    int mid=(left+right)/2;
    int k1,k2;
    if(Data_arr[left]<=Data_arr[mid])
    {
        k1=left;
        k2=mid;
    }
    else   //������˺��м��ѡ��С�ʹ�С
    {
        k1=mid;
        k2=left;
    }
    if(Data_arr[right]<Data_arr[k1])
    {
        k2=k1;
        k1=right;
    }
    else if(Data_arr[right]<Data_arr[k2])       //�ٴ��Ҷ�����С����С�Ƚ�
    {
        k2=right;
    }
    if(k2!=left)         //��С�߽�����left
    {
        Swap(Data_arr,N,k2,left);
    }
}
void InsertSort(Datatype Data_arr[])
//��������
//���ν�Ԫ�ذ���������뵽�������鵱��
{
    Datatype temp;
    int i,j;
    for(i=1;i<=N-1;i++)
    {
        if(Data_arr[i]<Data_arr[i-1])       //����Ѱ�Ҳ���λ�ã���������ԭλ
        {
            temp;Data_arr[i];    //�ݴ������Ԫ��
            for(j=i-1;j>=0&&temp<Data_arr[j];j--)
            {
                Data_arr[j+1]=Data_arr[j];   //����Ѱ��temp����λ��
            }
            Data_arr[j+1]=temp;    //����
        }
    }
}
void QuickSort_insert(Datatype Data_arr[],int M)
//���еݹ��������
//pivotpos�ǻ��ֽ�����Ѵ���������ֳ������֣���ߵ�Ԫ�������붼С���������ұߵĶ����ڻ��ߵ�����
{
    if(N<=M)
    {
        InsertSort(Data_arr);
    }
    else
    {
        QuickSort(Data_arr,0,N-1);
    }
}
Read_data(Datatype Data_arr[])
{
    FILE *fp;
    int i;
     fp=fopen("Data.txt","r");
    if(fp==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    for(i=0;i<N;i++)
    {
//        Data_arr[i]=rand()%(N+1);
//        fprintf(fp,"%d ",Data_arr[i]);
            fscanf(fp,"%d ",&Data_arr[i]);
    }
}
int main()
{
    int i,time_begin,time_end;

    Datatype Data_arr[N];
    Read_data(Data_arr);
    time_begin=clock();
    median3(Data_arr,0,N-1);
    QuickSort_insert(Data_arr,25);
//    for(i=0;i<N;i++)
//    {
//        printf("%d ",Data_arr[i]);
//    }
    time_end=clock();
    printf("Time is:%dms\n",time_end-time_begin);
    return 0;
}

int main()
{
    int i,time_begin,time_end;

    Datatype Data_arr[N];
    Read_data(Data_arr);
    time_begin=clock();
    median3(Data_arr,0,N-1);
    QuickSort_insert(Data_arr,25);
//    for(i=0;i<N;i++)
//    {
//        printf("%d ",Data_arr[i]);
//    }
    time_end=clock();
    printf("Time is:%dms\n",time_end-time_begin);
    return 0;
}
