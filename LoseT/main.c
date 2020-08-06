// LoseTree.cpp : 定义控制台应用程序的入口点。
//败者树，父节点保存失败者的信息，胜利者继续 比赛
//规定·数字大的为失败者
//败者树也是完全二叉树

#include <stdio.h>
#include <stdlib.h>
#define K   8
//8路平衡归并
#define MEM_SIZE 4
//内存最多存储3组数据.(多加了一个最大值数据）
#define INT_MAX 9999999
#define INT_MIN -9999999


typedef int LoseTree[K];
//败者树的非终端节点
typedef struct ExNode{
    //败者树的叶子节点
    int key;
}External;

//测试数组,假设 内存只能 放入 3组数据，并且 内存 已经将这些数据排好序了。
//现在 需要归并这些数据
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
//调整函数，和所有祖先比较，替换败者和最终胜利者T[0]
void createTree(LoseTree  T,External  exnode[]);
//创建败者树
void inputNewKey(External exnode[],int winIndex);

//归并函数
int main()
{
    LoseTree T;//非叶子节点
    External exnode[K+1];//叶子节点
    createTree(T,exnode);
    int winIndex = T[0];//胜利者 坐标
    while (exnode[winIndex].key != INT_MAX){
        printf("%d\t",exnode[winIndex].key);
        inputNewKey(exnode,winIndex);
        adjust(T,exnode,winIndex);
        winIndex = T[0];
    }
    return 0;
}
void createTree(LoseTree  T,External  exnode[])
//创建败者树..
{
    int i;
    for (i = 0; i < K; i++)      //初始化叶子节点
    {
        exnode[i].key = testArray[i][0];
    }
    exnode[K].key = INT_MIN;//为了让第一次 所有 都是 失败者
    for (i = 0; i < K; i++)  //初始化非叶子节点
    {
        T[i] = K;
    }
    for (i = K-1; i >= 0; i--){//调整叶子节点，顺序不能反
        adjust(T,exnode,i);
    }
}

void adjust(LoseTree T,External exnode[],int i)
//调整函数，和所有祖先比较，替换败者和最终胜利者T[0]
{
    int f = (i + K) / 2;
    while (f > 0){
        if (exnode[i].key > exnode[T[f]].key){ //非叶结点和叶结点比较key，若叶结点key大则互换位置
            int temp = i;
            i = T[f];//i 保存 胜利者，继续 比较
            T[f] = temp;//有新的败者了.
        }
        f = f / 2;
    }
    T[0] = i;//最终胜利者
}
void inputNewKey(External exnode[],int winIndex)
//补充选手
{
    int i;
    exnode[winIndex].key = testArray[winIndex][1];
    //前移
    for (i = 0; i < MEM_SIZE -1; i++){
        testArray[winIndex][i] = testArray[winIndex][i+1];
    }
}
