#include <bits/stdc++.h>
using namespace std;

int n;
int a[1000];

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = n - 1; i > 0; --i) a[i] = a[i] - a[i - 1];
    int num = 0;
    for (int i = 0; i < n; ++i) if (i % 2 != n % 2) num ^= a[i];
    if (num) cout << "TAK\n";
    else cout << "NIE\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}