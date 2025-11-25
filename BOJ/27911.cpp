#include <bits/stdc++.h>
using namespace std;

int n, q;
int a[5000], d[200000], s[200000];
int cache[5001][5001], lst[5000][5001], rst[5000][5001];
bool pos[5000][5000];

void init() {
    memset(lst, -1, sizeof(lst));
    memset(rst, -1, sizeof(rst));
    for (int i = 0; i < min(n, q); ++i) {
        for (int j = n - 1; j >= 0; --j) {
            if (pos[i][j]) rst[i][j] = j;
            else rst[i][j] = rst[i][j + 1];
        }

        if (pos[i][0]) lst[i][0] = 0;
        for (int j = 1; j < n; ++j) {
            if (pos[i][j]) lst[i][j] = j;
            else lst[i][j] = lst[i][j - 1];
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < q; ++i) cin >> d[i] >> s[i];


    for (int i = 0; i < min(n, q); ++i) {
        int cnt = 0;
        for (int j = 0; j < d[i]; ++j) if (a[j] < s[i]) ++cnt;
        for (int j = 0; j < n; ++j) {
            if (!cnt) pos[i][j] = true;

            if (j + d[i] == n) break;
            if (a[j + d[i]] < s[i]) ++cnt;
            if (a[j] < s[i]) --cnt;
        }
    }

    init();

    for (int len = n; len >= 1; --len) {
        for (int l = 0; l < n; ++l) {
            int r = l + len;
            if (r > n) break;
            int qq = cache[l][r];

            if (qq == min(n, q)) {
                cout << qq;
                return 0;
            }

            int idx = rst[qq][l];
            if (idx != -1 && idx + d[qq] <= r) {
                cache[idx + d[qq]][r] = max(cache[idx + d[qq]][r], qq + 1);
            }
            if (r - d[qq] >= 0) {
                idx = lst[qq][r - d[qq]];
                if (idx != -1 && l <= idx) {
                    cache[l][idx] = max(cache[l][idx], qq + 1);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; ++i) for (int j = i; j <= n; ++j) {
        ans = max(ans, cache[i][j]);
    }
    cout << ans;
}