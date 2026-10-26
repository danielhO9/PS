#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int Q;
deque<pair<ll, ll>> dq;

void solve() {
    cin >> Q;
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            ll c, x; cin >> c >> x;
            dq.push_back(make_pair(x, c));
        } else {
            ll k; cin >> k;
            ll ans = 0;
            while (k) {
                ll cnt = min(k, dq.front().second);
                ans += cnt * dq.front().first;
                dq.front().second -= cnt;
                k -= cnt;
                if (dq.front().second == 0) dq.pop_front();
            }
            cout << ans << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}