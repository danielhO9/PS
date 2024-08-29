#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, k;

void solve() {
	cin >> n >> k;
	int mx;
	for (int i = 19; i >= 0; --i) if ((k >> i) & 1) {
		mx = i;
		break;
	}
	vector<int> ans;
	int s = 0;
	for (int i = 0; i < mx; ++i) ans.push_back(1 << i);
	for (auto i: ans) s += i;
	s = k - 1 - s;
	ans.push_back(s);
	ans.push_back(k + 1);
	ans.push_back((1 << (mx + 1)) + k);
	for (int i = mx + 1; i < 20; ++i) ans.push_back(1 << i);
	cout << ans.size() << '\n';
	for (auto i: ans) cout << i << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}