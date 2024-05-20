#include <bits/stdc++.h>
using namespace std;

int r, c, k;
int arr[100][100];
int cnt[101];
int m, n;

void query() {
	if (m >= n) {
		int nn = 0;
		for (int i = 0; i < m; ++i) {
			memset(cnt, 0, sizeof(cnt));
			for (int j = 0; j < n; ++j) ++cnt[arr[i][j]];
			set<pair<int, int>> S;
			for (int j = 1; j <= 100; ++j) if (cnt[j] > 0) S.insert({cnt[j], j});
			for (int j = 0; j < n; ++j) arr[i][j] = 0;
			int tmp = 0;
			for (auto [j, k]: S) {
				if (tmp == 100) break;
				arr[i][tmp++] = k;
				if (tmp == 100) break;
				arr[i][tmp++] = j;
			}
			nn = max(nn, tmp);
		}
		n = nn;
	} else {
		int nm = 0;
		for (int i = 0; i < n; ++i) {
			memset(cnt, 0, sizeof(cnt));
			for (int j = 0; j < m; ++j) ++cnt[arr[j][i]];
			set<pair<int, int>> S;
			for (int j = 1; j <= 100; ++j) if (cnt[j] > 0) S.insert({cnt[j], j});
			for (int j = 0; j < m; ++j) arr[j][i] = 0;
			int tmp = 0;
			for (auto [j, k]: S) {
				if (tmp == 100) break;
				arr[tmp++][i] = k;
				if (tmp == 100) break;
				arr[tmp++][i] = j;
			}
			nm = max(nm, tmp);
		}
		m = nm;
	}
}

void solve() {
	cin >> r >> c >> k; --r; --c;
	memset(arr, 0, sizeof(arr));
	for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) cin >> arr[i][j];
	m = 3, n = 3;
	int t = 0;
	while (t < 101 && arr[r][c] != k) {
		query(); ++t;
	}
	if (t == 101) cout << -1;
	else cout << t;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}