#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, k;
ll l[200000], r[200000];

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> l[i];
    for (int i = 0; i < n; ++i) cin >> r[i];
    ll ans = 0;
    priority_queue<ll> pq;
    for (int i = 0; i < n; ++i) {
        ans += max(l[i], r[i]);
        pq.push(min(l[i], r[i]));
    }
    for (int i = 0; i < k - 1; ++i) {
        ans += pq.top(); pq.pop();
    }
    ++ans;
    cout << ans << '\n';

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}