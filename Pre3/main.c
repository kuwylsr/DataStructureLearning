
#include <stdio.h>
#include <stdlib.h>
#define N 100
int main()
{
    int n,i,j,k,start,end,len;
    int a[N][N];
    int isExist[N];
    int arr[N];
    printf("�ж��ٸ�ѡ�֣�\n");
    scanf("%d",&n);
    printf("�������ϵ����(���磺iʤj����a[i][j]=1,a[j][i]=-1,a[i][i]=0)");
    for(i=0;i<n;i++){
        isExist[i]=1;
        arr[i]=0;//����
        for(j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }//��ʼ��������ֵ
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(a[i][j]==1){
                start=i;
                end=j;
                isExist[i]=0;
                isExist[j]=0;
                goto out;
            }
        }
    }//�ҵ���ʼ��(2��Ԫ����ɣ�
    out:
    arr[0]=start;
    arr[1]=end;
    len=1;
    for(;len<n-1;){//��δ����һֱѭ��
        for(j=0;j<n;j++){
            if(isExist[j]==0)
                continue;//����㲻���ڣ�ֱ������
            if(a[end][j]==1){//�����β��ָ��j
                len++;//����+1
                arr[len]=j;//j�ӵ�β��
                end=j;
                isExist[j]=0;//�޳��������
                break;
            }
            else if(a[j][arr[0]]==1){//�����ͷ��ָ��
                len++;
                isExist[j]=0;
                for(i=len;i>0;i--){
                    arr[i]=arr[i-1];
                }
                arr[0]=j;//�ӵ�ͷ��
                break;
            }
            else {
                for(i=0;i<=len-1;i++){//�����
                    if(a[arr[i]][j]==1&&a[arr[i+1]][j]==-1){
                        len++;
                        isExist[j]=0;
                        for(k=len;k>i+1;k--){
                            arr[k]=arr[k-1];
                        }
                        arr[i+1]=j;//�嵽�м�
                        break;
                    }
                }
                break;
            }
        }
    }
    for(i=0;i<n-1;i++){
        printf("%d��",arr[i]);
    }
    printf("%d",arr[n-1]);
}
