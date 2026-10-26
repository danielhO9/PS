#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll g[200000];

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> g[i];
    sort(g, g + n);
    reverse(g, g + n);
    ll ans = 0;
    for (int i = 0; i < n; i += 2) {
        ans += g[i];
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}