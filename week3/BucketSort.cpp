#include <iostream>
#include <cstring>
using namespace std;

/*
 • 数组长度为 n, 所有记录区间 [0, m) 上
 • 时间代价:
 – 统计计数:Θ(n+m) ， 输出有序序列时循环 n 次 – 总的时间代价为 Θ(m+n)
 – 适用于 m 相对于 n 很小的情况
 • 空间代价:
 – m 个计数器
 • 稳定
 */

template <class Record> void BucketSort(Record Array[], int n, int max)
{
    int *count = new int[max]; // 桶容量计数器
    memset(count, 0, sizeof(int)*max);
    for (int i = 0; i < n; i++) // 统计每个取值出现的次数
        count[Array[i]]++;
    int k = 0;
    for (int i = 0; i <= max; ++i) {
        while (count[i]) {
            Array[k++] = i;
            count[i]--;
        }
    }
}

int main(int argc, const char *argv[])
{
    int a[7] = {1, 2, 5, 4, 7, 3, 1};
    BucketSort<int>(a, 7, 8);
    for (int i = 0; i < 7; ++i)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
