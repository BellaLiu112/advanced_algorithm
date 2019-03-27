#include <utility>
#include <iostream>
using namespace std;

struct Node{
    int key;
    int next;
};

struct StaticQueue{
    int head;
    int tail;
};

template <class Record>
void PrettyPrint(Record *Array, int n)
{
    cout << " " << endl;
    for (int i = 0; i < n; ++i)
        cout << Array[i].key << " " << Array[i].next << endl;
}

template <class Record>
void Distribute(Record *Array, int first, int i, int r, StaticQueue *queue)
{
    int j, k, a, curr = first;
    for (j = 0; j < r; j++)
        queue[j].head = -1;
    while (curr != -1){
        k = Array[curr].key;
        for (a = 0; a < i; ++a)
            k /= r;
        k %= r;
        if (queue[k].head == -1){
            queue[k].head = curr;
        } else {
            Array[queue[k].tail].next = curr;
        }
        queue[k].tail = curr;
        curr = Array[curr].next;
    }
}

template <class Record>
void Collect(Record *Array, int& first, int r, StaticQueue *queue)
{
    int last, k = 0;
    while (queue[k].head == -1)
        k++;
    first = queue[k].head;
    last = queue[k].tail;
    while (k < r-1) {
        k++;
        while (k < r-1 && queue[k].head == -1)
            k++;
        if (queue[k].head != -1) {
            Array[last].next = queue[k].head;
            last = queue[k].tail;
        }
    }
    Array[last].next = -1;
}

template <class Record>
void AddrSort(Record *Array, int n, int first)
{
    int i, j;
    j = first;
    Record TempRec;
    for (i = 0; i < n-1; ++i) {
        TempRec = Array[j];
        swap(Array[i], Array[j]);
        Array[i].next = j;
        j = TempRec.next;
        while (j <= i)
            j = Array[j].next;
    }
}

template <class Record>
void RadixSort(Record *Array, int n, int d, int r)
{
    int i, first = 0;
    StaticQueue *queue = new StaticQueue[r];
    for (i = 0; i < n-1; ++i)
        Array[i].next = i + 1;
    Array[n-1].next = -1;
    for (i = 0; i < d; ++i){
        Distribute(Array, first, i, r, queue);
        Collect(Array, first, r, queue);
    }
    for (i = 0; i < n; ++i)
        cout << Array[i].key << " " << Array[i].next << endl;
    delete[] queue;
    AddrSort(Array, n, first);
}

int main(int argc, const char *argv[])
{
    int a[8] = {49, 38, 65, 97, 76, 13, 27, 52};
    Node Array[8];
    for (int i = 0; i < 8; ++i)
        Array[i].key = a[i];
    RadixSort<Node>(Array, 8, 2, 10);
    return 0;
}

