#include <bits/stdc++.h>
using namespace std;

int n, d, ans, h[100000], o[100000];
vector<pair<int, int>> l;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> h[i] >> o[i];
	cin >> d;
	for (int i = 0; i < n; ++i) {
		if (abs(h[i] - o[i]) <= d) {
			l.push_back({min(h[i], o[i]) + d, 1});
			l.push_back({max(h[i], o[i]), 0});
		}
	}
	sort(l.begin(), l.end());
	int cnt = 0;
	for (auto [i, j]: l) {
		// cout << i << " " << j << '\n';
		if (j == 0) ++cnt;
		else --cnt;
		ans = max(ans, cnt);
	}
	cout << ans;
}