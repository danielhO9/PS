#include <bits/stdc++.h>
typedef long long ll;
const ll MOD = 1e9 + 7;

std::vector<int> adj[100001];
ll fac[100001];
ll ifac[100001];
ll N, K;
ll ans = 0;
std::vector<ll> h;

ll pow(ll a, ll b) {
    if (b == 0) return 1ll;
    ll h = pow(a, b / 2);
    h = (h * h) % MOD;
    if (b % 2) return (a * h) % MOD;
    else return h;
}

ll comb(ll a, ll b) {
    assert(a >= b);
    ll ret = fac[a];
    ret *= ifac[b]; ret %= MOD;
    ret *= ifac[a - b]; ret %= MOD;
    return ret;
}

ll dfs(int v, int p, int dep) {
    ll sz = 1;
    if (v != 1) h.push_back(dep);
    for (auto u: adj[v]) if (u != p) sz += dfs(u, v, dep + 1);
    if (v != 1) {
        ll rem = N - 1 - sz;
        ll tot = comb(N - 1, K);
        ll par = rem >= K ? comb(rem, K) : 0ll;
        ans += (2ll * ((tot - par + MOD) % MOD)) % MOD;
        ans %= MOD;
    }
    return sz;
}

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    std::cin >> N >> K;
    for (int i = 0; i < N - 1; ++i) {
        ll U, V; std::cin >> U >> V;
        adj[U].push_back(V);
        adj[V].push_back(U);
    }
    fac[0] = 1ll, ifac[0] = 1ll;
    for (ll i = 1; i <= 1e5; ++i) {
        fac[i] = (fac[i - 1] * i) % MOD;
        ifac[i] = pow(fac[i], MOD - 2);
    }
    dfs(1, 0, 0);
    sort(h.begin(), h.end());
    for (ll i = K - 1; i < N - 1; ++i) {
        ll tmp = (h[i] * comb(i, K - 1)) % MOD;
        ans = (ans - tmp + MOD) % MOD;
    }
    std::cout << ans;

}