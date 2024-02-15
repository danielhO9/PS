#include <bits/stdc++.h>
using namespace std;

void solve() {
	int n; cin >> n;
	vector<int> c(n + 1);
	unordered_map<int, int> M;
	for (int i = 1; i <= n; ++i) {
		cin >> c[i];
		M[c[i]] = i;
	}
	int k; cin >> k;
	vector<pair<int, int>> temp;
	for (auto [i, j]: M) temp.push_back({i, j});
	sort(temp.begin(), temp.end());
	vector<pair<int, int>> V;
	for (auto [i, j]: temp) if (V.empty() || V.back().second < j ) V.push_back({i, j});
	// for (auto i: V) {
	// 	cout << i.first << ' ' << i.second << '\n';
	// }
	vector<int> cnt(V.size(), 0);
	int rem = k;
	for (int i = 0; i < V.size(); ++i) {
		if (i == 0) {
			cnt[i] = rem / V[i].first;
			rem -= V[i].first * cnt[i];
		}
		else {
			cnt[i] = min(cnt[i - 1], rem / (V[i].first - V[i - 1].first));
			rem -= (V[i].first - V[i - 1].first) * cnt[i];
		}
		
	}
	// for (auto i: cnt) cout << i << ' ';
	vector<int> ans(n + 1, 0);
	int now = 0;
	for (int i = 1; i <= n; ++i) {
		if (V[now].second < i) {
			++now;
			if (now == V.size()) break;
		}
		ans[i] = cnt[now];
	}
	for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t; cin >> t;
	while (t--) solve();
}