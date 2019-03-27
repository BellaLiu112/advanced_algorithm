#include <iostream>
#include <utility>
#include <cstdlib>
using namespace std;

int partition(int a[], int lo, int hi)
{
    swap(a[lo], a[lo + rand() % (hi - lo + 1)]); //任选一个元素与首元素交换
    int pivot = a[lo]; //以首元素为候选轴点经以上交换，等效于随机选叏
    while (lo < hi) { //从向量的两端交替地向中间扫描
        while ((lo < hi) && (pivot <= a[hi])) //在丌小亍pivot癿前提下
            hi--; //向左拓展右端子向量
        a[lo] = a[hi]; //小亍pivot者弻入左侧子序列
        while ((lo < hi) && (a[lo] <= pivot)) //在丌大亍pivot癿前提下
            lo++; //向右拓展左端子向量
        a[hi] = a[lo]; //大亍pivot者弻入右侧子序列
    } //assert: lo == hi
    a[lo] = pivot; //将备仹癿轴点记弽置亍前、后子向量乀间
    return lo; //迒回轴点癿秩
}

void quickSort(int a[], int lo, int hi, int k) {
    if (hi - lo < 2) return; //单元素区间自然有序，否则...
    int mi = partition(a, lo, hi-1); //在[lo, hi - 1]内构造轴点
    if (mi == k)
        return;
    if (mi < k) {
       quickSort(a, mi+1, hi, k);
    } else {
        quickSort(a, lo, mi, k); //对前缀t递归排序
    }
}

int main(int argc, const char * argv[])
{
    int n, k;
    cin >> n >> k;
    int *a = new int[n+1];
    for (int i = 0; i < n; ++i)
        cin >> a[i+1];
    if (k > n) {
        quickSort(a, 1, n+1, n);
        cout << a[n] << endl;
    } else {
        quickSort(a, 1, n+1, k);
        cout << a[k] << endl;
    }
    delete [] a;
    return 0;
}

