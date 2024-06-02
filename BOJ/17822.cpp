#include <bits/stdc++.h>
using namespace std;

int N, M, T;
deque<int> num[50];
int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, 1, -1};

void query(int x, int d, int k) {
	for (int i = x; i <= N; i += x) {
		int p = i - 1;
		if (d == 0) {
			for (int j = 0; j < k; ++j) {
				int tmp = num[p].back(); num[p].pop_back();
				num[p].push_front(tmp);
			}
		} else {
			for (int j = 0; j < k; ++j) {
				int tmp = num[p].front(); num[p].pop_front();
				num[p].push_back(tmp);
			}
		}
	}
	bool flag = true;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		if (num[i][j] == 0) continue;
		int hnum = num[i][j];
		queue<pair<int, int>> Q; Q.push({i, j});
		bool fflag = false;
		while (!Q.empty()) {
			auto [y, x] = Q.front(); Q.pop();
			for (int k = 0; k < 4; ++k) {
				int ny = y + dy[k], nx = x + dx[k];
				if (nx == M) nx = 0;
				if (nx == -1) nx = M - 1;
				if (0 <= ny && ny < N && 0 <= nx && nx < M && num[ny][nx] == hnum) {
					fflag = true;
					flag = false;
					Q.push({ny, nx});
					// cout << ny << ' ' << nx << '\n';
					num[ny][nx] = 0;
				}
			}
		}
		if (fflag) {
			num[i][j] = 0;
			// cout << i << ' ' << j << '\n';
		}
	}
	if (flag) {
		int sum = 0, cnt = 0;
		for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
			if (num[i][j] != 0) {
				sum += num[i][j]; ++cnt;
			}
		}
		if (cnt > 0) {
			double avg = (double) sum / cnt;
			for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
				if (num[i][j] == 0) continue;
				if (num[i][j] > avg) --num[i][j];
				else if (num[i][j] < avg) ++num[i][j];
			}
		}
	}
}

void solve() {
	cin >> N >> M >> T;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			int tmp; cin >> tmp;
			num[i].push_back(tmp);
		}
	}
	for (int i = 0; i < T; ++i) {
		int x, d, k; cin >> x >> d >> k;
		query(x, d, k);
	}
	int sum = 0;
	for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
		sum += num[i][j];
		// if (num[i][j] != 0) cout << i << ' ' << j << '\n';
	}
	cout << sum;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}