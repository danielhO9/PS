#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m;
ll p[1000][1000];
ll q[1000][1000];
ll prefix_sum_p[1000][1000];
ll prefix_sum_q[1000][1000];
const ll MOD = 998244353;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> p[i][j];
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> q[i][j];
    
    for (int i = 0; i < n; ++i) {
        prefix_sum_p[i][m - 1] = p[i][m - 1];
        for (int j = m - 2; j >= 0; --j) prefix_sum_p[i][j] = (prefix_sum_p[i][j + 1] + p[i][j]) % MOD;
    }
    for (int j = 0; j < m; ++j) {
        prefix_sum_q[n - 1][j] = q[n - 1][j];
        for (int i = n - 2; i >= 0; --i) prefix_sum_q[i][j] = (prefix_sum_q[i + 1][j] + q[i][j]) % MOD;
    }

    ll answer = 2;
    for (int i = 1; i < n - 1; ++i) {
        for (int j = 1; j < m - 1; ++j) {
            ll prob = 1;
            prob *= prefix_sum_p[i + 1][j]; prob %= MOD;
            prob *= prefix_sum_q[i][j + 1]; prob %= MOD;
            prob *= (1 - prefix_sum_p[i][j] + MOD) % MOD; prob %= MOD;
            prob *= (1 - prefix_sum_q[i][j] + MOD) % MOD; prob %= MOD;
            answer += prob; answer %= MOD;
        }
    }
    cout << answer;
}