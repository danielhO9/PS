#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	ll n; cin >> n;
	vector<ll> todo;
	ll s = 0ll;
	for (ll i = 59; i >= 0; --i) if ((n >> i) & 1) {
		todo.push_back(i);
		s += (1ll << i);
	}
	vector<ll> ans;
	for (auto i: todo) {
		if (s - (1ll << i) != 0) ans.push_back(s - (1ll << i));
	}
	ans.push_back(s);
	cout << ans.size() << '\n';
	for (auto i: ans) cout << i << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}