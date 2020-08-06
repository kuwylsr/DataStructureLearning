// LoseTree.cpp : �������̨Ӧ�ó������ڵ㡣
//�����������ڵ㱣��ʧ���ߵ���Ϣ��ʤ���߼��� ����
//�涨�����ִ��Ϊʧ����
//������Ҳ����ȫ������

#include <stdio.h>
#include <stdlib.h>
#define K   8
//8·ƽ��鲢
#define MEM_SIZE 4
//�ڴ����洢3������.(�����һ�����ֵ���ݣ�
#define INT_MAX 9999999
#define INT_MIN -9999999


typedef int LoseTree[K];
//�������ķ��ն˽ڵ�
typedef struct ExNode{
    //��������Ҷ�ӽڵ�
    int key;
}External;

//��������,���� �ڴ�ֻ�� ���� 3�����ݣ����� �ڴ� �Ѿ�����Щ�����ź����ˡ�
//���� ��Ҫ�鲢��Щ����
static int testArray[K][MEM_SIZE] = {
    {10,15,16,INT_MAX},
    {9,20,38,INT_MAX},
    {20,20,30,INT_MAX},
    {6,15,25,INT_MAX},
    {8,15,20,INT_MAX},
    {9,11,16,INT_MAX},
    {90,100,110,INT_MAX},
    {17,18,20,INT_MAX},
};

void adjust(LoseTree T,External exnode[],int i);
//�������������������ȱȽϣ��滻���ߺ�����ʤ����T[0]
void createTree(LoseTree  T,External  exnode[]);
//����������
void inputNewKey(External exnode[],int winIndex);

//�鲢����
int main()
{
    LoseTree T;//��Ҷ�ӽڵ�
    External exnode[K+1];//Ҷ�ӽڵ�
    createTree(T,exnode);
    int winIndex = T[0];//ʤ���� ����
    while (exnode[winIndex].key != INT_MAX){
        printf("%d\t",exnode[winIndex].key);
        inputNewKey(exnode,winIndex);
        adjust(T,exnode,winIndex);
        winIndex = T[0];
    }
    return 0;
}
void createTree(LoseTree  T,External  exnode[])
//����������..
{
    int i;
    for (i = 0; i < K; i++)      //��ʼ��Ҷ�ӽڵ�
    {
        exnode[i].key = testArray[i][0];
    }
    exnode[K].key = INT_MIN;//Ϊ���õ�һ�� ���� ���� ʧ����
    for (i = 0; i < K; i++)  //��ʼ����Ҷ�ӽڵ�
    {
        T[i] = K;
    }
    for (i = K-1; i >= 0; i--){//����Ҷ�ӽڵ㣬˳���ܷ�
        adjust(T,exnode,i);
    }
}

void adjust(LoseTree T,External exnode[],int i)
//�������������������ȱȽϣ��滻���ߺ�����ʤ����T[0]
{
    int f = (i + K) / 2;
    while (f > 0){
        if (exnode[i].key > exnode[T[f]].key){ //��Ҷ����Ҷ���Ƚ�key����Ҷ���key���򻥻�λ��
            int temp = i;
            i = T[f];//i ���� ʤ���ߣ����� �Ƚ�
            T[f] = temp;//���µİ�����.
        }
        f = f / 2;
    }
    T[0] = i;//����ʤ����
}
void inputNewKey(External exnode[],int winIndex)
//����ѡ��
{
    int i;
    exnode[winIndex].key = testArray[winIndex][1];
    //ǰ��
    for (i = 0; i < MEM_SIZE -1; i++){
        testArray[winIndex][i] = testArray[winIndex][i+1];
    }
}
