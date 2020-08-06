#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxsize 200000
#define N 20000
typedef int Datatype;  //数组元素类型定义

void Swap(Datatype Data_arr[],int n,int i,int j)
//交换数组下标i和j的内容
{
    if(i>=0&&i<n&&j>=0&&j<n)
    {
        Datatype temp=Data_arr[i];
        Data_arr[i]=Data_arr[j];
        Data_arr[j]=temp;
    }
}
int Partition(Datatype Data_arr[],int low,int high)
//划分算法
//自左到右一趟，每遇到比基准小的交换到左边，函数返回基准移动到的位置
{
    int i,k=low;
    Datatype pivot=Data_arr[low];      //基准元素
    for(i=low+1;i<=high;i++)       //一趟扫描整个序列进行划分
    {
        if(Data_arr[i]<pivot)   //检测到排序码小于基准的元素
        {
            k++;
            if(k!=i)    //把小于基准的元素交换到左边去
            {
                Swap(Data_arr,N,i,k);
            }
        }
    }
    Data_arr[low]=Data_arr[k];
    Data_arr[k]=pivot;     //将基准元素就位
    return k;     //返回基准元素位置
}
void QuickSort(Datatype Data_arr[],int left,int right)
//进行优化的快速排序（尾递归）（这种优化一般由编译器实施）
//第一次递归之后变量p就没有用处了，也就是说第二次递归可以用迭代控制结构代替
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
//此函数在表左端，右端和中间点三者取中值，并交换到左端
{
    int mid=(left+right)/2;
    int k1,k2;
    if(Data_arr[left]<=Data_arr[mid])
    {
        k1=left;
        k2=mid;
    }
    else   //现在左端和中间点选最小和次小
    {
        k1=mid;
        k2=left;
    }
    if(Data_arr[right]<Data_arr[k1])
    {
        k2=k1;
        k1=right;
    }
    else if(Data_arr[right]<Data_arr[k2])       //再从右端与最小、次小比较
    {
        k2=right;
    }
    if(k2!=left)         //次小者交换到left
    {
        Swap(Data_arr,N,k2,left);
    }
}
void InsertSort(Datatype Data_arr[])
//插入排序
//依次将元素按其序码插入到排序数组当中
{
    Datatype temp;
    int i,j;
    for(i=1;i<=N-1;i++)
    {
        if(Data_arr[i]<Data_arr[i-1])       //逆序寻找插入位置，否则留置原位
        {
            temp;Data_arr[i];    //暂存待插入元素
            for(j=i-1;j>=0&&temp<Data_arr[j];j--)
            {
                Data_arr[j+1]=Data_arr[j];   //逆向寻找temp插入位置
            }
            Data_arr[j+1]=temp;    //插入
        }
    }
}
void QuickSort_insert(Datatype Data_arr[],int M)
//进行递归快速排序
//pivotpos是划分结果，把待排序数组分成两部分，左边的元素排序码都小于它，而右边的都大于或者等于它
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
typedef int Datatype;  //数组元素类型定义

void Swap(Datatype Data_arr[],int n,int i,int j)
//交换数组下标i和j的内容
{
    if(i>=0&&i<n&&j>=0&&j<n)
    {
        Datatype temp=Data_arr[i];
        Data_arr[i]=Data_arr[j];
        Data_arr[j]=temp;
    }
}
int Partition(Datatype Data_arr[],int low,int high)
//划分算法
//自左到右一趟，每遇到比基准小的交换到左边，函数返回基准移动到的位置
{
    int i,k=low;
    Datatype pivot=Data_arr[low];      //基准元素
    for(i=low+1;i<=high;i++)       //一趟扫描整个序列进行划分
    {
        if(Data_arr[i]<pivot)   //检测到排序码小于基准的元素
        {
            k++;
            if(k!=i)    //把小于基准的元素交换到左边去
            {
                Swap(Data_arr,N,i,k);
            }
        }
    }
    Data_arr[low]=Data_arr[k];
    Data_arr[k]=pivot;     //将基准元素就位
    return k;     //返回基准元素位置
}
void QuickSort(Datatype Data_arr[],int left,int right)
//进行优化的快速排序（尾递归）（这种优化一般由编译器实施）
//第一次递归之后变量p就没有用处了，也就是说第二次递归可以用迭代控制结构代替
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
//此函数在表左端，右端和中间点三者取中值，并交换到左端
{
    int mid=(left+right)/2;
    int k1,k2;
    if(Data_arr[left]<=Data_arr[mid])
    {
        k1=left;
        k2=mid;
    }
    else   //现在左端和中间点选最小和次小
    {
        k1=mid;
        k2=left;
    }
    if(Data_arr[right]<Data_arr[k1])
    {
        k2=k1;
        k1=right;
    }
    else if(Data_arr[right]<Data_arr[k2])       //再从右端与最小、次小比较
    {
        k2=right;
    }
    if(k2!=left)         //次小者交换到left
    {
        Swap(Data_arr,N,k2,left);
    }
}
void InsertSort(Datatype Data_arr[])
//插入排序
//依次将元素按其序码插入到排序数组当中
{
    Datatype temp;
    int i,j;
    for(i=1;i<=N-1;i++)
    {
        if(Data_arr[i]<Data_arr[i-1])       //逆序寻找插入位置，否则留置原位
        {
            temp;Data_arr[i];    //暂存待插入元素
            for(j=i-1;j>=0&&temp<Data_arr[j];j--)
            {
                Data_arr[j+1]=Data_arr[j];   //逆向寻找temp插入位置
            }
            Data_arr[j+1]=temp;    //插入
        }
    }
}
void QuickSort_insert(Datatype Data_arr[],int M)
//进行递归快速排序
//pivotpos是划分结果，把待排序数组分成两部分，左边的元素排序码都小于它，而右边的都大于或者等于它
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
