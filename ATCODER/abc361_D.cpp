#include <bits/stdc++.h>
using namespace std;

int cache[1<<16][15];

void solve() {
	int N; cin >> N;
	string S, T; cin >> S >> T;
	memset(cache, -1, sizeof(cache));
	int src = 0;
	for (int i = 0; i < N; ++i) {
		if (S[i] == 'W') src ^= (1 << i);
	}
	// cout << src << ' ';
	
	int target = 0;
	for (int i = 0; i < N; ++i) {
		if (T[i] == 'W') target ^= (1 << i);
	}
	// cout << target << ' ';

	queue<pair<int, int>> Q; Q.push({src, N}); cache[src][N] = 0;
	while (!Q.empty()) {
		int here = Q.front().first, emp = Q.front().second; Q.pop();
		// cout << here << ' '<< emp << '\n';
		for (int i = 0; i <= N; ++i) if (i != emp && i != emp + 1 && i != emp - 1) {
			int there = here;
			if ((here >> i) & 1) {
				there ^= (1 << emp);
				there ^= (1 << i);
			}
			if ((here >> (i + 1)) & 1) {
				there ^= (1 << (emp + 1));
				there ^= (1 << (i + 1));
			}
			if (cache[there][i] != -1) continue;
			cache[there][i] = cache[here][emp] + 1;
			Q.push({there, i});
		}
	}
	cout << cache[target][N];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}