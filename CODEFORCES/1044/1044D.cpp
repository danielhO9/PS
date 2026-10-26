#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll h[200000];
ll cache[200000];

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> h[i];
    cache[0] = h[0];
    cache[1] = h[0] + h[1] - 1;
    for (ll i = 2; i < n; ++i) {
        cache[i] = min(cache[i - 2] + h[i - 1] + max(h[i] - (i), 0ll), cache[i - 1] + h[i] - 1);
    }
    // for (int i = 0; i < n; ++i) cout << cache[i] << ' ';
    // cout << '\n';
    cout << cache[n - 1] << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}