#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	LL X; cin >> X;
	int L = 0, R = 1e9;
	LL t;
	for (LL i = 59; i >= 0; --i) if ((X | (1LL << i)) == X) { t = i; break; }
	vector<LL> ans;
	for (LL i = 0; i < t; ++i) {
		if ((X | (1LL << i)) == X) ans.push_back(R--);
		if (i == t - 1) break;
		ans.push_back(L++);
	}
	ans.push_back(R--);
	cout << ans.size() << '\n';
	for (auto i: ans) cout << i << ' ';
	cout << '\n';
}

int main() {
	int t; cin >> t;
	while (t--) solve();
}