#include <iostream>
#include <cstring>
using namespace std;

/*
 改进后的 mergeSort:
 1. 对基本已排序序 列直接插入排序 减少递归的开销
 2. R.Sedgewick 优化:归并时从两端开始 处理，向中间推进，简化边界判断 ModMerge

• 空间代价:Θ(n)
• 划分时间、排序时间、归并时间
T (n)  2T (n / 2)  cn
• T(1) = 1
• 归并排序总时间代价也为
– Θ(nlog n)
• 不依赖于原始数组的输入情况，最大、最小以及平均时
间代价均为 Θ(nlog n)
 */

#define THRESHOLD 32

void insertSort(int Array[], int n)
{
    int current;
    for (int i = 1; i < n; ++i) {
        current = Array[i];
        int j = i;
        while (j >= 1 && current < Array[j-1]) {
            Array[j] = Array[j-1];
            j--;
        }
        Array[j] = current;
    }
}

void Merge(int Array[], int tempArray[], int left, int right, int middle)
{
    for (int i = left; i <= right; ++i)
        tempArray[i] = Array[i];
    int index1 = left;
    int index2 = middle+1;
    int i = left;
    while(index1 <= middle && index2 <= right){
        if (tempArray[index1] < tempArray[index2]){
            Array[i++] = tempArray[index1++];
        } else {
            Array[i++] = tempArray[index2++];
        }
    }
    while(index1 <= middle)
        Array[i++] = tempArray[index1++];
    while(index2 <= right)
        Array[i++] = tempArray[index2++];
}

void ModMerge(int Array[], int tempArray[], int left, int right, int middle)
{
    for (int i = left; i <= middle; ++i)
        tempArray[i] = Array[i];
    for (int j = 1; j < right-middle; ++j)
        tempArray[right-j+1] = Array[middle+j];
    int index1, index2, k;
    for (index1 = left, index2=right, k=left; k <= right; ++k)
        if (tempArray[index1] <= tempArray[index2])
            Array[k++] = tempArray[index1++];
        else
            Array[k++] = tempArray[index2--];
}

void mergeSort(int Array[], int tempArray[], int left, int right)
{
    int middle;
    if (right-left+1 > THRESHOLD) {
        middle = (left + right) / 2;
        mergeSort(Array, tempArray, left, middle);
        mergeSort(Array, tempArray, middle+1, right);
        ModMerge(Array, tempArray, left, right, middle);
    } else {
        insertSort(&Array[left], right-left+1);
    }
}

int main(int argc, const char *argv[])
{
    int a[5] = {1, 3, 4, 2, 5};
    int temp[5] = {0};
    mergeSort(a, temp, 0, 5);
//    insertSort(a, 5);
    for (int i = 0; i < 5; ++i)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
