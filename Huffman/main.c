#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//1.根据文章出现的字符及其出现概率（权值）建Huffman树HT
//2.根据Huffman树HT求Huffman编码表HC

//3.编码：在Huffman编码表中寻找目的字符，将其转换为编码表中的编码串
//4.译码：读二进制Huffman编码，读0走左支，读1走右支，走到叶结点便读出字符，以此类推直到读取结束



//n个外结点的扩充二叉树共有2n-1个结点
#define leafNumber 128 //默认权值集合大小
#define totalNumber 255//树结点个数=2*leafNumber-1
#define maxWeight 32767//比所有权值更大的值
#define N 128
#define MAX_text 999999

//Huffman树的结构定义
typedef struct
{
    char data;    //结点的值
    int weight;    //结点的权
    int parent,lchild,rchild; //双亲、左、右子女结点指针
}HTNode;
typedef struct
{
    HTNode elem[totalNumber];  //Huffman树存储数组
    int num,root; //num是外结点数，root是根
}HFTree;

//Huffman编码表的结构定义
typedef struct
{
    char ch; //存储被编码的字符
    char bits[N+1]; //字符编码位串
}CodeNode;
typedef struct
{
    CodeNode HuffmanCode[N];
}HCode;

void createHFTree(HFTree *HT,char value[],int fr[]);
//输入数据value[]和相应的权值fr[n],构造用三叉链表表示的Huffman树HT
void SetChart_HuffmanEncoding(HFTree HT,HCode *HC);
//根据Huffman树HT求Huffman编码表HC
void Encoding_EnglishStory(char Story[],HCode HC);
//将英文文章的每个字符编二进制码
void Decoding_binarycoding(char binary[],HFTree HT);
//将文章的二进制编码译成原字符
void Compress_binarycoding(char binary[]);
//压缩文章的二进制编码文件
void Readfile_EnglishStory(char Story[],char value[],int fr[]);
//读出一篇英文文章并统计各个字符出现的概率
void Readfile_binarycoding(char binary[]);
//读出文章的二进制编码
void Writefile_Ebinarycoding(char s[],int flag);
//将每个字符的编码写入文件
void Writefile_DEnglishStory(char s,int flag);
//将译出的原字符写入文件
void Writefile_Pbinarycoding(char s,int flag);
//将压缩后的字符写入文件
int main()
{
    HFTree HT;
    HCode HC;
    int i;
    char Story[MAX_text];
    char value[128];
    char binary[MAX_text];
    int fr[128];
    for(i=0;i<N;i++)
    {
        value[i]=i;
        fr[i]=0;
    }
    Readfile_EnglishStory(Story,value,fr);
    createHFTree(&HT,value,fr);
    SetChart_HuffmanEncoding(HT,&HC);
    Encoding_EnglishStory(Story,HC);
    Readfile_binarycoding(binary);
    Decoding_binarycoding(binary,HT);
    Compress_binarycoding(binary);
    return 0;
}
void createHFTree(HFTree *HT,char value[],int fr[])
//输入数据value[]和相应的权值fr[n],构造用三叉链表表示的Huffman树HT
{
    int i,k,s1,s2;// s1 为最小值对应的标号 ，s2为次小值对应的标号
    int min1,min2; //min1为权值中的最小值，min2为权值中的次小值
    for(i=0;i<N;i++)   //所有外结点赋值
    {
        (*HT).elem[i].data=value[i];
        (*HT).elem[i].weight=fr[i];
    }
    for(i=0;i<255;i++) //所有指针置空
    {
        (*HT).elem[i].parent=-1;
        (*HT).elem[i].lchild=-1;
        (*HT).elem[i].rchild=-1;
    }
    for(i=N;i<2*N-1;i++) //逐步构造Huffman树
    {
        min1=maxWeight;
        min2=maxWeight;
        s1=0;
        s2=0;
        for(k=0;k<i;k++)//构造Huffman树的过程
        {
            if((*HT).elem[k].parent==-1)//如果标号为k的结点未成为其他树的结点
            {
                if((*HT).elem[k].weight<min1)//如果标号为k的结点的权值是最小的
                {
                    //将最小的权值，次小的权值，相应的最小标号，次小标号依次更新
                    min2=min1;
                    s2=s1;
                    min1=(*HT).elem[k].weight;
                    s1=k;
                }
                else if((*HT).elem[k].weight<min2)//如果标号为k的结点的权值是次小的
                {
                    //将次小的权值，相应的次小的标号依次更新
                    min2=(*HT).elem[k].weight;
                    s2=k;
                }
            }
        }
        //连接成树，构造子树
        (*HT).elem[s1].parent=i;
        (*HT).elem[s2].parent=i;
        (*HT).elem[i].lchild=s1;
        (*HT).elem[i].rchild=s2;
        (*HT).elem[i].weight=(*HT).elem[s1].weight+(*HT).elem[s2].weight;
    }
    (*HT).num=N;
    (*HT).root=2*N-2;
}
void SetChart_HuffmanEncoding(HFTree HT,HCode *HC)
//根据Huffman树HT求Huffman编码表HC
{
    int c,p; //c和p分别指示HT中孩子和双亲的位置标号
    int i;
    char cd[N+1]; //临时存放编码
    int start; //指示编码在cd中的位置
    cd[N]='\0'; //编码结束符
    for(i=0; i<N; i++) //依次求叶子HT.elem[i]的编码
    {
                (*HC).HuffmanCode[i].ch=HT.elem[i].data; //读入叶子HT.elem[i]所对应的字符
                start=N; //编码起始位置的初值
                c=i; //从叶子HT.elem[i]开始上溯
                while((p=HT.elem[c].parent)>=0) //直到上溯的T[c]是树根位置
                {
//                    cd[--start]=(HT.elem[p].lchild==c)?'0':'1';
                    if(HT.elem[p].lchild==c) //若HT.elem[c]是HT.elem[p]的左孩子，则生成代码0，否则生成代码1
                    {
                        cd[--start]='0';
                    }
                    else
                    {
                        cd[--start]='1';
                    }
                    c=p; //继续上溯
                }
                strcpy((*HC).HuffmanCode[i].bits,&cd[start]); //复制编码为字符串 于编码表HC
    }
}
void Encoding_EnglishStory(char Story[],HCode HC)
//将英文文章的每个字符编二进制码
{
    int i,j;
    for(i=0;i<=strlen(Story)-1;i++)
    {
        for(j=0;j<128;j++)
        {
            if(HC.HuffmanCode[j].ch==Story[i])
            {
                Writefile_Ebinarycoding(HC.HuffmanCode[j].bits,i);
            }
        }
    }
}
void Decoding_binarycoding(char binary[],HFTree HT)
//将文章的二进制编码译成原字符
{
    int i,flag=0;
    HTNode c=HT.elem[HT.root];
    for(i=0;i<=strlen(binary)-1;i++)
    {
        if(binary[i]=='0')
        {
            c=HT.elem[c.lchild];
        }
        if(binary[i]=='1')
        {
            c=HT.elem[c.rchild];
        }
        if(c.lchild==-1&&c.rchild==-1)
        {
            Writefile_DEnglishStory(c.data,flag);
            flag=1;
            c=HT.elem[HT.root];
        }
    }
}
void Compress_binarycoding(char binary[])
//压缩文章的二进制编码文件
{
    char s=0;
    int i,num=0,flag=0;
    for(i=0;i<=strlen(binary)-1;i++)
    {
        if(num<8)
        {
            s=s|(binary[i]-48);
            num++;
            if(num<8)
            s=s<<1;
        }
        if(num==8)
        {
        num=0;
        Writefile_Pbinarycoding(s,flag);
        flag=1;
        s=0;
        }
        if(i==strlen(binary)-1&&num<8&&num>0)
        {
            Writefile_Pbinarycoding(s,flag);
        }
    }
}
void Readfile_EnglishStory(char Story[],char value[],int fr[])
//读出一篇英文文章并统计各个字符出现的概率
{
    FILE *fp;
    int i,j;
    char name[100];
    printf("Input the article's name which you want to read:\n");
    scanf("%s",name);
    fp=fopen(name,"r");
    if(fp==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    for(i=0;!feof(fp);i++)
    {
        fscanf(fp,"%c",&Story[i]);
        for(j=0;j<128;j++)
        {
            if(Story[i]==j)
            {
                fr[j]++;
            }
        }
    }
    fclose(fp);
}
void Readfile_binarycoding(char binary[])
//读出文章的二进制编码
{
    FILE *fp;
    int i;
    char name[100];
    printf("Please input the binarycoding file's name which you want to read:\n");
    scanf("%s",name);
    fp=fopen(name,"r");
    if(fp==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    for(i=0;!feof(fp);i++)
    {
        fscanf(fp,"%c",&binary[i]);
    }
    fclose(fp);
}
void Writefile_Ebinarycoding(char s[],int flag)
//将每个字符的编码写入文件
{
    FILE *fp;
    char name[100];
    if(flag==0)
    {
        printf("Please input the Encoding file's name which you want to write:\n");
        scanf("%s",name);
        fp=fopen(name,"w");
    }
    else
    fp=fopen(name,"a");
    if(fp==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    fprintf(fp,"%s",s);
    fclose(fp);
}
void Writefile_DEnglishStory(char s,int flag)
//将译出的原字符写入文件
{
    FILE *fp;
    char name[100];
    if(flag==0)
    {
        printf("Please input the Decoding file's name which you want to write:\n");
        scanf("%s",name);
        fp=fopen(name,"w");
    }
    else
    fp=fopen(name,"a");
    if(fp==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    fprintf(fp,"%c",s);
    fclose(fp);
}
void Writefile_Pbinarycoding(char s,int flag)
//将压缩后的字符写入文件
{
    FILE *fp;
    char name[100];
    if(flag==0)
    {
        printf("Please input the Pressed file's name which you want to write:\n");
        scanf("%s",name);
        fp=fopen(name,"w");
    }
    else
    fp=fopen(name,"a");
    if(fp==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    fwrite(&s,sizeof(char),1,fp);
    fclose(fp);
}
