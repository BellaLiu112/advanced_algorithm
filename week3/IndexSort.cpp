#include <iostream>
#include <utility>
using namespace std;

template <class Record>
void AddrSort(Record Array[], int n)
{
    int *IndexArray = new int[n];
    int i,j,k;
    Record TempRec; //只需一个临时空间
    for (i=0; i<n; i++)
        IndexArray[i] = i;
    for (i=1; i<n; i++)// 依次插入第i个记录
        for (j=i; j>0; j--) // 依次比较，发现逆置就交换
            if ( Array[IndexArray[j]] <Array[IndexArray[j-1]])
                swap(IndexArray[j], IndexArray[j-1]);
            else break; //此时i前面记录已排序
    for(i=0;i<n;i++) { // 调整为按下标有序
        j= i;
        TempRec = Array[i];
        while (IndexArray[j] != i) {
            k=IndexArray[j];
            Array[j]=Array[k];
            IndexArray[j] = j;
            j = k;
        }
        Array[j] =TempRec;
        IndexArray[j] = j;
    }
}

int main(int argc, const char *argv[])
{
    int a[8] = {29, 25, 34, 64, 34, 12, 32, 45};
    AddrSort<int>(a, 8);
    return 0;
}
