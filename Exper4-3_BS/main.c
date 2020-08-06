#include <stdio.h>
#include <stdlib.h>

#define N 10000
#define maxsize 20000

void BucketSort(int A[],int B[],int len,int k)  //桶排序
{
    int C[k];
    int i,j,m;
    for(i=0; i<k; i++)
    {
        C[i]=0;
    }
    for(i=0; i<len; i++)
    {
        C[A[i]]++;
    }
    for(i=0,j=0; i<k; i++,j=m)
    {
        for(m=j; m<j+C[i]; m++)
        {
            B[m]=i;
        }
    }
}
int getMax(int A[],int len)  //得到数组A中最大的元素
{
    int i,max;
    max=A[0];
    for(i=1; i<len; i++)
    {
        if(A[i]>max)
            max=A[i];
    }
    return max;
}
Read_data(int Data_arr[])
{
    FILE *fp;
    int i;
     fp=fopen("Data4.txt","w");
    if(fp==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    for(i=0;i<N;i++)
    {
        Data_arr[i]=rand()%(N+1);
        fprintf(fp,"%d ",Data_arr[i]);
//            fscanf(fp,"%d ",&Data_arr[i]);
    }
}
int main()
{
     int i,max,time_begin,time_end;
    int A[maxsize];
    int B[maxsize];
    Read_data(A);
    max=getMax(A,N);
    time_begin=clock();
    BucketSort(A,B,N,max+1);
    for(i=0;i<N;i++)
    {
        printf("%d ",B[i]);
    }
    time_end=clock();
    printf("Time is:%dms\n",time_end-time_begin);
    return 0;
}
