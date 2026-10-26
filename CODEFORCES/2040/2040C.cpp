#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, k;
int way[200001];

void solve() {
	cin >> n >> k; --k;
	if (n < 60 && k >= (1ll << (n - 1))) {
		cout << -1 << '\n';
		return;
	}
	deque<int> ans;
	for (int i = 1; i < n; ++i) {
		ll val;
		if (n - 1 - i <= 60) val = (1ll << (n - 1 - i));
		else val = 1e12;
		if (k >= val) {
			way[i] = 1;
			k -= val;
		} else way[i] = 0;
	}
	ans.push_back(n);
	for (int i = n - 1; i >= 1; --i) {
		if (way[i]) ans.push_back(i);
		else ans.push_front(i);
	}
	for (auto i: ans) cout << i << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}