#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, R, G, B;

ll cache[11][101][101][101];
ll comb[11][11];

void init() {
    for (ll i = 1; i <= 10; ++i) {
        for (ll j = 0; j <= i; ++j) {
            ll val = 1;
            for (ll k = 0; k < j; ++k) val *= (i - k);
            for (ll k = 1; k <= j; ++k) val /= k;
            comb[i][j] = val;
        }
    }
}

ll matchCache(ll n, ll r, ll g, ll b) {
    ll& ret = cache[n][r][g][b];
    if (ret != -1) return ret;
    if (n == 1) {
        ret = 0;
        if (r > 0) ++ret;
        if (g > 0) ++ret;
        if (b > 0) ++ret;
        return ret;
    }
    ret = 0;
    if (r >= n) ret += matchCache(n - 1, r - n, g, b);
    if (g >= n) ret += matchCache(n - 1, r, g - n, b);
    if (b >= n) ret += matchCache(n - 1, r, g, b - n);
    if (n % 2 == 0) {
        int m = n / 2;
        if (r >= m && g >= m) ret += matchCache(n - 1, r - m, g - m, b) * comb[n][m];
        if (g >= m && b >= m) ret += matchCache(n - 1, r, g - m, b - m) * comb[n][m];
        if (b >= m && r >= m) ret += matchCache(n - 1, r - m, g, b - m) * comb[n][m];
    }
    if (n % 3 == 0) {
        int m = n / 3;
        if (r >= m && g >= m && b >= m) ret += matchCache(n - 1, r - m, g - m, b - m) * comb[n][m] * comb[n - m][m];
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();
    cin >> N >> R >> G >> B;
    ll n = 0;
    for (int i = 1; i <= N; ++i) n += i;
    memset(cache, -1, sizeof(cache));
    cout << matchCache(N, R, G, B);
}