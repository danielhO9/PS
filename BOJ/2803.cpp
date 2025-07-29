#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

ll N, M;

vector<ll> sosDP(const vector<ll>& a) {
    int sz = a.size();
    int n = (int)ceil(log2(sz));
    vector<ll> ret(1 << n);
    for (int i = 0; i < (1 << n); ++i) ret[i] = a[i];
    for (int i = 0; i < n; ++i) {
        for (int x = 0; x < (1 << n); ++x) {
            if (x & (1 << i)) ret[x] += ret[x ^ (1 << i)];
        }
    }
    return ret;
}

ll pow(ll a, ll b) {
    if (b == 0) return 1;
    ll h = pow(a, b / 2);
    h = (h * h) % MOD;
    if (b % 2) return (a * h) % MOD;
    else return h;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    vector<ll> a(1 << M);
    for (int i = 0; i < N; ++i) {
        int K; cin >> K;
        int val = 0;
        for (int j = 0; j < K; ++j) {
            int tmp; cin >> tmp; --tmp;
            val |= (1 << tmp);
        }
        ++a[val];
    }
    auto sm = sosDP(a);
    for (int i = 0; i < (1 << M); ++i) if (i < (((1 << M) - 1)^i)) swap(sm[i], sm[((1 << M) - 1)^i]);
    for (int i = 0; i < (1 << M); ++i) sm[i] = pow(2ll, sm[i]);
    ll ans = 0;
    for (int i = 0; i < (1 << M); ++i) {
        if (__builtin_popcount(i) & 1) ans -= sm[i];
        else ans += sm[i];
        ans += MOD;
        ans %= MOD;
    }
    cout << ans;
}