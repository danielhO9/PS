#include <bits/stdc++.h>
using namespace std;

double n1, m1, n2, m2;

void solve() {
    cin >> n1 >> m1 >> n2 >> m2;
    double ans = 0;
    double cur = 1.0;
    for (int i = 0; i < m1; ++i) {
        cur *= n1 - i;
        cur /= n1 + n2 + 1 - i;
    }
    cur *= n1 + 1; cur /= n1 + n2 + 2;
    ans += cur;
    for (int i = 1; i <= m2; ++i) {
        cur *= n2 + 1 - (i - 1); cur /= i;
        cur /= n1 + n2 + 2 - m1 - i; cur *= i + m1;
        ans += cur;
    }
    cout << fixed;
    cout.precision(10);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}