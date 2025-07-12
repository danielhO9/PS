#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

ll pow(ll a, ll b) {
    if (b == 0) return 1;
    ll h = pow(a, b / 2);
    h = (h * h) % MOD;
    if (b % 2) return (h * a) % MOD;
    else return h;
}

ll N;

void solve() {
    cin >> N;
    ll ans = 0;
    ll th = sqrt(N);
    for (ll b = 2; N / b >= th; ++b) {
        ans += (((N / b - 1)% MOD) * (b - 1) + (N % b)) % MOD;
        ans %= MOD;
        // cout << b << "\n";
    }
    ll inv = pow(2ll, MOD - 2);
    for (ll k = 1; k < th; ++k) {
        ll l = N / (k + 1) + 1;
        ll r = N / k;
        if (r == N) --r;
        if (l > r) continue;
        // cout << k << ' ' << l << ' ' << r << '\n';
        ll cnt = r - l + 1; cnt %= MOD;
        ll sm = ((l + r) % MOD) * cnt; sm %= MOD;
        sm *= inv; sm %= MOD;
        ll tmp = (N % MOD) * cnt; tmp %= MOD;
        tmp += MOD - sm; tmp %= MOD;
        tmp += MOD - ((k * cnt) % MOD); tmp %= MOD;
        tmp += cnt; tmp %= MOD;
        ans += tmp; ans %= MOD;

    }
    // for (ll b = 2; b < N; ++b) {
    //     ans += (N / b - 1) * (b - 1) + (N % b);
    // }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}