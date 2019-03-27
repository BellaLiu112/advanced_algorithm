#include <iostream>
#include <string>
using namespace std;

/*
 输入
 第1行：两个整数n和m，n(0<n<=50)表示字符串长度，m(0<m<=100)表示字符串数量
 
 第2至m+1行：每行是一个长度为n的字符串
 
 输出
 按逆序对数从少到多输出字符串，逆序对数一样多的字符串按照输入的顺序输出。
 */

struct info {
    int index;
    string key;
    int reverseCount;
};

int CountReverse(const string &str, const int &n)
{
    int res = 0;
    char last = 0;
    int count = 0;
    int i, j;
    for (i=0; i < n-1; ++i) {
        if (str[i] == 'A') {
            last = str[i];
            continue;
        } else if (str[i] == last) {
            res += count;
            continue;
        } else {
            count = 0;
            for (j = i+1; j < n; ++j)
                if (str[j] < str[i])
                    count++;
            res += count;
            last = str[i];
        }
    }
    return res;
}

int main(int argc, const char *argv[])
{
    //输入
    int n, m, i, j;
    cin >> n >> m;
    info *dnas = new info[m];
    for (i = 0; i < m; ++i) {
        dnas[i].index = i;
        cin >> dnas[i].key;
        dnas[i].reverseCount = CountReverse(dnas[i].key, n);
    }
    // 按照逆序对数插入排序
    int *IndexArray = new int[m];
    for (i = 0; i < m; ++i)
        IndexArray[i] = i;
    for (i = 1; i < m; ++i) {
        for (j = i; j > 0; j--) {
            if (dnas[IndexArray[j]].reverseCount < dnas[IndexArray[j-1]].reverseCount)
                swap(IndexArray[j-1], IndexArray[j]);
            else
                break;
        }
    }
    for (i = 0; i < m; ++i)
        cout << dnas[IndexArray[i]].key << endl;
    
    delete[] IndexArray;
    delete[] dnas;
    return 0;
}
