#include <bits/stdc++.h>
using namespace std;

int cache[200000][3];
int N;
int moves[200000];

int matchCache(int idx, int t) {
	if (idx == 0) {
		if ((moves[idx] + 2) % 3 == t) return 1;
		else if (moves[idx] == t) return 0;
		else return -987654321;
	}
	int& ret = cache[idx][t];
	if (ret != -1) return ret;
	if ((moves[idx] + 2)%3 == t) {
		ret = max(matchCache(idx - 1, (t + 1) % 3), matchCache(idx - 1, (t + 2) % 3)) + 1;
	} else if (moves[idx] == t) {
		ret = max(matchCache(idx - 1, (t + 1) % 3), matchCache(idx - 1, (t + 2) % 3));
	} else {
		ret = -987654321;
	}
	return ret;
}

void solve() {
	memset(cache, -1, sizeof(cache));
	cin >> N;
	string S; cin >> S;
	for (int i = 0; i < N; ++i) {
		if (S[i] == 'R') moves[i] = 0;
		else if (S[i] == 'S') moves[i] = 1;
		else moves[i] = 2;
	}
	int ans = 0;
	for (int i = 0; i < 3; ++i) ans = max(ans, matchCache(N - 1, i));
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}