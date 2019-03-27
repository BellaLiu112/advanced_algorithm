#include <iostream>
#include <cstring>
using namespace std;

/*
 描述
 现在有N（1<=N<=50000）头牛在选举它们的总统，选举包括两轮：第一轮投票选举出票数最多的K（1<=K<=N）头牛进入第二轮；第二轮对K头牛重新投票，票数最多的牛当选为总统。
 
 现在给出每头牛i在第一轮期望获得的票数Ai（1<=Ai<=1,000,000,000），以及在第二轮中（假设它进入第二轮）期望获得的票数Bi（1<=Bi<=1,000,000,000），请你预测一下哪头牛将当选总统。幸运的是，每轮投票都不会出现票数相同的情况。
 
 输入
 第1行：N和K
 
 第2至N+1行：第i+1行包括两个数字：Ai和Bi
 */


struct info{
    int round_1;
    int round_2;
    int index;
};

int Partition(info *Array, int l, int r) {
    info temp = Array[l];
    while (l < r) {
        while (Array[r].round_1 <= temp.round_1 && l < r)
            r--;
        memcpy(&Array[l], &Array[r], sizeof(info));
        while (Array[l].round_1 >= temp.round_1 && l < r)
            l++;
        memcpy(&Array[r], &Array[l], sizeof(info));
    }
    memcpy(&Array[l], &temp, sizeof(info));
    return l;
}

int main(int argc, const char *argv[])
{
    int N, K, i;
    cin >> N >> K;
    info *votes = new info[N];
    for (i = 0; i < N; ++i){
        cin >> votes[i].round_1 >> votes[i].round_2;
        votes[i].index = i+1;
    }
    // 选出票数最多的K头牛
    int l=0, r=N-1;
    int pivot = Partition(votes, l, r);
    while (pivot != K-1) {
        if (pivot < K-1) {
            pivot = Partition(votes, pivot+1, r);
        } else {
            pivot = Partition(votes, l, pivot-1);
        }
    }
    // 从前K个中选出最大的
    int MaxIndex = 0, MaxVote = 0;
    for (i = 1; i < K; ++i)
        if (votes[i].round_2 > votes[MaxIndex].round_2)
            MaxIndex = i;
        
    cout << votes[MaxIndex].index << endl;
    delete[] votes;
    return 0;
}
