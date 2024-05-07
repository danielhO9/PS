#include <bits/stdc++.h>
using namespace std;

int N, K;
int belt[202];
bool robot[202];
int cnt = 0, ans = 0;

void query() {
	++ans;
	for (int i = 2 * N; i >= 1; --i) {
		belt[i + 1] = belt[i];
		robot[i + 1] = robot[i];
	}
	belt[1] = belt[2 * N + 1];
	robot[1] = robot[2 * N + 1];
	robot[N] = false;
	for (int i = N - 1; i >= 1; --i) {
		if (robot[i] && !robot[i + 1] && belt[i + 1] >= 1) {
			--belt[i + 1];
			if (belt[i + 1] == 0) ++cnt;
			robot[i + 1] = true;
			robot[i] = false;
		}
	}
	robot[N] = false;
	if (belt[1] >= 1) {
		--belt[1];
		if (belt[1] == 0) ++cnt;
		robot[1] = true;
	}
}

void solve() {
	memset(robot, false, sizeof(robot));
	cin >> N >> K;
	for (int i = 1; i <= 2 * N; ++i) cin >> belt[i];
	while (cnt < K) query();
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}