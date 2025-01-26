#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, m;
ll a[200001];
ll sm[200001];

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) sm[i] += sm[i - 1];
	ll tmp = 0ll;
	int ans = 0;
	priority_queue<ll> pq;
	for (int i = m + 1; i <= n; ++i) {
		pq.push(-a[i]);
		tmp += a[i];
		while (tmp < 0) {
			ll cur = pq.top(); pq.pop();
			tmp += cur * 2ll;
			++ans;
		}
	}
	tmp = 0ll;
	while (!pq.empty()) pq.pop();
	for (int i = m; i > 1; --i) {
		pq.push(a[i]);
		tmp -= a[i];
		while (tmp < 0) {
			ll cur = pq.top(); pq.pop();
			tmp += cur * 2ll;
			++ans;
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}