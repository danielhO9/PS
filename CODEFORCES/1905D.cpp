#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void solve() {
	LL n; cin >> n;
	vector<LL> p(n); for (int i = 0; i < n; ++i) cin >> p[i];
	vector<bool> visited(n + 1, 0);
	LL none = 0;
	deque<pair<LL, LL>> D;
	LL sum = 0, ans = 0;
	for (int i = 0; i < n; ++i) {
		visited[p[i]] = 1;
		while (visited[none]) ++none;
		if (D.empty() || D.back().first < none) D.push_back({none, 1});
		else ++D.back().second;
		sum += none;
	}
	ans = max(ans, sum);
	LL cnt = n;
	for (auto i: p) {
		sum -= D[0].first;
		if (D[0].second == 1) D.pop_front();
		else --D[0].second;
		--cnt;
		while (!D.empty() && D.back().first > i) {
			sum -= D.back().first * D.back().second;
			cnt -= D.back().second;
			D.pop_back();
		}
		if (!D.empty() && D.back().first == i) D.back().second += n - 1 - cnt;
		else D.push_back({i, n - 1 - cnt});
		sum += (n - 1 - cnt) * i;
		sum += n;
		D.push_back({n, 1});
		cnt = n;
		ans = max(ans, sum);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}

// 2 3 6 7 0 1 4 5 8 2 3 6 7 0 1 4 5
// 0 0 0 0 1 4 5 
// 0 0 0 1 2 2 2
// 0 0 1 2 2 2 3
// 0 1 2 2 2 3 6
// 1 2 2 2 3 6 7
// 0 0 0 0 0 0 0
// 0 0 0 0 0 0 1
// 0 0 0 0 0 1 4
// 0 0 0 0 1 4 5