#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define radix 10
#define d 5
#define maxSize 20000
#define N 10000

int getDigit(int x,int k)
//������x����ȡ��kλ���֣����λ��1���θ�λ��2.........,���λ��k
{
    int i;
    if(k<1||k>d)  //����λ��������d
    {
        return -1;
    }
    for(i=1;i<=d-k;i++)
    {
        x=x/10;
    }
    return x%10;    //��ȡx�ĵ�kλ����
}
void RadixSort(int A[],int left,int right,int k)
//MSD���������㷨�Ӹ�λ����λ�����н��з��䣬ʵ������k�ǵڼ�λ��n�Ǵ�����ĸ���
//��Ϊ�ǵݹ��㷨��left��right�Ǵ�����Ԫ�������е���βλ��
{
    if(left>=right||k>d)
    {
        return;
    }
    int i,j,v,p1,p2,count[radix],posit[radix];
    int *auxArray=(int *)malloc((right-left+1)*sizeof(int));  //�ݴ�����
    for(j=0;j<radix;j++)
    {
        count[j]=0;
    }
        for(i=left;i<=right;i++)  //ͳ�Ƹ�ͰԪ�ظ���
        {
            v=getDigit(A[i],k);
            count[v]++;
        }
        posit[0]=0;
        for(j=1;j<radix;j++) //���Ÿ�ͰԪ��λ��
        {
            posit[j]=count[j-1]+posit[j-1];
        }
        for(i=left;i<=right;i++)//Ԫ�ذ�λֵ���䵽��Ͱ
        {
            v=getDigit(A[i],k);    //ȡԪ��A[i]��kλ��ֵ
            auxArray[posit[v]++]=A[i];   //��Ԥ�ȼ���λ�ô��
        }
        for(i=left,j=0;i<=right;i++,j++)  //��������д��ԭ����
        {
            A[i]=auxArray[j];
        }
        free(auxArray);
        p1=left;
        for(j=0;j<radix;j++)    //��Ͱ�ݹ��k-1λ����
        {
            p2=p1+count[j]-1;  //ȡ��Ͱ����ĩλ��
            RadixSort(A,p1,p2,k+1);  //����Ͱ��Ԫ����Ͱ����
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
