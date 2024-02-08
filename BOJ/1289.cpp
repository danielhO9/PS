#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int N;
vector<pair<int, LL>> graph[100001];
LL cache[100001], mod = 1000000007, ans = 0;

LL matchCache(int d, int p) {
    LL& ret = cache[d];
    if (ret != -1) return ret;
    ret = 0;
    LL temp = 0;
    for (auto i: graph[d]) if (i.first != p) {
        LL part = i.second + matchCache(i.first, d) * i.second; part %= mod;
        ret += part; ret %= mod;
        ans += temp * part; ans %= mod;
        temp += part; temp %= mod;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int A, B, W;
    cin >> N;
    for (int i = 0; i < N - 1; ++i) {
        cin >> A >> B >> W;
        graph[A].push_back({B, W});
        graph[B].push_back({A, W});
    }
    memset(cache, -1, sizeof(cache));
    matchCache(1, 0);
    for (int i = 1; i <= N; ++i) { ans += cache[i]; ans %= mod; }
    cout << ans;
    return 0;
}