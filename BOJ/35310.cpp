#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 998244353;
ll N, M;
string s;
ll dp[3000 * 25 + 1];
ll psm[3000 * 25 + 1];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    cin >> s;
    M = min(M, N * 25);

    dp[0] = 1;
    for (int i = 0; i < N; ++i) {
        int n = (i + 1) * 25;
        psm[0] = dp[0];
        for (int j = 1; j <= n; ++j) psm[j] = (psm[j - 1] + dp[j]) % MOD;
        for (int j = 1; j <= n; ++j) {
            dp[j] = psm[j];
            if (j - 26 >= 0) {
                dp[j] -= psm[j - 26];
                dp[j] += MOD;
                dp[j] %= MOD;
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i <= M; ++i) ans = (ans + dp[i]) % MOD;
    cout << ans;
}