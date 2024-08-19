#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> sfx(n);
    for (int i = 0; i < n; ++i) cin >> sfx[i];
    vector<int> inv(n + 1);
    for (int i = 0; i < n; ++i) inv[sfx[i]] = i;
    inv[n] = -1;
    int ans = 0;
    for (int i = 0; i + 1 < n; ++i) {
        if (inv[sfx[i] + 1] < inv[sfx[i + 1] + 1]) continue;
        ++ans;
    }
    cout << ans + 1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}