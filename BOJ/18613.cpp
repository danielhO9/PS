#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
8, 9,      0,      1, 0,      9
1, 1 + 2x, 2 + 4x, 1, 2 + 2x, 4 + 4x
11 + 12x
6x^2 + 17x + 11
*/

ll n;

void solve() {
    cin >> n;
    ll l = -1, r = 1e9, mid;
    while (l + 1 < r) {
        mid = (l + r) / 2;
        if (n <= 6 * mid * mid + 17 * mid + 11) r = mid;
        else l = mid;
    }
    --r;
    ll p = (r == -1 ? 0: 6 * r * r + 17 * r + 11);
    ++r;
    n -= p;
    if (n == 1) cout << 8;
    else if (n <= 2 + 2 * r) cout << 9;
    else if (n <= 4 + 6 * r) cout << 0;
    else if (n <= 5 + 6 * r) cout << 1;
    else if (n <= 7 + 8 * r) cout << 0;
    else cout << 9;
    cout << ' ';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}