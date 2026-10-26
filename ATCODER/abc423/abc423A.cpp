#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    ll X, C; cin >> X >> C;
    ll tmp = X / (1000ll + C);
    cout << tmp * (1000 );
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}