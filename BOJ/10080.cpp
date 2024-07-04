#include <bits/stdc++.h>
using namespace std;

int A[50][50], B[50][50];
int cnt = 0;

void query(int y, int x) {
	++cnt;
	for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) A[i + y][j + x] ^= 1;
}

void solve() {
	int N, M; cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		string s; cin >> s;
		for (int j = 0; j < M; ++j) A[i][j] = s[j] - '0';
	}
	for (int i = 0; i < N; ++i) {
		string s; cin >> s;
		for (int j = 0; j < M; ++j) B[i][j] = s[j] - '0';
	}
	for (int i = 0; i < N - 2; ++i) for (int j = 0; j < M - 2; ++j) {
		if (A[i][j] == B[i][j]) continue;
		query(i, j);
	}
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		if (A[i][j] != B[i][j]) {
			cout << -1;
			return;
		}
	}
	cout << cnt;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}