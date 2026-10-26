#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

ll N, C;
ll A[300000];
ll S, inv, big, small;
ll ans[300000];

ll pow(ll a, ll b) {
    if (b == 0) return 1ll;
    ll h = pow(a, b / 2);
    h = (h * h) % MOD;
    if (b % 2) return (h * a) % MOD;
    else return h;
}

void solve() {
    cin >> N >> C; --C;
    for (int i = 0; i < N; ++i) cin >> A[i];
    ++A[C];
    S = 0; for (int i = 0; i < N; ++i) S += A[i];
    --S; inv = pow(S, MOD - 2);
    vector<pair<ll, int>> v;
    for (int i = 0; i < N; ++i) v.push_back(make_pair(A[i], i));
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    big = 0;
    small = S + 1;
    for (auto [a, i]: v) {
        small -= a;
        ans[i] = a - 1 + small + big;

        ans[i] %= MOD;
        ans[i] *= pow(S - small, MOD - 2); ans[i] %= MOD;
        big += ((ans[i] + 1) * a) % MOD;
        big %= MOD;
    }
    // cout << ans[0] << ' ';
    cout << ans[C];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}