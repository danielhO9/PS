#include <bits/stdc++.h>
using namespace std;

int n, k;
int x[200001];
int last[200001];
bool used[200001];
vector<int> ans;

void solve() {
	cin >> n >> k;
	for (int i = 1; i <= n; ++i) cin >> x[i];
	for (int i = 1; i <= n; ++i) last[x[i]] = i;
	priority_queue<pair<int, int>> pq;
	int prv = 0;
	for (int i = 1; i <= k; ++i) pq.push({-last[i], i});
	while (ans.size() != k) {
		while (used[pq.top().second]) pq.pop();
		priority_queue<pair<int, int>> npq;
		int maxx = pq.top().second;
		// cout << prv + 1 << ' ' << -pq.top().first << "\n";
		for (int i = prv + 1; i <= -pq.top().first; ++i) {
			if (!used[x[i]] && x[i] <= maxx) npq.push({-x[i], -i});
		}
		while (!npq.empty()) {
			auto here = npq.top(); npq.pop();
			if (-here.second > prv && !used[-here.first]) {
				used[-here.first] = true;
				ans.push_back(-here.first);
				prv = -here.second;
			}
		}
	}
	for (auto i: ans) cout << i << ' ';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}

/*
5 1
2 2
6 3
*/