#include <iostream>
#include <cstring>
using namespace std;

class loser_heap {
    int capacity;
    int size;
    int *addr;
public:
    loser_heap( ) {capacity=0; size=0; addr=NULL;}
    void build_heap(int *a, int n) {addr=a; size=n; capacity=n;}
    int adjust(int number);
    int insert_and_pop(int number, int flag);
    void percolate_down(int index);
};

void loser_heap::percolate_down(int index)
{
    int j = 2*index + 1;
    int tmp = addr[index];
    while (j < size) {
        if (j < size-1 && addr[j] > addr[j+1])
            j++;
        if (addr[j] < tmp) {
            addr[index] = addr[j];
            index = j;
            j = 2*index + 1;
        } else {
            break;
        }
    }
    addr[index] = tmp;
}

int loser_heap::adjust(int number)
{
    if (!size) {
        build_heap(addr, capacity);
        return 0;
    }
    if (number < addr[0]) {
        return -1;
    }
    return 1;
}

int loser_heap::insert_and_pop(int number, int flag)
{
    int ret = addr[0];
    if (flag == -1) {
        addr[0] = addr[--size];
        percolate_down(0);
        memcpy(&addr[size], &addr[size+1], capacity-size);
        addr[capacity-1] = number;
    } else {
        addr[0] = number;
        percolate_down(0);
    }
    return ret;
}


int main(int argc, const char *argv[])
{
    int m,n;
    cin >> m >> n;
    int *initial_seq = new int[m];
    int i = 0;
    for (; i < m; ++i)
        cin >> initial_seq[i];
    int *heap_addr = new int[n];
    for (i = 0; i < n; ++i)
        cin >> heap_addr[i];
    int *output = new int[m+n];
    loser_heap hp;
    hp.build_heap(heap_addr, n);
    
    int tmp, flag;
    for (i = 0; i < m; ++i) {
        flag = hp.adjust(initial_seq[i]);
        if (!flag)
            break;
        tmp = hp.insert_and_pop(initial_seq[i], flag);
        output[i] = tmp;
    }
    for (int j = 0; j < i; ++j)
        cout << output[j] << " ";
    cout << endl;
    
    delete []output;
    delete []initial_seq;
    delete []heap_addr;
    
    return 0;
}
