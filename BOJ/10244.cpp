#include <bits/stdc++.h>
using namespace std;

int n;
int a[100000];
bool vis[101];

void solve() {
    memset(vis, 0, sizeof(vis));
    set<int> s, ns;
    for (int i = 0; i < n; ++i) {
        ns.insert(a[i]);
        for (auto j: s) ns.insert(gcd(j, a[i]));
        swap(ns, s);
        ns.clear();
        for (auto j: s) vis[j] = true;
    }
    int cnt = 0;
    for (int i = 1; i <= 100; ++i) if (vis[i]) ++cnt;
    cout << cnt << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while (true) {
        cin >> n;
        if (n == 0) break;
        for (int i = 0; i < n; ++i) cin >> a[i];
        solve();
    }
}