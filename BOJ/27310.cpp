#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s; cin >> s;
    int ans = 0;
    for (auto i: s) {
        if (i == ':') ++ans;
        if (i == '_') ans += 5;
    }
    ans += s.size();
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}