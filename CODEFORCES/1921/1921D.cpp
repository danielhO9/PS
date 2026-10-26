#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	ll n, m; cin >> n >> m;
	deque<ll> a, b;
	for (int i = 0; i < n; ++i) {
		ll num; cin >> num;
		a.push_back(num);
	}
	for (int i = 0; i < m; ++i) {
		ll num; cin >> num;
		b.push_back(num);
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	ll ans = 0;
	while (!a.empty()) {
		ll l = max(abs(a.front() - b.front()), abs(a.front() - b.back()));
		ll r = max(abs(a.back() - b.front()), abs(a.back() - b.back()));
		if (l > r) {
			ans += l;
			if (abs(a.front() - b.front()) > abs(a.front() - b.back())) b.pop_front();
			else b.pop_back();
			a.pop_front();
		} else {
			ans += r;
			if (abs(a.back() - b.front()) > abs(a.back() - b.back())) b.pop_front();
			else b.pop_back();
			a.pop_back();
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}