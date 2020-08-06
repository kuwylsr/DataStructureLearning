#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,flagloc,flagnum;
    int num[10];
    printf("Please input one hundred numbers:\n");
    for(i=0; i<10; i++)
    {
        scanf("%d",&num[i]);
    }
    flagloc=0;
    flagnum=num[0];
    for(i=0; i<10; i++)
    {
        for(j=0; j<10; j++)
        {
            if(num[i]<num[j])
            {
                break;
            }
            if(j==9)
            {
                flagloc=i;flagnum=num[i];
            }
        }

    }
    printf("%d,%d",flagloc,flagnum);
    return 0;
}
