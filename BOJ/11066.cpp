#include <bits/stdc++.h>
typedef long long LL;
using namespace std;
int K, cost[500], cache[500][500], sumCost[501];

int matchCache(int start, int end) {
    if (start == end) return 0;
    int& ret = cache[start][end];
    if (ret != -1) return ret;
    ret = 987654321;
    for (int i = start; i < end; ++i) ret = min(ret, matchCache(start, i) + matchCache(i + 1, end) + sumCost[end + 1] - sumCost[start]);
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int T; cin >> T;
    for (int i = 0; i < T; ++i) {
        cin >> K;
        for (int j = 0; j < K; ++j) {
            cin >> cost[j];
            sumCost[j + 1] = sumCost[j] + cost[j];
        }
        memset(cache, -1, sizeof(cache));
        cout << matchCache(0, K - 1) << "\n";
    }
    return 0;
}