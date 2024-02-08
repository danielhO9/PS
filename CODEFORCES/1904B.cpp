#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	int n; cin >> n;
	vector<pair<LL, int>> V;
	LL a[n];
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		V.push_back({a[i], i});
	}
	sort(V.begin(), V.end());
	vector<int> ans(n, -1);
	LL sum = 0;
	for (int i = 0; i < n; ++i) {
		if (ans[i] != -1) continue;
		int end = i;
		sum += V[i].first;
		while (true) {
			if (end == n - 1) break;
			if (V[end + 1].first <= sum) {
				++end;
				sum += V[end].first;
			} else {
				break;
			}
		}
		for (int j = i; j <= end; ++j) {
			ans[j] = end;
		}
	}
	vector<int> ret(n);
	for (int i = 0; i < n; ++i) ret[V[i].second] = ans[i];
	for (auto i: ret) cout << i << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}