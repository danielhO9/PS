#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
int a[100];

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) if (a[i] == a[j]) {
        cout << "YES\n";
        return;
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}