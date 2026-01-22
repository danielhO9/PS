#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll arr[3][3];

ll gcd(ll a, ll b) {
    if (a < b) swap(a, b);
    if (b == 0) return 1;
    return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    ll g = gcd(a, b);
    return (a / g) * b;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) cin >> arr[i][j];
    ll l = lcm(arr[0][0], arr[1][0]);
    l = lcm(l, arr[2][0]);
    set<tuple<ll, int, int>> s;
    for (int i = 0; i < 3; ++i) {
        s.insert({arr[i][1], 1, i});
        s.insert({arr[i][2] + 1, -1, i});
    }
    ll t = 0;
    int cnt = 0;
    while (true) {
        auto [a, b, c] = *s.begin();
        s.erase(s.begin());

        t = a;
        cnt += b;
        if (b == -1) {
            s.insert({a + arr[c][0] - 1 - arr[c][2] + arr[c][1], 1, c});
            s.insert({a + arr[c][0] - 1 - arr[c][2] + arr[c][2] + 1, -1, c});
        }
        if (t >= l) break;
        if (cnt == 3) {
            cout << t;
            return 0;
        }
    }
    cout << -1;
}