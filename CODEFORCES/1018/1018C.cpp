#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll h[1000][1000];
ll a[1000], b[1000];
ll cache[1000][2];

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) cin >> h[i][j];
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            cache[0][0] = 0;
            cache[0][1] = a[0];
            continue;
        }
        bool flag[3];
        flag[0] = flag[1] = flag[2] = true;
        for (int j = 0; j < n; ++j) {
            if (h[i - 1][j] == h[i][j] - 1) flag[0] = false;
            if (h[i - 1][j] == h[i][j]) flag[1] = false;
            if (h[i - 1][j] == h[i][j] + 1) flag[2] = false;
        }
        cache[i][0] = cache[i][1] = 1e14;
        if (flag[0]) cache[i][0] = min(cache[i - 1][1], cache[i][0]);
        if (flag[1]) {
            cache[i][0] = min(cache[i - 1][0], cache[i][0]);
            cache[i][1] = min(cache[i - 1][1] + a[i], cache[i][1]);
        }
        if (flag[2]) cache[i][1] = min(cache[i - 1][0] + a[i], cache[i][1]);
        
    }
    ll ans = min(cache[n - 1][0], cache[n - 1][1]);
    // cout << ans << '\n';
    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            cache[0][0] = 0;
            cache[0][1] = b[0];
            continue;
        }
        bool flag[3];
        flag[0] = flag[1] = flag[2] = true;
        for (int j = 0; j < n; ++j) {
            if (h[j][i - 1] == h[j][i] - 1) flag[0] = false;
            if (h[j][i - 1] == h[j][i]) flag[1] = false;
            if (h[j][i - 1] == h[j][i] + 1) flag[2] = false;
        }
        cache[i][0] = cache[i][1] = 1e14;
        if (flag[0]) cache[i][0] = min(cache[i - 1][1], cache[i][0]);
        if (flag[1]) {
            cache[i][0] = min(cache[i - 1][0], cache[i][0]);
            cache[i][1] = min(cache[i - 1][1] + b[i], cache[i][1]);
        }
        if (flag[2]) cache[i][1] = min(cache[i - 1][0] + b[i], cache[i][1]);
    }
    ans += min(cache[n - 1][0], cache[n - 1][1]);
    if (ans > 1e13) cout << -1 << '\n';
    else cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}