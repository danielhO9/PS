#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
string c1, c2;

void solve() {
    cin >> N >> c1 >> c2;
    string cc1 = c1, cc2 = c2;
    ll ans = LLONG_MAX;
    for (ll t = 0; t < 2; ++t) {
        ll tans = 0;
        ll x1 = 0, x2 = 0, Y1 = 0, y2 = 0, i1 = 1, i2 = 1;
        while (i1 < 2 * N && c1[i1] != 'U') ++i1;
        while (i2 < 2 * N && c2[i2] != 'R') ++i2;
        if (c1[0] != 'U') {
            tans += i1;
            swap(c1[i1], c1[0]);
        }
        if (c2[0] != 'R') {
            tans += i2;
            swap(c2[i2], c2[0]);
        }
        for (ll i = 0; i < 2 * N - 1; ++i) {
            while (i1 <= i) ++i1;
            while (i2 <= i) ++i2;
            while (i1 < 2 * N && c1[i1] != 'U') ++i1;
            while (i2 < 2 * N && c2[i2] != 'R') ++i2;
            if (c1[i] == 'R') ++x1;
            else ++Y1;
            if (c2[i] == 'R') ++x2;
            else ++y2;
            if (x1 == x2 && Y1 == y2) {
                assert(c1[i] == 'R' && c2[i] == 'U');
                if (i2 == 2 * N || i1 - i < i2 - i) {
                    tans += i1 - i;
                    swap(c1[i], c1[i1]);
                    ++Y1; --x1;
                } else {
                    tans += i2 - i;
                    swap(c2[i], c2[i2]);
                    ++x2; --y2;
                }
            }
            // cout << c1 << ' ' << c2 << "\n";
        }
        // cout << c1 << ' ' << c2 << "\n";
        // cout << '\n';
        ans = min(ans, tans);
        c2 = cc1;
        c1 = cc2;
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}