#include <stdio.h>
#define k 5
#define MAXKEY 10000
#define MINKEY -1

typedef int LoserTree[k];   //表示非终端结点，由于y是完全二叉树，所以可以使用一维数组来表示
typedef struct {
    int key;
} ExNode, External[k+1];

External b;                 // 表示败者树的叶子结点
//a0 - a4为5个初始归并段
int a0[] = {10, 15, 16};
int a1[] = {9, 18, 20};
int a2[] = {20, 22, 40};
int a3[] = {6, 15, 25};
int a4[] = {12, 37, 48};

// t0 - t4 用于模拟从初始归并段中读入记录时使用
int t0=0, t1=0, t2=0, t3=0, t4=0;
// 沿从叶子节点b[s]到根节点ls[0]的路径调整败者树
void Adjust(LoserTree ls, int s)
{
    int t = (s+k) / 2;  // t表示s的父节点在ls中的下标 败者树中木有度为1的结点
    while (t > 0) {
        // 判断每一个叶子节点同双亲节点中记录的败者的值相比较，调整败者的值，其中 s 一直表示的都是胜者
        if (b[s].key > b[ls[t]].key) {
            int temp = s;
            s = ls[t]; // 记录胜者的下标
            ls[t] = temp; //更新败者的下标
        }
        t >>= 1;
    }
    // 最终将胜者的值赋给 ls[0]
    ls[0] = s;
}

// 创建败者树
void CreateLoserTree(LoserTree ls)
{
    b[k].key = MINKEY;
    // 设置ls数组中败者的初始值
    for (int i = 0; i < k; i++)
        ls[i] = k;
    //对于每一个叶子节点，调整败者树中非终端节点中记录败者的值
    for (int i=k-1; i >=0; i--)
        Adjust(ls, i);
}

//模拟从外存向内存读入初始归并段中的每一个小部分
void input(int i)
{
    switch (i) {
        case 0:
            if (t0 < 3) {
                b[i].key = a0[t0];
                t0++;
            } else {
                b[i].key = MAXKEY;
            }
            break;
        case 1:
            if (t1 < 3) {
                b[i].key = a1[t1];
                t1++;
            } else {
                b[i].key = MAXKEY;
            }
            break;
        case 2:
            if (t2 < 3) {
                b[i].key = a2[t2];
                t2++;
            } else {
                b[i].key = MAXKEY;
            }
            break;
        case 3:
            if (t3 < 3) {
                b[i].key = a3[t3];
                t3++;
            } else {
                b[i].key = MAXKEY;
            }
            break;
        case 4:
            if (t4 < 3) {
                b[i].key = a4[t4];
                t4++;
            } else{
                b[i].key = MAXKEY;
            }
            break;
        default:
            break;
    }
}

void K_merge(LoserTree ls)
{
    int i;
    // 模拟从外存中的5个初始归并段中向内存t调取数据
    for (i = 0; i <= k; i++)
        input(i);
    // 创建败者树
    for (i = 0; i < k; ++i)
        printf("%d ", b[i].key);
    printf("\n");
    CreateLoserTree(ls);
    //最终的胜者存储在ls[0]中，当其值为MAXKEY时，证明5个零食文件归并结束
    while (b[ls[0]].key != MAXKEY) {
        //输出过程模拟向外存别的操作
        printf("%d ", b[ls[0]].key);
        //就读入后续的记录
        input(ls[0]);
        //根据新读入的记录的关键字的值，重新调整败方树，找出最终的胜者
        Adjust(ls, ls[0]);
    }
}

int main(int argc, const char *argv[])
{
    LoserTree ls;
    K_merge(ls);
    return 0;
}
