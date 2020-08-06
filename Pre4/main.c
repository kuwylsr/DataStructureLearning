#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 10
#define M 20
#define W 20
#define N 20
typedef struct institute
{
    char name[MAX_LEN];
    long num;
    long summarkm;
    long summarkw;
    int scoream[M];
    int scoreaw[W];
} INS;
int main()
{
    char ch;
    int n,m,w;
    int scoreb3[M+W][3];
    int scoreb5[M+W][5];
    INS ins[N];
    printf("Input institute number(n<=%d):",N);
    scanf("%d",&n);
    printf("Input m number(n<=%d):",M);
    scanf("%d",&m);
    printf("Input w number(n<=%d):",W);
    scanf("%d",&w);
    while(1)
    {
        ch=Menu();
        switch(ch)
        {
        case 1:
            ReadScore(ins,n,m,w);
            break;
        case 2:
            ReadScorebefore(scoreb3,scoreb5,m,w);
            break;
        case 3:
            Sumofins(ins,n,m,w);
            break;
        case 4:
            Sortbynum(ins,n,m,w);
            Print(ins,n,m,w);
            break;
        case 5:
            Sortbyname(ins,n,m,w);
            Print(ins,n,m,w);
            break;
        case 6:
            Sortbysum(ins,n,m,w);
            Print(ins,n,m,w);
            break;
        case 7:
            Sortbysummarkm(ins,n,m,w);
            Print(ins,n,m,w);
            break;
        case 8:
            Sortbysummarkw(ins,n,m,w);
            Print(ins,n,m,w);
            break;
        case 9:
            SearchbynumaboutS(ins,n,m,w);
            break;
        case 10:
            SearchbynumaboutBs(ins,n,m,w);
            break;
        case 11:
            WritetoFile(ins,n,m,w);
            break;
        case 12:
            ReadfromFile(ins,n,m,w);
            break;
        case 0:
            printf("End of Program!\n");
            exit(0);
        default:
            printf("Input Error!\n");
        }
    }
    return 0;
}
int Menu(void)
{
    int s;
    printf("Management for item\n");
    printf("1.ReadScore\n");
    printf("2.ReadScorebefore\n");
    printf("3.Sumofins\n");
    printf("4.Sortbynum\n");
    printf("5.Sortbyname\n");
    printf("6.Sortbysum\n");
    printf("7.Sortbysumam\n");
    printf("8.Sortbysumaw\n");
    printf("9.SearchbynumaboutS\n");
    printf("10.SearchbynumaboutBs\n");
    printf("11.WritetoFile\n");
    printf("12.ReadfromFile\n");
    printf("0.Exit\n");
    printf("Please Input your choice:");
    scanf("%d",&s);
    return s;
}
void ReadScore(INS ins[],int n,int m,int w)
{
    int i,j;
    printf("Input ins's ID,name,scoream,scoreaw:\n");
    for(i=0; i<n; i++)
    {
        printf("Input the ins's num and name:(%d)\n",n);
        scanf("%ld%s",&ins[i].num,&ins[i].name);
        printf("Input the score of man:(%d)\n",m);
        for(j=0; j<m; j++)
        {
            scanf("%d",&ins[i].scoream[j]);
        }
        printf("Input the score of woman:(%d)\n",w);
        for(j=0; j<w; j++)
        {
            scanf("%d",&ins[i].scoreaw[j]);
        }
    }
}
void ReadScorebefore(int scoreb3[][3],int scoreb5[][5],int m,int w)
{
    int i,j;
    printf("Input every event score about man before top 3:\n");
    for(i=0; i<m; i++)
    {
        for(j=0; j<3; j++)
        {
            scanf("%d",&scoreb3[i][j]);
        }
    }
    printf("Input every event score about woman before top 5:\n");
    for(i=0; i<w; i++)
    {
        for(j=0; j<5; j++)
        {
            scanf("%d",&scoreb5[i][j]);
        }
    }
}
void Sumofins(INS ins[],int n,int m,int w,int scoreb3[][3],int scoreb5[][5])
{
    int i,j;
    for(i=0; i<n; i++)
    {
        for(j=0; j<m; j++)
        {
            if(ins[i].scoream[j]==scoreb3[0])
            {
                ins[i].summarkm+=5;
            }
            if(ins[i].scoream[j]==scoreb3[1])
            {
                ins[i].summarkm+=3;
            }
            if(ins[i].scoream[j]==scoreb3[2])
            {
                ins[i].summarkm+=2;
            }
            if(ins[i].scoreaw==scoreb5[0])
            {
                ins[i].summarkw+=7;
            }
            if(ins[i].scoreaw==scoreb5[1])
            {
                ins[i].summarkw+=5;
            }
            if(ins[i].scoreaw==scoreb5[2])
            {
                ins[i].summarkw+=3;
            }
            if(ins[i].scoreaw==scoreb5[3])
            {
                ins[i].summarkw+=2;
            }
            if(ins[i].scoreaw==scoreb5[4])
            {
                ins[i].summarkw+=1;
            }
        }
        printf("ins %ld: sum=%ld",ins[i].num,ins[i].summarkm+ins[i].summarkw);
    }
}
void Sortbynum(INS ins[],int n,int m,int w)
{
    int i,j,temp,t;
    for(i=0; i<n; i++)
    {
        for(j=1; j<n-i; j++)
        {
            if(ins[j].num<ins[j-1].num)
            {
                for(t=0; t<m; t++)
                {
                    Swapint(&ins[j].scoream[t],&ins[j-1].scoream[t]);
                }
                for(t=0; t<w; t++)
                {
                    Swapint(&ins[j].scoreaw[t],&ins[j-1].scoreaw[t]);
                }
                Swaplong(&ins[j].num,&ins[j-1].num);
                Swapchar(ins[j].name,ins[j-1].name);
            }
        }
    }
}
void Swaplong(long *x,long *y)
{
    long temp;
    temp =*x;
    *x=*y;
    *y=temp;
}
void Swapint(int *x,int *y)
{
    int temp;
    temp =*x;
    *x=*y;
    *y=temp;
}
void Swapchar(char x[],char y[])
{
    char temp[MAX_LEN];
    strcpy(temp,x);
    strcpy(x,y);
    strcpy(y,temp);
}
void Print(INS ins[],int n,int m,int w)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        printf("%ld\t%s\t",ins[i].num,ins[i].name);
        for(j=0;j<m;j++)
        {
            printf("%d\t%d\t",ins[i].scoream[j],ins[i].scoreaw[j]);
        }
        printf("%ld",ins[i].summarkm+ins[i].summarkw);
    }
}
void Sortbyname(INS ins[],int n,int m,int w)
{
    int i,j,t,temp;
    for(i=0;i<n-1;i++)
    {
        for(j=1;j<n-i;j++)
        {
            if(strcmp(ins[j].name,ins[j-1].name)<0)
            {
                for(t=0; t<m; t++)
                {
                    Swapint(&ins[j].scoream[t],&ins[j-1].scoream[t]);
                }
                for(t=0; t<w; t++)
                {
                    Swapint(&ins[j].scoreaw[t],&ins[j-1].scoreaw[t]);
                }
                Swaplong(&ins[j].num,&ins[j-1].num);
                Swapchar(ins[j].name,ins[j-1].name);
            }

        }
    }
}
void Sortbysum(INS ins[],int n,int m,int w)
{
    int i,j,temp,t;
    for(i=0; i<n; i++)
    {
        for(j=1; j<n-i; j++)
        {
            if(ins[j].summarkm+ins[j].summarkw<ins[j-1].summarkm+ins[j-1].summarkw)
            {
                for(t=0; t<m; t++)
                {
                    Swapint(&ins[j].scoream[t],&ins[j-1].scoream[t]);
                }
                for(t=0; t<w; t++)
                {
                    Swapint(&ins[j].scoreaw[t],&ins[j-1].scoreaw[t]);
                }
                Swaplong(&ins[j].num,&ins[j-1].num);
                Swapchar(ins[j].name,ins[j-1].name);
            }
        }
    }
}
void Sortbysummarkm(INS ins[],int n,int m,int w)
{
    int i,j,temp,t;
    for(i=0; i<n; i++)
    {
        for(j=1; j<n-i; j++)
        {
            if(ins[j].summarkm<ins[j-1].summarkm)
            {
                for(t=0; t<m; t++)
                {
                    Swapint(&ins[j].scoream[t],&ins[j-1].scoream[t]);
                }
                for(t=0; t<w; t++)
                {
                    Swapint(&ins[j].scoreaw[t],&ins[j-1].scoreaw[t]);
                }
                Swaplong(&ins[j].num,&ins[j-1].num);
                Swapchar(ins[j].name,ins[j-1].name);
            }
        }
    }
}
void Sortbysummarkw(INS ins[],int n,int m,int w)
{
    int i,j,temp,t;
    for(i=0; i<n; i++)
    {
        for(j=1; j<n-i; j++)
        {
            if(ins[j].summarkw<ins[j-1].summarkw)
            {
                for(t=0; t<m; t++)
                {
                    Swapint(&ins[j].scoream[t],&ins[j-1].scoream[t]);
                }
                for(t=0; t<w; t++)
                {
                    Swapint(&ins[j].scoreaw[t],&ins[j-1].scoreaw[t]);
                }
                Swaplong(&ins[j].num,&ins[j-1].num);
                Swapchar(ins[j].name,ins[j-1].name);
            }
        }
    }
}
void SearchbynumaboutS(INS ins[],int n,int m,int w)
{
    long number;
    int i,j,k;
    printf("Input the number you want to search:");
    scanf("%ld",&number);
    printf("Input the number you want to search:");
    scanf("%d",&k);
    for(i=0;i<n;i++)
    {
        if(ins[i].num==number)
        {
            if(k>=0&&k<=m-1)
            {
                printf("%d",ins[i].scoream[k]);
            }
            if(k>=m&&k<=m+w)
            {
                printf("%d",ins[i].scoreaw[k-m]);
            }
        }
    }
}
void SearchbynumaboutBs(INS ins[],int n,int m,int w,int scoreb3[][3],int scoreb5[][5])
{
    int number;
    int i,j,k;
    printf("Input the number you want to search:");
    scanf("%d",&number);
    for(k=0; k<3; k++)
    {
        for(i=0; i<n; i++)
        {
            if(number>=0&&number<=m-1)
            {
                for(j=0; j<m; j++)
                {
                    if(ins[i].scoream[j]==scoreb3[number][k])
                    {
                        printf(":%s",ins[i].name);
                    }
                }
            }
        }
    }
    for(k=0; k<5; k++)
    {
        for(i=0; i<n; i++)
        {
            if(number>=m&&number<=m+w)
            {
                for(j=0; j<w; j++)
                {
                    if(ins[i].scoreaw[j]==scoreb5[number][k])
                    {
                        printf(":%s",ins[i].name);
                    }
                }
            }
        }
    }
}
void WritetoFile(INS ins[],int n,int m,int w)
{
    FILE *fp;
    int i,j;
    fprintf(fp,"%d\t%d\t%d\t",n,m,w);
    fp=fopen("institutePK.txt","w");
    if(fp==NULL)
    {
        printf("Failure to open institutePK.txt!\n");
        exit(0);
    }
    for(i=0;i<n;i++)
    {
        fprintf(fp,"%5ld%5s",ins[i].num,ins[i].name);
        for(j=0;j<m;j++)
        {
            fprintf(fp,"%d",ins[i].scoream[j]);
        }
        for(j=0;j<w;j++)
        {
            fprintf(fp,"%d",ins[i].scoreaw[j]);
        }
    }
    fclose(fp);
}
void ReadfromFile(INS ins[],int n,int m,int w)
{
    FILE *fp;
    int i,j;
    fp=fopen("institutePK.txt","r");
    if(fp==NULL)
    {
        printf("Failure to open institutePK.txt!\n");
        exit(0);
    }
    fscanf(fp,"%d\t%d\t%d",n,m,w);
    for(i=0;i<n;i++)
    {
        fscanf(fp,"%5ld",&ins[i].num);
        fscanf(fp,"%3s",&ins[i].name);
        for(j=0;j<m;j++)
        {
            fscanf(fp,"%d",ins[i].scoream[j]);
        }
        for(j=0;j<w;j++)
        {
            fscanf(fp,"%d",ins[i].scoreaw[j]);
        }
    }
    fclose(fp);
}
