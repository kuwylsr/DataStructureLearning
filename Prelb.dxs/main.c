#include <stdio.h>
#include <stdlib.h>

typedef struct polynode
{
    double coef;
    int exp;
    struct polynode *next;
} Term;
void Input(struct polynode * pl,double C[],int E[],int n);
void Multi(struct polynode * pl1,struct polynode * pl2,struct polynode * pl3);
void print(struct polynode * P);
int main()
{
    int p1,p2,i;
    struct polynode * head1=(Term *)malloc(sizeof(Term));
    head1->next=NULL;
    struct polynode * head2=(Term *)malloc(sizeof(Term));
    head2->next=NULL;
    struct polynode * head3=(Term *)malloc(sizeof(Term));
    head3->next=NULL;
    double c1[10];
    int e1[10];
    double c2[10];
    int e2[10];
    printf("Input the number of the part in the first poly:\n");
    scanf("%d",&p1);
    for(i=0; i<p1; i++)
    {
        printf("Input the coef:\n");
        scanf("%lf",&c1[i]);
        printf("Input the exp:\n");
        scanf("%d",&e1[i]);
    }
    printf("Input the number of the part in the second poly:\n");
    scanf("%d",&p2);
    for(i=0; i<p2; i++)
    {
        printf("Input the coef:\n");
        scanf("%lf",&c2[i]);
        printf("Input the exp:\n");
        scanf("%d",&e2[i]);
    }
    Input(head1,c1,e1,p1);
    Input(head2,c2,e2,p2);
    Multi(head1,head2,head3);
    print(head3);
    return 0;
}
void Input (struct polynode *pl,double C[],int E[],int n)
{
   struct polynode *newterm ,*p,*pre;
   int i;
   for(i=0;i<n;i++)
   {
       p=pl->next;
       pre=pl;
       while(p!=NULL&&p->exp<E[i])
       {
           pre=p;
           p=p->next;
       }
       if(p!=NULL&&p->exp==E[i])
       {
           printf("已有与指数%d相等的项，输入作废\n",E[i]);
       }
       else
       {
           newterm=(Term*)malloc(sizeof(Term));
           newterm->coef=C[i];
           newterm->exp=E[i];
           newterm->next=p;
           pre->next=newterm;
       }
   }
}
void Multi(struct polynode * pl1,struct polynode * pl2,struct polynode * pl3)
{
    Term *pa,*pb,*t,*pr,*p,*q;
    int k;
    pa=pl1->next;
    t=pl3;
    while(pa!=NULL)
    {
        pb=pl2->next;
        while(pb!=NULL)
        {
            k=pa->exp+pb->exp;
            pr=t;
            p=pr->next;
            while(p!=NULL&&p->exp<k)
            {
                pr=p;
                p=p->next;
            }
            if(p==NULL||p->exp>k)
            {
                q=(Term *)malloc(sizeof(Term));
                q->next=p;
                pr->next=q;
                q->coef=pa->coef*pb->coef;
                q->exp=k;
            }
            else
            {
                p->coef+=pa->coef*pb->coef;
                if(fabs(p->coef)<0.001)
                {
                    pr->next=p->next;
                    free(p);
                }
            }
            pb=pb->next;
        }
        pa=pa->next;
        t=t->next;
    }

}
void print(struct polynode *P)
{
   struct polynode *p=P->next;
   printf("The result is:\n");
   int h=1;
   while(p!=NULL)
   {
       if(h==1)
       {
           if(p->coef<0)
            printf("-");
           h=0;
       }
       else
       {
           if(p->coef>0)
            printf("+");
           else
            printf("-");
       }
       if(p->exp==0||fabs(p->coef)!=1)
        printf("%lf",fabs(p->coef));
       switch(p->exp)
       {
           case 0:break;
           case 1:printf("X");
           break;
           default:printf("X^%d",p->exp);
       }
       p=p->next;

   }
   printf("\n");
}
