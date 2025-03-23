#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll a[9];

void solve() {
    ll x, y; cin >> x >> y;
    ll val = 0;
    ll pow = 1;
    for (ll i = 0; i < N; ++i) {
        val += pow * a[i];
        pow *= x;
    }
    if (y == val) cout << "On\n";
    else if (y < val) cout << "Inside\n";
    else cout << "Outside\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while (true) {
        cin >> N;
        for (int i = 0; i < N; ++i) cin >> a[i];
        if (N == 0) break;
        solve();
    }
}