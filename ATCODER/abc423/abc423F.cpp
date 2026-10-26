#include <bits/stdc++.h>
using namespace std;
typedef long long ull;
typedef __int128_t ll;

ull N, M, Y;
ull A[20];
ll F[1 << 20];
ll x[21];
const ll MAX = 1e18;
ll comb[21][21];

ll gcd(ll a, ll b) {
    if (b > a) swap(a, b);
    if (b == 0) return a;
    return gcd(b, a % b);
}

void init() {
    for (ll i = 1; i <= 20; ++i) {
        comb[i][0] = 1ll;
        for (ll j = 1; j <= i; ++j) {
            comb[i][j] = comb[i][j - 1] * (i - j + 1);
            comb[i][j] /= j;
        }
    }
}

void solve() {
    cin >> N >> M >> Y;
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) F[1 << i] = A[i];
    ll ans = 0;

    for (ll i = 0; i <= N; ++i) {
        if (i < M) x[i] = 0;
        else if (i == M) x[i] = 1;
        else {
            for (ll j = 0; j < i; ++j) x[i] -= comb[i][j] * x[j];
        }
    }


    for (int c = 2; c <= N; ++c) {
        for (int i = 0; i < (1 << N) ; ++i) if (__builtin_popcount(i) == c) {
            int j = __builtin_ctz(i);
            int prv = i ^ (1 << j);
            if (F[prv] == MAX + 1) F[i] = MAX + 1;
            else {
                // lcm(F[prv], A[j])
                ll g = gcd(F[prv], A[j]);
                g = A[j] / g;
                if (MAX / g < F[prv]) F[i] = MAX + 1;
                else F[i] = g * F[prv];
            }
        }
    }

    for (int c = 1; c <= N; ++c) {
        if (c < M) continue;
        for (int i = 0; i < (1 << N); ++i) if (__builtin_popcount(i) == c) {
            ans += (Y / F[i]) * x[c];
        }
    }
    
    cout << (ull) ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();
    solve();
}