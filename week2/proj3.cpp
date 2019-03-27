#include <iostream>
#include <cstring>
#include <map>
using namespace std;

int main(int argc, const char *argv[])
{
    map<int, int> array;
    int n, t;
    cin >> n >> t;
    int tmp;
    map<int, int>::iterator it, it1;
    while (n--) {
        cin >> tmp;
        it = array.find(tmp);
        if (it != array.end()){
            it->second++;
        } else {
            array.insert(make_pair(tmp, 1));
        }
    }
    int target;
    int cnt;
    if (t != 0) {
        cnt = 0;
        for (it = array.begin(); it != array.end(); ++it) {
            if (t > 0)
            {
                target = it->first + t;
            } else {
                target = it->first - t;
            }
        it1 = array.find(target);
        if (it1 != array.end()) {cnt++;}
        }  
    } else {
        cnt = 0;
        for (it = array.begin(); it != array.end(); ++it){
            if (it->second > 1)
                cnt++;
        }
    } 
    
    cout << cnt << endl;
    return 0;
}
