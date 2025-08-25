#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    int x, y; cin >> x >> y;
    int ans = (x + y) % 12;
    if (ans == 0) ans = 12;
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}