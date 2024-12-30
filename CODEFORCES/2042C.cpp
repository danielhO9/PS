#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, k;
string s;

void solve() {
	cin >> n >> k;
	cin >> s;
	vector<ll> sum(n);
	for (int i = n - 1; i >= 0; --i) {
		if (i == n - 1) sum[i] = (s[i] == '1');
		else {
			sum[i] = sum[i + 1] + (s[i] == '1');
		}
	}
	priority_queue<ll> pq;
	for (int i = 1; i < n; ++i) {
		sum[i] = sum[i] - (n - i - sum[i]);
		pq.push(sum[i]);
	}
	ll num = 0ll;
	ll ans = 1;
	while (!pq.empty()) {
		if (pq.top() <= 0) {
			pq.pop();
			continue;
		}
		num += pq.top(); pq.pop();
		++ans;
		if (num >= k) {
			cout << ans << '\n';
			return;
		}
	}
	cout << -1 << '\n';

	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}