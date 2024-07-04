#include <bits/stdc++.h>
using namespace std;
int N;
vector<int> s[3];
int ans[2];

void query(int x, int idx) {
	if (x == 0) {
		s[idx][0] ^= 1;
		s[idx][1] ^= 1;
	} else if (x == N - 1) {
		s[idx][N - 1] ^= 1;
		s[idx][N - 2] ^= 1;
	} else {
		for (int i = -1; i <= 1; ++i) s[idx][i + x] ^= 1;
	}
}

void solve() {
	cin >> N;
	for (int i = 0; i < 2; ++i) {
		string tmp; cin >> tmp;
		for (int j = 0; j < N; ++j) s[i == 1 ? i + 1 : i].push_back(tmp[j] - '0');
	}
	for (int i = 0; i < N; ++i) s[1].push_back(s[0][i]);
	ans[1] = 1; query(0, 1);
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < N - 1; ++j) {
			if (s[i][j] != s[2][j]) {
				++ans[i];
				query(j + 1, i);
			}
		}
	}
	int cnt = 987654321;
	for (int i = 0; i < 2; ++i) {
		bool flag = true;
		for (int j = 0; j < N; ++j) if (s[i][j] != s[2][j]) {
			flag = false;
			break;
		}
		if (flag) cnt = min(cnt, ans[i]);
	}
	if (cnt == 987654321) cout << -1;
	else cout << cnt;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}