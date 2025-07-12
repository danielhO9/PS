#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N; ll L;
ll arr[100000];
ll cache[100000][2];

ll matchCache(int n, int t) {
    ll& ret = cache[n][t];
    if (ret != -1) return ret;
    if (n == 0) {
        if (t == 0) ret = arr[n] * 2;
        else ret = L;
        return ret;
    }
    ret = min(matchCache(n-1, 0) + arr[n], matchCache(n - 1, 1) + L - arr[n]);
    if (t == 0) ret += arr[n];
    else ret += L - arr[n];
    return ret;
}

void solve() {
    cin >> N >> L;
    for (int i = 0; i < N; ++i) cin >> arr[i];
    for (int i = 0; i < N; ++i) for (int j = 0; j < 2; ++j) cache[i][j] = -1;
    cout << min(matchCache(N - 1, 0), matchCache(N - 1, 1)) << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << '\n';
        solve();
    }
}