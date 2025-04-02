#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;

ll N, K;
ll p[1000001];

ll pow(ll a, ll b) {
    if (b == 0) return 1;
    ll h = pow(a, b / 2);
    h = (h * h) % MOD;
    if (b % 2) return (h * a) % MOD;
    else return h;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> K;
    p[0] = 1ll;
    for (ll i = 1; i <= N; ++i) p[i] = (p[i - 1] * K) % MOD;
    ll ans = 0;
    ll comb = 1;
    for (ll i = 0; i <= N / 2; ++i) {
        ll dif = (comb * p[N - i]) % MOD;
        dif *= (N - 2 * i + 1); dif %= MOD;
        dif *= pow(N - i + 1, MOD - 2); dif %= MOD;
        ans += dif;
        ans %= MOD;
        comb *= (N - i); comb %= MOD;
        comb *= pow(i + 1, MOD - 2); comb %= MOD;
    }
    cout << ans;
}