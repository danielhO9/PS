#include <bits/stdc++.h>
using namespace std;

int n, k;
int x[601][601];
int smx[601][601];
int f[601][601];

int cache[601][51];
vector<int> ans;

int matchCache(int c, int u) {
    int& ret = cache[c][u];
    if (ret != -987654322) return ret;
    if (u == 0) return ret = 0;
    if (n - c < u) return ret = -987654321;
    for (int i = c + 1; i < n; ++i) ret = max(ret, matchCache(i, u - 1) + f[c][i]);
    return ret;
}

void reconstruct(int c, int u) {
    if (u == 0) return;
    for (int i = c + 1; i < n; ++i) if (matchCache(c, u) == matchCache(i, u - 1) + f[c][i]) {
        ans.push_back(i);
        reconstruct(i, u - 1);
        return;
    }
}

void solve() {
    cin >> n >> k;
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= k; ++j) cache[i][j] = -987654322;
    for (int i = 1; i < n; ++i) for (int j = i + 1; j <= n; ++j) cin >> x[i][j];
    // smx[i][j]: i -> [j, n]
    for (int i = 1; i < n; ++i) {
        smx[i][n] = x[i][n];
        for (int j = n - 1; j > i; --j) smx[i][j] = smx[i][j + 1] + x[i][j];
    }
    // prv: i, cur: j
    for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
        for (int l = i + 1; l <= j; ++l) f[i][j] += smx[l][j + 1];
    }
    reconstruct(0, k);
    for (auto i: ans) cout << i << ' ';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}