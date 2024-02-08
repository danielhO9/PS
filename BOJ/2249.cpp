#include <bits/stdc++.h>
using namespace std;
int n, k, coin[100], cache[10001];

int matchCache(int i) {
    int& ret = cache[i];
    if (ret != -1) return ret;
    ret = 10001;
    for (int j = 0; j < n; ++j) if (i - coin[j] >= 0) {
        ret = min(matchCache(i - coin[j]) + 1, ret);
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    memset(cache, -1, sizeof(cache));
    for (int i = 0; i < n; ++i) { cin >> coin[i]; if (coin[i] <= k) cache[coin[i]] = 1; };
    int ans = matchCache(k);
    if (ans == 10001) cout << -1;
    else cout << ans;
    return 0;
}