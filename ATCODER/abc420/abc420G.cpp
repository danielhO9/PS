#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll X;

void solve() {
    cin >> X;
    ll A = 1ll - 4ll * X;
    set<ll> s;
    ll AA = abs(A);
    vector<ll> fac;
    for (ll i = 1; i * i <= AA; ++i) {
        if (AA % i == 0) {
            fac.push_back(i);
            fac.push_back(AA / i);
        }
    }
    for (auto u: fac) {
        ll v = abs(A) / u;
        if (A < 0) v *= -1ll;
        ll tmp = u + v - 2;
        if (tmp % 4 == 0) s.insert(tmp / 4);
        ll uu = -u, vv = -v;
        tmp = uu + vv - 2;
        if (tmp % 4 == 0) s.insert(tmp / 4);
    }
    cout << s.size() << '\n';
    for (auto i: s) cout << i << ' ';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}