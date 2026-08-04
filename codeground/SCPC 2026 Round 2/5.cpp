#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll A, B;
int N;
pair<ll, ll> h[3000];
ll arr[301][301];
ll sm[301][301];
ll dp[301][301][301][2];
vector<int> tmp[301];

void solve() {
    cin >> A >> B;
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> h[i].first >> h[i].second;
    if (N > 300) {
        cout << 0 << '\n';
        return;
    }

    vector<ll> x, y;
    for (int i = 0; i < N; ++i) {
        x.push_back(h[i].first);
        y.push_back(h[i].second);
    }
    x.push_back(0); x.push_back(A);
    y.push_back(0); y.push_back(B);
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    for (int i = 0; i < N; ++i) {
        h[i].first = lower_bound(x.begin(), x.end(), h[i].first) - x.begin();
        h[i].second = lower_bound(y.begin(), y.end(), h[i].second) - y.begin();
    }
    for (int i = 0; i < N + 1; ++i) for (int j = 0; j < N + 1; ++j) {
        arr[i][j] = (x[i + 1] - x[i]) * (y[j + 1] - y[j]);
    }
    for (int i = 0; i < N + 1; ++i) {
        sm[i][0] = arr[i][0];
        for (int j = 1; j < N + 1; ++j) sm[i][j] = arr[i][j] + sm[i][j - 1];
    }
    for (int i = 0; i < N + 1; ++i) tmp[i].clear();
    for (int i = 0; i < N; ++i) tmp[h[i].second].push_back(h[i].first - 1);
    for (int i = 0; i < N + 1; ++i) for (int j = i; j < N + 1; ++j) {
        dp[0][i][j][0] = sm[0][j];
        if (i > 0) dp[0][i][j][0] -= sm[0][i - 1];
    }
    for (int t = 1; t < N + 1; ++t) {
        for (int i = 0; i < N + 1; ++i) for (int j = i; j < N + 1; ++j) {
            dp[t][i][j][0] = sm[t][j];
            if (i > 0) dp[t][i][j][0] -= sm[t][i - 1];
            ll mx = 0;
            for (int ii = i; ii <= j; ++ii) for (int jj = ii; jj <= j; ++jj) {
                bool flag = true;
                for (auto k: tmp[t]) if (ii <= k && k < jj) flag = false;
                if (flag) {
                    mx = max(mx, dp[t - 1][ii][jj][0]);
                }
            }
            dp[t][i][j][0] += mx;
        }
    }

    for (int i = 0; i < N + 1; ++i) tmp[i].clear();
    for (int i = 0; i < N; ++i) tmp[h[i].second - 1].push_back(h[i].first - 1);
    for (int i = 0; i < N + 1; ++i) for (int j = i; j < N + 1; ++j) {
        dp[N][i][j][1] = sm[N][j];
        if (i > 0) dp[N][i][j][1] -= sm[N][i - 1];
    }
    for (int t = N - 1; t >= 0; --t) {
        for (int i = 0; i < N + 1; ++i) for (int j = i; j < N + 1; ++j) {
            dp[t][i][j][1] = sm[t][j];
            if (i > 0) dp[t][i][j][1] -= sm[t][i - 1];
            ll mx = 0;
            for (int ii = i; ii <= j; ++ii) for (int jj = ii; jj <= j; ++jj) {
                bool flag = true;
                for (auto k: tmp[t]) if (ii <= k && k < jj) flag = false;
                if (flag) {
                    mx = max(mx, dp[t + 1][ii][jj][1]);
                }
            }
            dp[t][i][j][1] += mx;
        }
    }

    ll ans = 0;
    for (int i = 0; i <= N; ++i) for (int j = 0; j <= N; ++j) for (int k = j; k <= N; ++k) {
        ll val = sm[i][k];
        if (j > 0) val -= sm[i][j - 1];
        ans = max(ans, dp[i][j][k][0] + dp[i][j][k][1] - val);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    for (int i = 1; i <= t; ++i) {
        cout << "Case #" << i << '\n';
        solve();
        cout.flush();
    }
}