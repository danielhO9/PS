#include <bits/stdc++.h>
using namespace std;

int n;
double mx, my, mz;

const double MAX = 500000;

double val[13];
double dis[13][13];
double sdis[13];
double dp[1 << 13][13];

vector<int> ord[14];

void tsp(int N) {
    for (int i = 0; i < (1 << N); ++i) for (int j = 0; j < N; ++j) dp[i][j] = MAX;
    for (int i = 0; i < N; ++i) dp[1 << i][i] = sdis[i];
    for (int l = 1; l < N; ++l) {
        for (auto mask: ord[l]) for (int i = 0; i < N; ++i) if (!(mask >> i & 1)) {
            for (int j = 0; j < N; ++j) {
                dp[mask ^ (1 << i)][i] = min(dp[mask ^ (1 << i)][i], dp[mask][j] + dis[j][i]);
            }
        }
    }
    for (int i = 0; i < N; ++i) dp[(1 << N) - 1][i] += val[i];
}

double cache[13][13];
double ptx[13][13], pty[13][13], ptz[13][13];
double sx[13], sy[13], sz[13];
double ssids[13];
int k[13];

double f(double x, double y, double z, double xx, double yy, double zz) {
    x -= xx;
    y -= yy;
    z -= zz;
    return sqrt(x * x + y * y + z * z);
}

void solve() {
    for (int i = 0; i < 13; ++i) val[i] = 0.0;
    for (int i = 0; i < n; ++i) {
        cin >> k[i] >> sx[i] >> sy[i] >> sz[i];

        ssids[i] = f(sx[i], sy[i], sz[i], mx, my, mz);
        for (int j = 0; j < k[i]; ++j) cin >> ptx[i][j] >> pty[i][j] >> ptz[i][j];
        for (int j = 0; j < k[i]; ++j) sdis[j] = f(sx[i], sy[i], sz[i], ptx[i][j], pty[i][j], ptz[i][j]);
        for (int j = 0; j < k[i]; ++j) for (int l = 0; l < k[i]; ++l) {
            dis[j][l] = f(ptx[i][l], pty[i][l], ptz[i][l], ptx[i][j], pty[i][j], ptz[i][j]);
        }
        tsp(k[i]);
        for (int j = 0; j < k[i]; ++j) cache[i][j] = dp[(1 << k[i]) - 1][j];
    }

    for (int i = 0; i < n; ++i) sdis[i] = ssids[i];

    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) if (i != j) {
        dis[i][j] = MAX;
        for (int l = 0; l < k[i]; ++l) {
            dis[i][j] = min(dis[i][j], cache[i][l] + f(sx[j], sy[j], sz[j], ptx[i][l], pty[i][l], ptz[i][l]));
        }
    }
    for (int i = 0; i < n; ++i) {
        val[i] = MAX;
        for (int j = 0; j < k[i]; ++j) val[i] = min(val[i], cache[i][j]);
    }
    tsp(n);
    double ans = MAX;
    for (int i = 0; i < n; ++i) ans = min(ans, dp[(1 << n) - 1][i]);
    // ans += 0.005;
    cout << fixed;
    cout.precision(2);
    cout << ans << '\n';
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    for (int i = 0; i < (1 << 13); ++i) ord[__builtin_popcount(i)].push_back(i);
    while (true) {
        cin >> n >> mx >> my >> mz;
        if (n == 0) break;
        solve();
    }
}