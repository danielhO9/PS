#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
ll comb[11][11];

ll N, K;
ll A[200001];
ll S[200001];

void solve() {
    for (ll i = 0; i <= 10; ++i) {
        comb[i][0] = 1;
        for (ll j = 1; j <= i; ++j) {
            comb[i][j] = comb[i][j - 1] * (i - j + 1);
            comb[i][j] /= j;
        }
    }
    cin >> N >> K;
    for (int i = 1; i <= N; ++i) cin >> A[i], S[i] = (S[i - 1] + A[i]) % MOD;
    vector<ll> prv(K + 1);
    prv[0] = 1;
    vector<ll> cur(K + 1);
    ll ans = 0;
    for (int r = 1; r <= N; ++r) {
        cur[K] = 1;
        if (K % 2) cur[K] = MOD - 1;
        for (int i = K - 1; i >= 0; --i) {
            cur[i] = (cur[i + 1] * S[r]) % MOD;
            cur[i] *= -1; cur[i] += MOD; cur[i] %= MOD;
        }
        for (int i = 0; i <= K; ++i) cur[i] *= comb[K][i], cur[i] %= MOD;
        for (int i = 0; i <= K; ++i) {
            ans += (prv[i] * cur[i]) % MOD;
            ans %= MOD;
        }
        // for (int i = 0; i <= K; ++i) cout << prv[i] << ' ';
        // cout << '\n';
        // for (int i = 0; i <= K; ++i) cout << cur[i] << ' ';
        // cout << '\n';
        // cout << '\n';
        ll val = 1;
        for (int i = 0; i <= K; ++i) {
            prv[i] += val; prv[i] %= MOD;
            val *= S[r]; val %= MOD;
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}