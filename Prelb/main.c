#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct link
{
    char name[10];
    char trademark[10];
    int price;
    int num;
    struct link *next;
};
struct link *AppendNode(struct link *head);
void Readfile(struct link *head);
void Writefile(struct link *head);
void Searchinformation(struct link *head);
void Inputtheinformation(struct link *head,int x);
struct link *exporttheelectric(struct link *head);
struct link *Importtheelectric(struct link *head);
struct link *Refreshtheinformation(struct link *head);
int Menu(void);
int main()
{
    char ch;
    int x,i;
    struct link *head=NULL;
    printf("the number of electric appliance:\n");
    scanf("%d",&x);
    for(i=0; i<x; i++)
    {
        head=AppendNode(head);
    }
    while(1)
    {
        ch=Menu();
        switch(ch)
        {
        case 1:
            Inputtheinformation(head,x);
            break;
        case 2:
            Writefile(head);
            break;
        case 3:
            Searchinformation(head);
            break;
        case 4:
            Readfile(head);
            break;
        case 5:
            head=Importtheelectric(head);
            break;
        case 6:
            head=exporttheelectric(head);
            break;
        case 7:
            head=Refreshtheinformation(head);
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
    printf("1.Input the information!\n");
    printf("2.WritetoFile!\n");
    printf("3.Search the information!\n");
    printf("4.ReadfromFile!\n");
    printf("5.Import some electric appliances!\n");
    printf("6.export some electric appliances!\n");
    printf("7.refresh some electric appliances!\n");
    printf("0.Exit\n");
    printf("Please Input your choice:");
    scanf("%d",&s);
    return s;
}
struct link *AppendNode(struct link *head)
{
    struct link *p=NULL;
    struct link *pr=head;
    p=(struct link*)malloc(sizeof(struct link));
    if(p==NULL)
    {
        printf("No enough memory to allocate!\n");
        exit(0);
    }
    if(head==NULL)
    {
        head=p;
    }
    else
    {
        while(pr->next!=NULL)
        {
            pr=pr->next;
        }
        pr->next=p;
    }
    p->next=NULL;
    return head;
}
void Searchinformation(struct link *head)
{
    struct link *p=head;
    for(; p!=NULL;)
    {
        printf("名称：%s\t品牌：%s\t价格：%4d\t数量：%3d\t",p->name,p->trademark,p->price,p->num);
        printf("\n");
        p=p->next;
    }
}
void Writefile(struct link *head)
{
    struct link *p=head;
    FILE *fp;
    fp=fopen("informations.txt","w");
    if(fp==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    for(; p!=NULL;)
    {
        fprintf(fp,"%s\t%s\t%d\t%d\t",p->name,p->trademark,p->price,p->num);
        fprintf(fp,"\n");
        p=p->next;
    }
    printf("successful!");
    fclose(fp);
}
void Inputtheinformation(struct link *head,int x)
{
    int i;
    struct link *p=head;
    for(i=0; i<x; i++)
    {
        printf("Input the name:\n");
        scanf("%s",p->name);
        printf("Input the bland:\n");
        scanf("%s",p->trademark);
        printf("Input the price:\n");
        scanf("%d",&p->price);
        printf("Input the number:\n");
        scanf("%d",&p->num);
        p=p->next;
    }
}
void Readfile(struct link *head)
{
    struct link *p=head;
    FILE *fp;
    fp=fopen("informations.txt","r");
    if(fp==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    for(; p!=NULL;)
    {
        fscanf(fp,"%s",p->name);
        fscanf(fp,"%s",p->trademark);
        fscanf(fp,"%d",&p->price);
        fscanf(fp,"%d",&p->num);
        p=p->next;
    }
    printf("successful!");
    fclose(fp);
}
struct link *Importtheelectric(struct link *head)
{
    struct link *pr=head,*p=head,*temp=NULL;
    char it;
    int t;
    char choice1[10],choice2[10];

    printf("do you want to import the new kinds of electric appliance?(Y or N)?\n");
    scanf(" %c",&it);
    if(it=='N')
    {
        printf("Input the name and trademark of the electric appliance you want to import:\n");
        scanf("%s",&choice1);
        scanf("%s",&choice2);
        printf("Input the number of the things you want to import:\n");
        scanf("%d",&t);
        while((strcmp(choice1,p->name)!=0||strcmp(choice2,p->trademark)!=0)&&p->next!=NULL)
        {
            pr=p;
            p=p->next;
        }
        if(strcmp(choice1,p->name)==0&&strcmp(choice2,p->trademark)==0)
        {
            p->num+=t;
        }
        return head;
    }
    else
    {
        p=(struct link *)malloc(sizeof(struct link));
        if(p==NULL)
        {
            printf("No enough memory to allocate!\n");
            exit(0);
        }
        p->next=NULL;
        Inputtheinformation(p,1);
        if(head==NULL)
        {
            head=p;
        }
        else
        {
            while(pr->price<p->price&&pr->next!=NULL)
            {
                temp=pr;
                pr=pr->next;
            }
            if(pr->price>=p->price)
            {
                if(pr==head)
                {
                    p->next=head;
                    head=p;
                }
                else
                {
                    pr=temp;
                    p->next=pr->next;
                    pr->next=p;
                }
            }
            else
            {
                pr->next=p;
            }
        }
        return head;
    }

}
struct link *exporttheelectric(struct link *head)
{
    struct link *p=head,*pr=head;
    char choice1[10],choice2[10];
    int t;
    printf("Input the name and trademark of the electric appliance you want to export:\n");
    scanf("%s",&choice1);
    scanf("%s",&choice2);
    printf("Input the number of the things you want to export:\n");
    scanf("%d",&t);
    while((strcmp(choice1,p->name)!=0||strcmp(choice2,p->trademark)!=0)&&p->next!=NULL)
    {
        pr=p;
        p=p->next;
    }
    if(strcmp(choice1,p->name)==0&&strcmp(choice2,p->trademark)==0)
    {
        p->num-=t;
        if(p->num<=0)
        {
            if(p==head)
            {
                head=p->next;
            }
            else
            {
                pr->next=p->next;
            }
            free(p);
        }
        printf("successful!");
    }
    else
    {
        printf("don't have the electric appliance what you want!\n");
    }
    return head;
}
struct link *Refreshtheinformation(struct link *head)
{
    struct link *p=head,*pr=head;
    char choice1[10],choice2[10],choice3[10],latername[10],latertrademark[10];
    int t1,t2;
    printf("Input the name and trademark of the electric appliance you want to refresh:\n");
    scanf("%s",&choice1);
    scanf("%s",&choice2);
    printf("Input the kind of the things you want to refresh:\n");
    scanf("%s",&choice3);
    while((strcmp(choice1,p->name)!=0||strcmp(choice2,p->trademark)!=0)&&p->next!=NULL)
    {
        pr=p;
        p=p->next;
    }
    if(strcmp(choice1,p->name)==0&&strcmp(choice2,p->trademark)==0)
    {
        if(strcmp(choice3,"name")==0)
        {
            printf("Input the later name:\n");
            scanf("%s",latername);
            strcpy(p->name,latername);
        }
        if(strcmp(choice3,"trademark")==0)
        {
            printf("Input the later trademark:\n");
            scanf("%s",latertrademark);
            strcpy(p->trademark,latertrademark);
        }
        if(strcmp(choice3,"number")==0)
        {
            printf("Input the later numbers:\n");
            scanf("%d",&t1);
            p->num=t1;
        }
        if(strcmp(choice3,"price")==0)
        {
            printf("Input the later prices:\n");
            scanf("%d",&t2);
            p->price=t2;
        }
        if(p->num<=0)
        {
            if(p==head)
            {
                head=p->next;
            }
            else
            {
                pr->next=p->next;
            }
            free(p);
        }
    }
    else
    {
        printf("don't have the electric appliance what you want!\n");
    }
    return head;
}
