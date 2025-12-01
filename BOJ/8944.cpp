#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll MOD = 9999991;

int N;
int l[21], r[21];
ll dp[21], sz[21];
ll fac[21], ifac[21];

ll pow(ll a, ll b) {
    if (b == 0) return 1;
    ll h = pow(a, b >> 1);
    h = (h * h) % MOD;
    if (b & 1) return (h * a) % MOD;
    else return h;
}

ll comb(ll n, ll r) {
    ll ret = fac[n];
    ret *= ifac[r]; ret %= MOD;
    ret *= ifac[n - r]; ret %= MOD;
    return ret;
}

void dfs(int v) {
    if (l[v] == -1 && r[v] == -1) {
        dp[v] = 1;
        sz[v] = 1;
        return;
    }
    dp[v] = 1;
    sz[v] = 1;
    if (r[v] != -1) {
        dfs(r[v]);
        dp[v] *= dp[r[v]];
        dp[v] %= MOD;
        sz[v] += sz[r[v]];
    }
    if (l[v] != -1) {
        dfs(l[v]);
        dp[v] *= dp[l[v]];
        dp[v] %= MOD;
        sz[v] += sz[l[v]];
    }

    dp[v] *= comb(sz[l[v]] + sz[r[v]], sz[l[v]]);
    dp[v] %= MOD;
}

void solve() {
    cin >> N;
    int rt = -1;
    memset(l, -1, sizeof(l));
    memset(r, -1, sizeof(r));

    for (int i = 0; i < N; ++i) {
        int v; cin >> v;
        if (rt == -1) {
            rt = v;
            continue;
        }
        int cur = rt;
        while (true) {
            if (cur < v) {
                if (r[cur] == -1) {
                    r[cur] = v;
                    break;
                } else cur = r[cur];
            } else {
                if (l[cur] == -1) {
                    l[cur] = v;
                    break;
                } else cur = l[cur];
            }
        }
    }
    dfs(rt);
    cout << dp[rt] << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    fac[0] = 1;
    for (ll i = 1; i <= 20; ++i) {
        fac[i] = fac[i - 1] * i;
        fac[i] %= MOD;
    }

    for (ll i = 0; i <= 20; ++i) ifac[i] = pow(fac[i], MOD - 2);
    
    int t; cin >> t;
    while (t--) solve();
}