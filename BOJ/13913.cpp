#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 1;

void solve() {
	int N, K; cin >> N >> K;
	int time[MAX]; memset(time, -1, sizeof(time));
	deque<int> Q; Q.push_back(N); time[N] = 0;
	while (!Q.empty()) {
		int here = Q.front(); Q.pop_front();
		if (0 <= here - 1 && time[here - 1] == -1) {
			Q.push_back(here - 1); time[here - 1] = time[here] + 1;
			if (here - 1 == K) break;
		}
		if (here + 1 < MAX && time[here + 1] == -1) {
			Q.push_back(here + 1); time[here + 1] = time[here] + 1;
			if (here + 1 == K) break;
		}
		if (here * 2 < MAX && time[here * 2] == -1) {
			Q.push_back(here * 2); time[here * 2] = time[here] + 1;
			if (here * 2 == K) break;
		}
	}
	cout << time[K] << '\n';
	vector<int> ans;
	int x = K;
	while (x != N) {
		ans.push_back(x);
		if (0 <= x - 1 && x - 1 < MAX && time[x - 1] == time[x] - 1) {
			x = x - 1; continue;
		}
		if (0 <= x + 1 && x + 1 < MAX && time[x + 1] == time[x] - 1) {
			x = x + 1; continue;
		}
		if (x % 2 == 0 && 0 <= x / 2 && x / 2 < MAX && time[x / 2] == time[x] - 1) {
			x = x / 2; continue;
		}
	}
	ans.push_back(N);
	for (int i = (int) ans.size() - 1; i >= 0; --i) cout << ans[i] << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}