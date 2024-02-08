#include <bits/stdc++.h>
using namespace std;

int N, K, visited[200001], ans[200001], cnt[200001];
deque<pair<int, int>> Q;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> K;
	Q.push_back({N, 0}); visited[N] = 1; cnt[N] = 1;
	int v, c;
	while (!Q.empty()) {
		v = Q.front().first; c = Q.front().second;
		if (v - 1 >= 0) {
			if (!visited[v - 1]) {
				visited[v - 1] = 1; ans[v - 1] = c + 1; cnt[v - 1] += cnt[v];
				Q.push_back({v - 1, c + 1});
			} else if (c + 1 == ans[v - 1]) cnt[v - 1] += cnt[v];
		}
		if (v + 1 <= 200000) {
			if (!visited[v + 1]) {
				visited[v + 1] = 1; ans[v + 1] = c + 1; cnt[v + 1] += cnt[v];
				Q.push_back({v + 1, c + 1});
			} else if (c + 1 == ans[v + 1]) cnt[v + 1] += cnt[v];
		}
		if (v * 2 <= 200000) {
			if (!visited[v * 2]) {
				visited[v * 2] = 1; ans[v * 2] = c + 1; cnt[v * 2] += cnt[v];
				Q.push_back({v * 2, c + 1});
			} else if (c + 1 == ans[v * 2]) cnt[v * 2] += cnt[v];
		}
		Q.pop_front();
	}
	cout << ans[K] << "\n" << cnt[K];
}