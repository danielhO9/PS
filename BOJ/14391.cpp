#include <bits/stdc++.h>
using namespace std;

char paper[4][4];
bool used[4][4];
int ans = 0;
int N, M;

int getNum(int i, int j, int right, int cnt) {
	int dx[2] = {0, 1};
	int dy[2] = {1, 0};
	string num = "";
	++cnt;
	while (cnt--) {
		num += paper[i][j];
		j += dx[right];
		i += dy[right];
	}
	return stoi(num);
}

void generator(int i, int j, int val) {
	if (i == N) {
		ans = max(ans, val);
		return;
	}
	int nj = (j + 1) % M, ni = i;
	if (nj == 0) ++ni;
	if (used[i][j]) {
		generator(ni, nj, val);
		return;
	}
	for (int len = 0; len < M - j; ++len) {
		if (used[i][j +len]) break;
		for (int k = j; k <= j + len; ++k) used[i][k] = true;
		generator(ni, nj, val + getNum(i, j, 1, len));
		for (int k = j; k <= j + len; ++k) used[i][k] = false;
	}
	for (int len = 0; len < N - i; ++len) {
		if (used[i + len][j]) break;
		for (int k = i; k <= i + len; ++k) used[k][j] = true;
		generator(ni, nj, val + getNum(i, j, 0, len));
		for (int k = i; k <= i + len; ++k) used[k][j] = false;
	}
}

void solve() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> paper[i][j];
	memset(used, 0, sizeof(used));
	generator(0, 0, 0);
	cout << ans;
	// cout << getNum(0, 0, 1, 2);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}