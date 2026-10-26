#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    ll X, Y; cin >> X >> Y;
    for (int i = 0; i < 8; ++i) {
        ll tmp = X + Y;
        string ss = to_string(tmp);
        reverse(ss.begin(), ss.end());
        tmp = stoll(ss);
        X = Y;
        Y = tmp;
    }
    cout << Y;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}