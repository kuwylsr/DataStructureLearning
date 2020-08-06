
#include <stdio.h>
#include <stdlib.h>
#define N 100
int main()
{
    int n,i,j,k,start,end,len;
    int a[N][N];
    int isExist[N];
    int arr[N];
    printf("有多少个选手？\n");
    scanf("%d",&n);
    printf("请输入关系矩阵(例如：i胜j，则a[i][j]=1,a[j][i]=-1,a[i][i]=0)");
    for(i=0;i<n;i++){
        isExist[i]=1;
        arr[i]=0;//链空
        for(j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }//初始化，并赋值
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
    }//找到初始链(2个元素组成）
    out:
    arr[0]=start;
    arr[1]=end;
    len=1;
    for(;len<n-1;){//链未满就一直循环
        for(j=0;j<n;j++){
            if(isExist[j]==0)
                continue;//如果点不存在，直接跳过
            if(a[end][j]==1){//如果链尾点指向j
                len++;//长度+1
                arr[len]=j;//j接到尾上
                end=j;
                isExist[j]=0;//剔除加入的项
                break;
            }
            else if(a[j][arr[0]]==1){//如果链头被指向
                len++;
                isExist[j]=0;
                for(i=len;i>0;i--){
                    arr[i]=arr[i-1];
                }
                arr[0]=j;//接到头上
                break;
            }
            else {
                for(i=0;i<=len-1;i++){//情况三
                    if(a[arr[i]][j]==1&&a[arr[i+1]][j]==-1){
                        len++;
                        isExist[j]=0;
                        for(k=len;k>i+1;k--){
                            arr[k]=arr[k-1];
                        }
                        arr[i+1]=j;//插到中间
                        break;
                    }
                }
                break;
            }
        }
    }
    for(i=0;i<n-1;i++){
        printf("%d→",arr[i]);
    }
    printf("%d",arr[n-1]);
}
