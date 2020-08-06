#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int i,j,k;
    char a[8][5]= {"PAB","5C","PABC","CXY","CRSI","7","B899","B9"};
    char temp[8][5];
    for(i=0; i<8; i++)
    {
        strcpy(temp[i],a[i]);
    }

    for(i=0; i<7; i++)
    {
        for(k=1; k<8-i; k++)
        {
            for(j=0; (a[k-1][j]!='\0')&&(a[k][j]!='\0'); j++)
            {
                if(a[k][j]<a[k-1][j])
                {
                    if((a[k][j]>=48&&a[k-1][j]>=48&&a[k][j]<=57&&a[k-1][j]<=57)||(a[k][j]>=65&&a[k-1][j]>=65&&a[k][j]<=90&&a[k-1][j]<=90))
                    {
                        strcpy(temp[k],a[k]);
                        strcpy(a[k],a[k-1]);
                        strcpy(a[k-1],temp[k]);
                        break;
                    }

                    else
                    {
                        break;
                    }
                }
                if(a[k][j]==a[k-1][j])
                {
                    continue;
                }
                if(a[k][j]>a[k-1][j])
                {
                    if(a[k-1][j]>=48&&a[k-1][j]<=57&&a[k][j]>=65&&a[k][j]<=90)
                    {
                        strcpy(temp[k],a[k]);
                        strcpy(a[k],a[k-1]);
                        strcpy(a[k-1],temp[k]);
                    }
                    break;
                }
            }
        }
    }
    for(i=0; i<8; i++)
    {
        printf("%s\n",a[i]);
    }
    return 0;
}
