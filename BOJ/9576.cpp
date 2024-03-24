#include <bits/stdc++.h>
using namespace std;

void solve() {
	int N, M; cin >> N >> M;
	vector<pair<int, int>> book;
	for (int i = 0; i < M; ++i) {
		int a, b; cin >> a >> b;
		book.push_back({a, b});
	}
	sort(book.begin(), book.end(), [](const auto& a, const auto & b) {
		if (a.second == b.second) return a.first < b.first;
		return a.second < b.second;
	});
	vector<bool> used(N + 1, false);
	int ans = 0;
	for (int i = 0; i < M; ++i) {
		for (int j = book[i].first; j <= book[i].second; ++j) {
			if (!used[j]) {
				used[j] = true; ++ans; break;
			}
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}