#include <bits/stdc++.h>
using namespace std;

// zzeca
// azzec
// zzeeca
// zzeec
// zzee
// zze
// zz

void solve() {
	int n; cin >> n;
	string s; cin >> s;
	vector<int> V(n);
	for (int i = 0; i < n; ++i) V[i] = s[i] - 'a';
	vector<vector<int>> ind(26);
	for (int i = 0; i < n; ++i) {
		ind[V[i]].push_back(i);
	}
	vector<int> maxV(n);
	for (int i = 0; i < n; ++i) maxV[i] = V[i];
	vector<int> largesti;
	vector<int> largestv;
	int now = 0;
	int temp = -1;
	for (int i = 25; i >= 0; --i) {
		if (ind[i].empty()) continue;
		if (temp < 0) temp = ind[i].size();
		auto ite = lower_bound(ind[i].begin(), ind[i].end(), now);
		for (auto j = ite; j != ind[i].end(); ++j) {
			largesti.push_back(*j);
			largestv.push_back(V[*j]);
			maxV[*j] = -1;
			now = *j;
		}
	}
	for (int i = 1; i < n; ++i) {
		if (maxV[i] != -1 && maxV[i] < maxV[i - 1]) {
			cout << -1 << '\n';
			return;
		}
		maxV[i] = max(maxV[i], maxV[i - 1]);
	}
	int m = largesti.size();
	sort(largestv.begin(), largestv.end());
	// for (auto i: largesti) cout << i << ' ';
	// cout << '\n';
	// for (auto i: largestv) cout << i << ' ';
	// cout << '\n';
	for (int i = 0; i < m; ++i) {
		V[largesti[i]] = largestv[i];
	}
	for (int i = 1; i < n; ++i) {
		if (V[i - 1] > V[i]) {
			cout << -1 << '\n';
			return;
		}
	}
	int ans = largesti.size(); 
	ans -= temp;
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}