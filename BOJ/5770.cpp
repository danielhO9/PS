#include <bits/stdc++.h>
using namespace std;

int P, S, N;

void solve() {
	vector<int> trap(3);
	vector<int> pos(P);
	vector<bool> flag(P, false);
	for (int i = 0; i < 3; ++i) cin >> trap[i];
	cin >> N;
	int ans = -1;
	int cur = 0;
	for (int i = 0; i < N; ++i) {
		int D1, D2; cin >> D1 >> D2;
		if (ans != -1) continue;
		int D = D1 + D2;
		pos[cur] += D;
		if (pos[cur] > S) ans = cur;
		for (auto i: trap) if (pos[cur] == i) flag[cur] = true;
		cur = (cur + 1) % P;
		while (flag[cur]) {
			flag[cur] = false;
			cur = (cur + 1) % P;
		}
	}
	cout << ans + 1 << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	while (true) {
		cin >> P >> S;
		if (P == 0) break;
		solve();
	}
}