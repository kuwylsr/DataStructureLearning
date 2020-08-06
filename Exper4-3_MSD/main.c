#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define radix 10
#define d 5
#define maxSize 20000
#define N 10000

int getDigit(int x,int k)
//从整数x中提取第k位数字，最高位算1，次高位算2.........,最低位算k
{
    int i;
    if(k<1||k>d)  //正数位数不超过d
    {
        return -1;
    }
    for(i=1;i<=d-k;i++)
    {
        x=x/10;
    }
    return x%10;    //提取x的第k位数字
}
void RadixSort(int A[],int left,int right,int k)
//MSD基数排序算法从高位到低位对序列进行分配，实现排序。k是第几位，n是待排序的个数
//因为是递归算法，left和right是待排序元素子序列的首尾位置
{
    if(left>=right||k>d)
    {
        return;
    }
    int i,j,v,p1,p2,count[radix],posit[radix];
    int *auxArray=(int *)malloc((right-left+1)*sizeof(int));  //暂存数组
    for(j=0;j<radix;j++)
    {
        count[j]=0;
    }
        for(i=left;i<=right;i++)  //统计各桶元素个数
        {
            v=getDigit(A[i],k);
            count[v]++;
        }
        posit[0]=0;
        for(j=1;j<radix;j++) //安排各桶元素位置
        {
            posit[j]=count[j-1]+posit[j-1];
        }
        for(i=left;i<=right;i++)//元素按位值分配到个桶
        {
            v=getDigit(A[i],k);    //取元素A[i]第k位的值
            auxArray[posit[v]++]=A[i];   //按预先计算位置存放
        }
        for(i=left,j=0;i<=right;i++,j++)  //辅助数组写入原数组
        {
            A[i]=auxArray[j];
        }
        free(auxArray);
        p1=left;
        for(j=0;j<radix;j++)    //按桶递归对k-1位处理
        {
            p2=p1+count[j]-1;  //取子桶的首末位置
            RadixSort(A,p1,p2,k+1);  //对子桶内元素做桶排序
            p1=p2+1;
        }
}
Read_data(int Data_arr[])
{
    FILE *fp;
    int i;
     fp=fopen("Data2.txt","r");
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

    int Data_arr[N];
    Read_data(Data_arr);
    time_begin=clock();
    RadixSort(Data_arr,0,N-1,1);
    for(i=0;i<N;i++)
    {
        printf("%d ",Data_arr[i]);
    }
    time_end=clock();
    printf("Time is:%dms\n",time_end-time_begin);
    return 0;
}
