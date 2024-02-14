#include <bits/stdc++.h>
using namespace std;

void solve() {
	int N, K, D; cin >> N >> K >> D;
	vector<vector<int>> m(N);
	vector<int> d(N);
	vector<pair<int, int>> V;
	for (int i = 0; i < N; ++i) {
		int M; cin >> M >> d[i];
		V.push_back({d[i], i});
		for (int j = 0; j < M; ++j) {
			int t; cin >> t;
			m[i].push_back(t);
		}
	}
	sort(V.begin(), V.end());

	int r = 0;
	int cnt[31];
	int ans = 0;
	memset(cnt, 0, sizeof(cnt));
	for (auto i: m[V[0].second]) ++cnt[i];
	for (int l = 0; l < N; ++l) {
		while (r + 1 < N && V[r + 1].first - V[l].first <= D) {
			++r;
			for (auto i: m[V[r].second]) ++cnt[i];
		}
		int temp = 0;
		for (int i = 1; i <= 30; ++i) if (1 <= cnt[i] && cnt[i] < (r - l + 1)) ++temp;
		ans = max(temp * (r - l + 1), ans);
		for (auto i: m[V[l].second]) --cnt[i];
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}