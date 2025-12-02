#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
ll a[100];
ll cnt[11];
ll ccnt[13];
ll dp[16];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for (ll i = 0; i < n; ++i) {
        char c; cin >> c;

        if (c == 'A') a[i] = 1;
        else if ('B' <= c && c <= 'Z') a[i] = 10;
        else a[i] = c - '0';

        if (c == 'A') ++ccnt[0];
        else if ('0' <= c && c <= '9') ++ccnt[c - '1'];
        else if (c == 'T') ++ccnt[9];
        else if (c == 'J') ++ccnt[10];
        else if (c == 'Q') ++ccnt[11];
        else if (c == 'K') ++ccnt[12];
    }
    ll ans = 0;
    dp[0] = 1;
    for (ll i = 0; i < n; ++i) {
        for (ll j = 15; j >= 0; --j) {
            if (j + a[i] <= 15) dp[j + a[i]] += dp[j];
        }
    }
    ans += dp[15] * 2;
    // for (ll i = 0; i < n; ++i) ++cnt[a[i]];
    for (ll i = 0; i < 14; ++i) ans += ccnt[i] * (ccnt[i] - 1);
    for (ll len = 13; len >= 3; --len) {
        for (ll i = 0; i < 13; ++i) {
            if (i + len == 14) break;
            ll tmp = 1;
            for (ll j = 0; j < len; ++j) tmp *= ccnt[i + j];
            tmp *= len;
            if (tmp != 0) for (ll j = 0; j < len; ++j) ccnt[i + j] = 0;
            ans += tmp;
            // if (tmp != 0) cout << tmp << '\n';
        }
    }
    cout << ans;
}