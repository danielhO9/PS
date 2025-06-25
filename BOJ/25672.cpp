#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<int> v(k);
    for (int i = 0; i < k; ++i) cin >> v[i];
    if (k == 0 || v[0] != 1) {
        cout << n << ' ' << k + 1 << '\n';
        cout << 1 << ' ';
        for (auto i: v) cout << i << ' ';
        cout << '\n';
    } else {
        cout << n << ' ' << k - 1 << '\n';
        for (int i = 1; i < k; ++i) cout << v[i] << ' ';
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}