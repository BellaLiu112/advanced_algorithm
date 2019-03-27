//#include <stdio.h>
//#include <cstring>
//using namespace std;
//#define M 30000
//
//int ELFhash(char *key) {
//    unsigned long h = 0, g;
//    while (*key) {
//        h = (h << 4) + *key++;
//        g = h & 0xF0000000L;
//        if (g) h ^= g >> 24;
//        h &= ~g;
//    }
//    return h % M;
//}
//
//template <class S, class T>
//class node {
//public:
//    node(){};
//    S *key;
//    T *value;
//    node *next;
//};
//
//template <class S, class T>
//class my_hash_map {
//    node<T, S> **node_array;
//    int capacity;
//    int load;
//public:
//    my_hash_map(int m){
//        capacity = m;
//        load = 0;
//        node_array = new node<T, S>*[m];
//        for (int i = 0; i < m; ++i) {
//            node_array[i] = NULL;
//        }
//    }
//    void insert(char *key, char *value);
//    char *search(char *key);
//    ~my_hash_map();
//};
//
//template <class S, class T>
//my_hash_map<S, T>::~my_hash_map( )
//{
//    node<S, T> *tmp0, *tmp1;
//    for (int i = 0; i < capacity; ++i) {
//        if (node_array[i]) {
//            tmp0 = node_array[i];
//            tmp1 = tmp0;
//            while (tmp0->next) {
//                tmp0 = tmp0->next;
//                delete tmp1;
//                tmp1 = tmp0;
//            }
//            delete tmp1;
//        }
//    }
//    delete []node_array;
//}
//
//template <class S, class T>
//void my_hash_map<S, T>::insert(char *key, char *value)
//{
//    int h = ELFhash(key);
//    node<S, T> *addr = node_array[h];
//    if (!addr) {
//        node_array[h] = new node<S, T>;
//        node_array[h]->key = new char[strlen(key) + 1];
//        strcpy(node_array[h]->key, key);
//        node_array[h]->value = new char[strlen(value) + 1];
//        strcpy(node_array[h]->value, value);
//        node_array[h]->next = NULL;
//    } else {
//        while (addr->next)
//            addr = addr->next;
//        addr->next = new node<S, T>;
//        addr->next->key = new char[strlen(key) + 1];
//        strcpy(addr->next->key, key);
//        addr->next->value = new char[strlen(value) + 1];
//        strcpy(addr->next->value, value);
//        addr->next->next = NULL;
//    }
//    load++;
//}
//
//template <class S, class T>
//char *my_hash_map<S, T>::search(char *key)
//{
//    int h = ELFhash(key);
//    node<S, T> *addr = node_array[h];
//    if (!addr)
//        return NULL;
//    while (strcmp(key, addr->key))
//        addr = addr->next;
//    return addr->value;
//}
//
//int split_str(const char *s) {
//    int i = 0;
//    for ( ; ; ) {
//        if (s[i] == '\0' || s[i] == ' ') {
//            break;
//        }
//        i++;
//    }
//    
//    return i;
//}
//
//int main(int argc, const char *argv[])
//{
//    my_hash_map<char, char> word_dict(M);
//    
//    char key[11], value[11];
//    char buffer[32];
//    char *p;
//    while (1) {
//        //int rt = scanf("%s", value);
//        //if (rt <= 0) {
//        //    break;
//        //}
//        p = gets(buffer);
//        
//        if (!p || !*p) {
//            int err = ferror(stdin);
//            bool eof = feof(stdin);
//            break;
//        }
//        
//        int index = split_str(buffer);
//        
//        //rt = scanf("%s", key);
//        buffer[index] = 0;
//        word_dict.insert(buffer + index + 1, buffer);
//    }
//    
//    while (1) {
//        //int rt = scanf("%s", key);
//        //if (rt <= 0) {
//        //    break;
//        //}
//        p = gets(buffer);
//        if (!p || !*p) {
//            int err = ferror(stdin);
//            bool eof = feof(stdin);
//            break;
//        }
//        char *str = word_dict.search(buffer);
//        if (!str) {
//            printf("eh\n");
//        } else printf("%s\n", str);
//    }
//    return 0;
//}
//
//
//
//
