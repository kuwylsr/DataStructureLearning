#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef char SElemType;
typedef struct node
{
    SElemType data;
    struct node *link;
} LinkNode, *LinkStack;
typedef struct node1
{
    double  data;
    struct node *link;
} LinkNode1, *LinkStack1;
void InitStack(LinkStack *S)
//链式栈初始化：置栈顶指针为空
{
    *S=NULL;
}
int Push(LinkStack *S,SElemType x)
//进栈：将元素x插入到链式栈的栈顶，及链头
{
    LinkNode *p=(LinkNode *)malloc(sizeof(LinkNode));
    p->data=x;
    p->link=*S;
    *S=p;
    return 1;
}
int Pop(LinkStack *S,SElemType *x)
//退栈：若栈空，函数返回0，参数x的值不可用
//若栈不空，则函数返回1，并通过引用参数x返回被删栈顶元素的值
{
    if(*S==NULL)
    {
        return 0;
    }
    LinkNode *p=*S;
    *x=p->data;
    *S=p->link;
    free(p);
    return 1;
}
int GetTop(LinkStack *S,SElemType *x)
//读取栈顶：若栈不空，函数通过引用参数x返回栈顶元素的值
{
    if(*S==NULL)
    {
        return 0;
    }
    *x=(*S)->data;
    return 1;
}
int StackEmpty(LinkStack *S)
//判断栈是否为空：若栈为空，则函数返回1，否则函数返回0；
{
    return *S==NULL;
}
void InitStack1(LinkStack1 *S)
//链式栈初始化：置栈顶指针为空
{
    *S=NULL;
}
int Push1(LinkStack *S,double x)
//进栈：将元素x插入到链式栈的栈顶，及链头
{
    LinkNode1 *p=(LinkNode1 *)malloc(sizeof(LinkNode1));
    p->data=x;
    p->link=*S;
    *S=p;
    return 1;
}
int Pop1(LinkStack1 *S,double *x)
//退栈：若栈空，函数返回0，参数x的值不可用
//若栈不空，则函数返回1，并通过引用参数x返回被删栈顶元素的值
{
    if(*S==NULL)
    {
        return 0;
    }
    LinkNode1 *p=*S;
    *x=p->data;
    *S=p->link;
    free(p);
    return 1;
}
void Comlatevalue(LinkStack1 *S1,char poly[]);
void Altermidtolate(LinkStack *S,char poly[]);
void Computering(LinkStack *S2,char op);
int icp(char ch);
int isp(char ch);
int i=0;
int main()
{
    int flag1=1;
    LinkStack S;
    LinkStack1 S1;
    InitStack1(&S1);
    InitStack(&S);
    char poly[50];
    while(StackEmpty(&S)&&StackEmpty(&S1)&&flag1==1)
    {
        Altermidtolate(&S,poly);
        printf("\n");
        poly[i]='\0';
        printf("计算结果为:\n");
        Comlatevalue(&S1,poly);
        printf("是否继续运行程序?是--1，否--0\n");
        scanf("%d",&flag1);
        InitStack1(&S1);
        InitStack(&S);
        i=0;
    }
    return 0;
}
void Altermidtolate(LinkStack *S,char poly[])
{
    printf("请输入中缀表达式:\n");
    char ch,ch1,op;
    Push(S,'#');
    scanf(" %c",&ch);
    printf("后缀表达式为:\n");
    if(ch=='-')
    {
        poly[0]='0';
        poly[1]=' ';
        scanf("%c",&ch);
        poly[2]=ch;
        poly[3]=' ';
        poly[4]='-';
        printf("-%c",ch);
        i=5;
        scanf("%c",&ch);
    }
    while(ch!='#'||StackEmpty(S)!=1)
    {
        if((ch>='0'&&ch<='9')||ch==' '||ch=='.')
        {
            poly[i]=ch;
            printf("%c",poly[i]);
            i++;
            scanf("%c",&ch);
        }
        else
        {
            GetTop(S,&ch1);
            if(isp(ch1)<icp(ch))
            {
                Push(S,ch);
                scanf("%c",&ch);
            }
            else if(isp(ch1)>icp(ch))
            {
                Pop(S,&op);
                poly[i]=op;
                i++;
                printf("%c",op);
            }
            else
            {
                Pop(S,&op);
                if(op=='(')
                {
                    scanf("%c",&ch);
                }
            }
        }

    }
}
int icp(char ch)
{
    switch(ch)
    {
    case '#':
        return 0;
        break;
    case '(':
        return 8;
        break;
    case '^':
        return 6;
        break;
    case '*':
    case '/':
    case '%':
        return 4;
        break;
    case '+':
    case '-':
        return 2;
        break;
    case ')':
        return 1;
        break;
    }
}
int isp(char ch)
{
    switch(ch)
    {
    case '#':
        return 0;
        break;
    case '(':
        return 1;
        break;
    case '*':
    case '/':
    case '%':
        return 5;
        break;
    case '+':
    case '-':
        return 3;
        break;
    case '^':
        return 7;
        break;
    case ')':
        return 8;
        break;
    }
}
void Comlatevalue(LinkStack1 *S1,char poly[])
{
    double result;
    int a,k;
    double x=(double)(poly[0]-48);
    char ch;
    for(a=0; poly[a]!='\0'; a++)
    {
        if((poly[a]>='0'&&poly[a]<='9')||(poly[a]==' ')||(poly[a]=='.'))
        {
            if((poly[a+1]>='0'&&poly[a+1]<='9'))
            {
                if(poly[a-1]=='+'||poly[a-1]=='*'||poly[a-1]=='/'||poly[a-1]=='%'||poly[a-1]=='^')
                    x=poly[a]-48;
                x=x*10+(double)(poly[a+1]-48);
                continue;
            }
            if(poly[a+1]=='.')
            {
                k=-1;
                if(poly[a-1]=='+'||poly[a-1]=='-'||poly[a-1]=='*'||poly[a-1]=='/'||poly[a-1]=='%'||poly[a-1]=='^')
                x=poly[a]-48;
                do
                {
                    a++;
                    x=x+(poly[a+1]-48)*pow(10,k);
                    k--;
                }
                while(poly[a+2]!=' '&&poly[a+2]!='#');
                continue;
            }
            if(poly[a+1]==' ')
            {
                if((poly[a-1]=='+'||poly[a-1]=='-'||poly[a-1]=='*'||poly[a-1]=='/'||poly[a-1]=='%'||poly[a-1]=='^')&&(a>=1))
                {
                    Push1(S1,poly[a]-48);
                    continue;
                }
                Push1(S1,x);
                x=0;
                continue;
            }
        }
        if(poly[a]=='+'||poly[a]=='-'||poly[a]=='*'||poly[a]=='/'||poly[a]=='%'||poly[a]=='^')
        {
            Computering(S1,poly[a]);
        }
    }
    Pop1(S1,&result);
    printf("%lf\n",result);
}
void Computering(LinkStack *S2,char op)
{
    double L,R;
    if(StackEmpty(S2)==1)
    {
        printf("输入有误，退出程序！");
        exit(0);
    }
    Pop1(S2,&R);
    if(R=='('-48)
    {
        printf("输入有误，退出程序！");
        exit(0);
    }
    if(R==')'-48
    )
    {
        printf("输入有误，退出程序！");
        exit(0);
    }
     if(StackEmpty(S2)==1)
    {
        printf("输入有误，退出程序！");
        exit(0);
    }
    Pop1(S2,&L);
    switch(op)
    {
    case '+' :
        Push1(S2,L+R);
        break;
    case '-' :
        Push1(S2,L-R);
        break;
    case '*':
        Push1(S2,L*R);
        break;
    case '/':
        Push1(S2,L/R);
        break;
    case '%':
        Push1(S2,L-(int)(L/R)*R);
        break;
    case '^':
        Push1(S2,pow(L,R));
    }
}
