#include <bits/stdc++.h>
using namespace std;
vector<int> graph[100001];
int n, cache[100001][19], t = 1, ans;

int matchCache(int d, int dc, int p) {
    int& ret = cache[d][dc];
    if (ret != -1) return ret;
    ret = dc;
    for (auto i: graph[d]) if (i != p) {
        int temp = 987654321;
        for (int j = 1; j <= t; ++j) if (j != dc) temp = min(temp, matchCache(i, j, d));
        ret += temp;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n; int x, y;
    for (int i = 0; i < n - 1; ++i) {
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    memset(cache, -1, sizeof(cache));
    int pos = 1;
    while (pos < n) { pos *= 2; ++t; }
    ans = 987654321;
    for (int i = 1; i <= t; ++i) ans = min(ans, matchCache(1, i, 0));
    cout << ans;
    return 0;
}