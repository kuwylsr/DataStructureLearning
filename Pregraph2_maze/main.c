#include <stdio.h>
#include <stdlib.h>
#define maxlen 50


/*
  �����������
���Ǽ����յ��ڵ�N�㣬���������������·�����ȿ϶���N���������Nһ����������̵ġ�
�����ü򵥵ķ�֤����֤���������յ��ڵ�N���ϱ߳��ֹ���
�����M�㣬M<N����ô�����������Ĺ����У��϶�������������M��ģ�
��ʱ��������M���ʱ�����յ���ֹ��ˣ���ô���·��Ӧ����M��������N�ˡ�
���Ը��ݹ�����������Ļ����������յ�ʱ����·��һ������̵ġ�
 */

typedef struct node
{
    int x,y;
    int visited;
    int content;
} Node;

int BFS(Node Vs, Node Vd,int n,int dp[][maxlen],Node parent[][maxlen],Node maze[][maxlen])    //Vs���Թ���㣬Vd���Թ��յ�
{
    Node Queue[105];
    int front=0,rear=0;//���׵Ķ���
    Node Vn, Vw;
    int i,j;
    //�˸�����
    int dir[][2] = {  {0, 1}, {1, 0},  {0, -1}, {-1, 0},{-1,1},{-1,-1},{1,1},{1,-1}  };

    //��ʼ״̬�����Ž�����Q
    Queue[rear++]=Vs;
    Vs.visited=1;   //���ýڵ��Ѿ����ʹ��ˣ�
    while (front!=rear)
    {
        //���в�Ϊ�գ�����������

        Vn=Queue[front++];//ȡ�����е�ͷVn
        for(i = 0; i < 8; i++)
        {
            Vw.x=Vn.x+dir[i][0];
            Vw.y=Vn.y+dir[i][1];    //����Vn���ڽڵ㸳��Vw

            if(Vw.x<0||Vw.x>n-1||Vw.y<0||Vw.y>n-1)
            {
                continue;
            }
            else
            {
                 Vw.content=maze[Vw.x][Vw.y].content;
                 Vw.visited=maze[Vw.x][Vw.y].visited;
            }
            if (!Vw.visited&&Vw.content==0)
            {
                //Vw��һ���Ϸ��Ľڵ㲢��Ϊ��ɫ�ڵ�
                dp[Vw.x][Vw.y]=dp[Vn.x][Vn.y]+1;
                parent[Vw.x][Vw.y]=Vn;
                Queue[rear++]=Vw;//�������Q
                Vw.visited=1;                        //���ýڵ���ɫ
                maze[Vw.x][Vw.y].visited=1;
            }
             if (Vw.x == Vd.x&&Vw.y==Vd.y)
            {
               Printrode(maze,dp,parent,n);
                return 1;//����
            }
        }
    }
    return -1;//�޽�
}
void Readfile(Node maze[][maxlen],int n,int dp[][maxlen],Node parent[][maxlen])
{
    FILE *fp;
    int i,j;
    fp=fopen("Square.txt","r");
    if(fp==NULL)
    {
        printf("Failure to open Square.txt!\n");
        exit(0);
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            fscanf(fp,"%d",&maze[i][j].content);
            maze[i][j].visited=0;
            maze[i][j].x=i;
            maze[i][j].y=j;
            dp[i][j]=0;

        }
    }
    parent[i][j].content=0;
    fclose(fp);
}
void Printrode(Node maze[][maxlen],int dp[][maxlen],Node parent[][maxlen],int n)
{
    int j1=maze[n-1][n-1].x;
    int j11;
    int j2=maze[n-1][n-1].y;
    int j22;
    int k1=0;
    int k2=0;
    Node order[maxlen][maxlen];
    printf("The road is:");
    while(j1!=maze[0][0].x&&j2!=maze[0][0].y)
    {
        order[k1][k2]=maze[j1][j2];
        j11=j1;
        j1=parent[j1][j2].x;
        j2=parent[j11][j2].y;
        k1++;
        k2++;
    }
    order[k1][k2]=maze[0][0];
    while(k1>0&&k2>0)
    {
        printf("(%d,%d)->",order[k1][k2].x,order[k1][k2].y);
        k1--;
        k2--;
    }
    printf("(%d,%d)",maze[n-1][n-1].x,maze[n-1][n-1].y);
    printf("\n");
    printf("The length is:%d",dp[n-1][n-1]);
}
int main()
{
    Node maze[maxlen][maxlen];
    int dp[maxlen][maxlen];
    Node parent[maxlen][maxlen];
    int i,j,n;
    printf("The size of the maze:\n");
    scanf("%d",&n);
    Readfile(maze,n,dp,parent);
    BFS(maze[0][0],maze[n-1][n-1],n,dp,parent,maze);
    return 0;
}
