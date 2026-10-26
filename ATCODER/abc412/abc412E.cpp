#include <bits/stdc++.h>
using namespace std;
typedef unsigned long ull;
typedef long long ll;

ll L, R;
bool isP[10000001];
vector<ll> p;

void solve() {
    cin >> L >> R;
    for (int i = 2; i <= 10000000; ++i) isP[i] = true;
    vector<bool> v(R - L + 1, true);
    for (ll i = 2; i <= 10000000; ++i) if (isP[i]) {
        p.push_back(i);
        for (ll j = i * 2; j <= 10000000; j += i) isP[j] = false;

        ll val = i * (L / i);
        while (val < L) val += i;
        val = max(val, i * 2);
        for (ll j = val; j <= R; j += i) {
            // cout << j << ' ';
            v[j - L] = false;
        }
    }
    int ans = 0;
    if (!v[0]) ++ans;
    for (auto i: v) if (i) ++ans;
    for (auto i: p) {
        ll j = i * i;
        while (j <= R) {
            if (!v[0] && j == L) --ans;
            if (j >= L) {
                ++ans;
            }
            if (100000000000000ll / i < j) break;
            j *= i;
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}