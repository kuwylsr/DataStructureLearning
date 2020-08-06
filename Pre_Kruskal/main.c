#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define maxSize 20
#define maxValue 32767

typedef double WeightType;
typedef struct
{
    int x,y;
}point;
typedef struct
{
    point v1,v2;
    WeightType cost;
}MSTEdgeNode;
typedef struct
{
    MSTEdgeNode edgeValue[maxSize];
    int n;
}MinSpanTree;

int Read(MSTEdgeNode EV[])
{
    FILE *fp;
    int i,j,n;
    fp=fopen("Bridge.txt","r");
    if(fp==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    fscanf(fp,"%d",&(n));
    for(i=0;!feof(fp);i++)
    {
        fscanf(fp,"%d,%d %d,%d",EV[i].v1.x,EV[i].v1.y,EV[i].v2.x,EV[i].v2.y);
    }
    for(i=0;i<(n*(n-1))/2;i++)
    {
        EV[i].cost=sqrt((EV[i].v1.x-EV[i].v2.x)*(EV[i].v1.x-EV[i].v2.x)+(EV[i].v1.y-EV[i].v2.y)*(EV[i].v1.y-EV[i].v2.y));
    }
        return n;
    fclose(fp);
}
int main()
{
    printf("Hello world!\n");
    return 0;
}
