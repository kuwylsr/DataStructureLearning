#include <stdio.h>
#include <stdlib.h>

#define maxsize 200000
#define N 20000
typedef int Datatype;

void Swap(Datatype Data_arr[],int n,int i,int j)
{
    if(i>=0&&i<n&&j>=0&&j<n)
    {
        Datatype temp=Data_arr[i];
        Data_arr[i]=Data_arr[j];
        Data_arr[j]=temp;
    }
}
int partition(Datatype Data_arr[],int n,int low,int high)
{
    int i,k=low;
    Datatype pivot=Data_arr[low];
    for(i=low+1;i<=high;i++)
    {
        if(Data_arr[i]<pivot)
        {
            k++;
            if(k!=i)
            {
                Swap(Data_arr,n,i,k);
            }
        }
    }
    Data_arr[low]=Data_arr[k];
    Data_arr[k]=pivot;
    return k;
}
void QuickSort(Datatype Data_arr[],int left,int right)
{
    if(left<right)
    {
        int pivotpos=partition(Data_arr,N,left,right);
        QuickSort(Data_arr,left,pivotpos-1);
        QuickSort(Data_arr,pivotpos+1,right);
    }
}
Read_data(Datatype Data_arr[])
{
    FILE *fp;
    int i;
     fp=fopen("Data1.txt","r");
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
    QuickSort(Data_arr,0,N-1);
//    for(i=0;i<N;i++)
//    {
//        printf("%d ",Data_arr[i]);
//    }
    time_end=clock();
    printf("Time is:%dms\n",time_end-time_begin);
    return 0;
}
