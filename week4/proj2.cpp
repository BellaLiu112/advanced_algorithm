#include <iostream>
using namespace std;


/*
 描述
 给定一个整数数组，要求对数组中的元素构建败方树（数组相邻元素两两比较，从第一个元素开始）。之后修改数组中的元素，要求输出初始构建以及修改后得到的败方树的所有内部结点代表的整数(从左到右从上到下输出）
 
 输入
 第一行为数组的元素个数n和修改的次数m。
 
 第二行为n个整数，即数组的元素。
 
 接下来m行代表m次修改操作，每次操作修改数组中的一个元素，每一行包括两个整数，第一个为被修改元素在数组中的标号，第二个为修改之后的元素值。
 
 输出
 输出m+1行。
 
 第一行为初始构建的败方树的所有内部结点代表的整数(按照树的结点从左到右从上到下的顺序输出）
 
 接下来m行为接下来m次修改后得到的败方树的所有内部结点代表的整数(按照树的结点从左到右从上到下的顺序输出）
 
 
 样例输入
 8 1
 10 9 20 6 16 12 90 17
 3 15
 
 样例输出
 6 12 9 17 10 20 16 90
 9 12 15 17 10 20 16 90

 */

void build_loser_tree(int *addr, int *parent_node, int n)
{
    int parent_idx, parent_value;
    int child_idx, child_value;
    int loser_idx, suc_idx=n;
    for (int i = n-1; i >= 0; --i) {
        child_idx = i;
        child_value = addr[i];
        parent_idx = (i+n) >> 1;
        parent_value = addr[parent_node[parent_idx]];
        loser_idx = i;
        while (parent_idx > 0) {
            if (parent_value >= child_value) {
                parent_idx >>= 1;
                parent_value = addr[parent_node[parent_idx]];
                continue;
            }
            loser_idx = child_idx;
            suc_idx = parent_node[parent_idx];
            parent_node[parent_idx] = loser_idx;
            parent_idx >>= 1;
            child_idx = suc_idx;
            child_value = addr[suc_idx];
            parent_value = addr[parent_node[parent_idx]];
        }
    }
    parent_node[0] = suc_idx;
}

void modification(int *addr, int *parent_node, int n, int idx, int value)
{
    addr[idx] =  value;
    int parent_idx = (n + idx) >> 1;
    int parent_value = addr[parent_node[parent_idx]];
    int child_idx = idx, child_value = value;
    int loser_idx=idx, suc_idx=idx;
    while (parent_idx > 0) {
        if (parent_value >= child_value) {
            parent_idx >>= 1;
            parent_value = addr[parent_node[parent_idx]];
            continue;
        }
        loser_idx = child_idx;
        suc_idx = parent_node[parent_idx];
        parent_node[parent_idx] = loser_idx;
        parent_idx >>= 1;
        child_idx = suc_idx;
        child_value = addr[suc_idx];
        parent_value = addr[parent_node[parent_idx]];
    }
    parent_node[0] = suc_idx;
}


int main(int argc, const char *argv[])
{
    int n, m;
    cin >> n >> m;
    int *a = new int[n+1];
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    a[n] = 1 << 31;
    int *parent_nodes = new int[n];
    for (int i = 0; i < n; ++i)
        parent_nodes[i] = n;
    build_loser_tree(a, parent_nodes, n);
    for (int i = 0; i < n; ++i)
        cout << a[parent_nodes[i]] << " ";
    cout << endl;
    int modi_idx, modi_value;
    for (int j = 0; j < m; ++j) {
        cin >> modi_idx >> modi_value;
        modification(a, parent_nodes, n, modi_idx, modi_value);
        for (int i = 0; i < n; ++i)
            cout << a[parent_nodes[i]] << " ";
        cout << endl;
    }
    return 0;
}


