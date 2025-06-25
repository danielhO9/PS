#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    if (k == n) {
        cout << "Impossible"; return 0;
    }
    if (n == 1) {
        cout << 1; return 0;
    }
    if (n % 2 && k == 0) {
        for (int i = 2; i <= n; ++i) cout << i << ' ';
        cout << 1;
        return 0;
    }
    vector<int> ans(n + 1);
    for (int i = 1; i <= n; ++i) ans[i] = i;
    int dif = (n - 1) - k;
    if (dif % 2) swap(ans[1], ans[2]);
    int idx = 3;
    for (int i = 0; i < dif / 2; ++i) {
        swap(ans[idx], ans[idx + 1]);
        idx += 2;
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
}