#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    priority_queue<ll> pq;
    int K; cin >> K;
    for (int i = 0; i < K; ++i) {
        ll tmp; cin >> tmp;
        pq.push(-tmp);
    }
    ll ans = 0;
    while (pq.size() >= 2) {
        ll a = -pq.top(); pq.pop();
        ll b = -pq.top(); pq.pop();
        ans += a + b;
        pq.push(-(a + b));
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}