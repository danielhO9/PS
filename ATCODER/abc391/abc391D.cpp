#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, W;
deque<pair<int, int>> pts[200001];
int ans[200001];

void solve() {
	cin >> N >> W;
	for (int i = 1; i <= N; ++i) {
		int x, y; cin >> x >> y;
		pts[x].push_back({y, i});
	}
	for (int i = 1; i <= W; ++i) sort(pts[i].begin(), pts[i].end());
	int cur = 1;
	int tm = 0;
	memset(ans, -1, sizeof(ans));
	while (true) {
		vector<int> v;
		bool flag = true;
		for (int i = 1; i <= W; ++i) {
			if (pts[i].empty()) {
				flag = false;
				break;
			}
			tm = max(tm, pts[i].front().first);
			v.push_back(pts[i].front().second);
			pts[i].pop_front();
		}
		if (!flag) {
			for (int i = 1; i <= N; ++i) if (ans[i] == -1) ans[i] = INT32_MAX;
			break;
		}
		for (auto i: v) ans[i] = tm;
	}
	// for (int i = 1; i <= N; ++i) cout << ans[i] << ' ';
	int Q; cin >> Q;
	while (Q--) {
		int t, a; cin >> t >> a;
		if (ans[a] <= t) cout << "No\n";
		else cout << "Yes\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}