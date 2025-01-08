#include <bits/stdc++.h>
using namespace std;

int N;
int dis[501][501];
int cnt;
int used = 0;
random_device rd;
mt19937 gen(rd());
vector<int> v[500];

void query(int x, int y, bool hard) {
	if (hard) {
		if (dis[x][y] >= 0) return;
	} else if (dis[x][y] != -1) return;
	++used;
	cnt -= 2;
	cout << "? " << x << ' ' << y << '\n';
	cout.flush();
	int ret; cin >> ret;
	assert(ret != -1);
	dis[x][y] = ret;
	dis[y][x] = ret;
}

void solve() {
	cin >> N;

	memset(dis, -1, sizeof(dis));
	for (int i = 1; i <= N; ++i) dis[i][i] = 0;

	cnt = N * N - N;
	vector<int> toChoose;
	for (int i = 1; i <= N; ++i) toChoose.push_back(i);
	shuffle(toChoose.begin(), toChoose.end(), gen);

	for (int i = 0; i < N; ++i) {
		if ((cnt / 2) + used <= 30000) break;
		
		for (int j = 0; j < N; ++j) v[j].clear();

		int cur = toChoose[i];
		for (int j = 1; j <= N; ++j) {
			query(cur, j, true);
			v[dis[cur][j]].push_back(j);
		}
		for (int j = 0; j < N; ++j) for (int k = 0; k < N; ++k) if (abs(j - k) > 1) {
			for (int a: v[j]) for (int b: v[k]) if (dis[a][b] == -1) {
				dis[a][b] = -2;
				dis[b][a] = -2;
				cnt -= 2;
			}
		}
	}
	vector<pair<int, int>> ans;
	for (int i = 1; i <= N; ++i) for (int j = i + 1; j <= N; ++j) {
		query(i, j, false);
		if (dis[i][j] == 1) ans.push_back({i, j});
	}
	cout << "! " << ans.size() << '\n';
	for (auto i: ans) cout << i.first << ' ' << i.second << '\n';
	cout.flush();
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}