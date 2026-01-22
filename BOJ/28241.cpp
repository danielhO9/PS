#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m;
ll mn[100000];
ll mx[100000];
ll dp[100000][4];
ll d[10000];

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int k; cin >> k;
        d[i] = 0;
        ll prv = 0, a;
        mn[i] = m + 1;
        mx[i] = 0;
        for (int j = 0; j < k; ++j) {
            cin >> a;
            d[i] = max(d[i], a - prv);
            prv = a;
            mn[i] = min(mn[i], a);
            mx[i] = max(mx[i], a);
        }
        d[i] = max(d[i], m + 1 - prv);
    }
    for (int i = n - 1; i >= 0; --i) {
        if (i == n - 1) {
            for (int j = 0; j < 4; ++j) {
                int a = j & 1;
                int b = (j - a) >> 1;
                if (a == b) dp[i][j] = (m + 1) * 2;
                else dp[i][j] = m + 1;
            }
            continue;
        }

        for (int j = 0; j < 4; ++j) dp[i][j] = LLONG_MAX;

        for (int j = 0; j < 4; ++j) for (int k = 0; k < 4; ++k) {
            int a = j & 1, na = k & 1;
            int b = (j - a) >> 1, nb = (k - na) >> 1;
            ll tmp = dp[i + 1][j];
            if (a != na) tmp += m + 1;
            if (b != nb) tmp += m + 1;
            if (a == na && b == nb) {
                if (a != b) {
                    tmp += (m + 1 - d[i]) * 2;
                } else {
                    if (a == 0) tmp += mx[i] * 2;
                    else tmp += (m + 1 - mn[i]) * 2;
                }
            }
            dp[i][k] = min(dp[i][k], tmp);
        }
    }
    cout << min(dp[0][0], dp[0][1]) + (n - 1) * 2;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}