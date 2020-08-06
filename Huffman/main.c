#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//1.�������³��ֵ��ַ�������ָ��ʣ�Ȩֵ����Huffman��HT
//2.����Huffman��HT��Huffman�����HC

//3.���룺��Huffman�������Ѱ��Ŀ���ַ�������ת��Ϊ������еı��봮
//4.���룺��������Huffman���룬��0����֧����1����֧���ߵ�Ҷ��������ַ����Դ�����ֱ����ȡ����



//n��������������������2n-1�����
#define leafNumber 128 //Ĭ��Ȩֵ���ϴ�С
#define totalNumber 255//��������=2*leafNumber-1
#define maxWeight 32767//������Ȩֵ�����ֵ
#define N 128
#define MAX_text 999999

//Huffman���Ľṹ����
typedef struct
{
    char data;    //����ֵ
    int weight;    //����Ȩ
    int parent,lchild,rchild; //˫�ס�������Ů���ָ��
}HTNode;
typedef struct
{
    HTNode elem[totalNumber];  //Huffman���洢����
    int num,root; //num����������root�Ǹ�
}HFTree;

//Huffman�����Ľṹ����
typedef struct
{
    char ch; //�洢��������ַ�
    char bits[N+1]; //�ַ�����λ��
}CodeNode;
typedef struct
{
    CodeNode HuffmanCode[N];
}HCode;

void createHFTree(HFTree *HT,char value[],int fr[]);
//��������value[]����Ӧ��Ȩֵfr[n],���������������ʾ��Huffman��HT
void SetChart_HuffmanEncoding(HFTree HT,HCode *HC);
//����Huffman��HT��Huffman�����HC
void Encoding_EnglishStory(char Story[],HCode HC);
//��Ӣ�����µ�ÿ���ַ����������
void Decoding_binarycoding(char binary[],HFTree HT);
//�����µĶ����Ʊ������ԭ�ַ�
void Compress_binarycoding(char binary[]);
//ѹ�����µĶ����Ʊ����ļ�
void Readfile_EnglishStory(char Story[],char value[],int fr[]);
//����һƪӢ�����²�ͳ�Ƹ����ַ����ֵĸ���
void Readfile_binarycoding(char binary[]);
//�������µĶ����Ʊ���
void Writefile_Ebinarycoding(char s[],int flag);
//��ÿ���ַ��ı���д���ļ�
void Writefile_DEnglishStory(char s,int flag);
//�������ԭ�ַ�д���ļ�
void Writefile_Pbinarycoding(char s,int flag);
//��ѹ������ַ�д���ļ�
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
//��������value[]����Ӧ��Ȩֵfr[n],���������������ʾ��Huffman��HT
{
    int i,k,s1,s2;// s1 Ϊ��Сֵ��Ӧ�ı�� ��s2Ϊ��Сֵ��Ӧ�ı��
    int min1,min2; //min1ΪȨֵ�е���Сֵ��min2ΪȨֵ�еĴ�Сֵ
    for(i=0;i<N;i++)   //�������㸳ֵ
    {
        (*HT).elem[i].data=value[i];
        (*HT).elem[i].weight=fr[i];
    }
    for(i=0;i<255;i++) //����ָ���ÿ�
    {
        (*HT).elem[i].parent=-1;
        (*HT).elem[i].lchild=-1;
        (*HT).elem[i].rchild=-1;
    }
    for(i=N;i<2*N-1;i++) //�𲽹���Huffman��
    {
        min1=maxWeight;
        min2=maxWeight;
        s1=0;
        s2=0;
        for(k=0;k<i;k++)//����Huffman���Ĺ���
        {
            if((*HT).elem[k].parent==-1)//������Ϊk�Ľ��δ��Ϊ�������Ľ��
            {
                if((*HT).elem[k].weight<min1)//������Ϊk�Ľ���Ȩֵ����С��
                {
                    //����С��Ȩֵ����С��Ȩֵ����Ӧ����С��ţ���С������θ���
                    min2=min1;
                    s2=s1;
                    min1=(*HT).elem[k].weight;
                    s1=k;
                }
                else if((*HT).elem[k].weight<min2)//������Ϊk�Ľ���Ȩֵ�Ǵ�С��
                {
                    //����С��Ȩֵ����Ӧ�Ĵ�С�ı�����θ���
                    min2=(*HT).elem[k].weight;
                    s2=k;
                }
            }
        }
        //���ӳ�������������
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
//����Huffman��HT��Huffman�����HC
{
    int c,p; //c��p�ֱ�ָʾHT�к��Ӻ�˫�׵�λ�ñ��
    int i;
    char cd[N+1]; //��ʱ��ű���
    int start; //ָʾ������cd�е�λ��
    cd[N]='\0'; //���������
    for(i=0; i<N; i++) //������Ҷ��HT.elem[i]�ı���
    {
                (*HC).HuffmanCode[i].ch=HT.elem[i].data; //����Ҷ��HT.elem[i]����Ӧ���ַ�
                start=N; //������ʼλ�õĳ�ֵ
                c=i; //��Ҷ��HT.elem[i]��ʼ����
                while((p=HT.elem[c].parent)>=0) //ֱ�����ݵ�T[c]������λ��
                {
//                    cd[--start]=(HT.elem[p].lchild==c)?'0':'1';
                    if(HT.elem[p].lchild==c) //��HT.elem[c]��HT.elem[p]�����ӣ������ɴ���0���������ɴ���1
                    {
                        cd[--start]='0';
                    }
                    else
                    {
                        cd[--start]='1';
                    }
                    c=p; //��������
                }
                strcpy((*HC).HuffmanCode[i].bits,&cd[start]); //���Ʊ���Ϊ�ַ��� �ڱ����HC
    }
}
void Encoding_EnglishStory(char Story[],HCode HC)
//��Ӣ�����µ�ÿ���ַ����������
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
//�����µĶ����Ʊ������ԭ�ַ�
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
//ѹ�����µĶ����Ʊ����ļ�
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
//����һƪӢ�����²�ͳ�Ƹ����ַ����ֵĸ���
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
//�������µĶ����Ʊ���
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
//��ÿ���ַ��ı���д���ļ�
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
//�������ԭ�ַ�д���ļ�
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
//��ѹ������ַ�д���ļ�
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
