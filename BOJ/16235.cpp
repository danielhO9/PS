#include <bits/stdc++.h>
using namespace std;

int N, M, K;
int A[10][10];
vector<int> tree[10][10];
int dead[10][10];
int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int food[10][10];

void query() {
	memset(dead, 0, sizeof(dead));
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
		if (tree[i][j].empty()) continue;
		sort(tree[i][j].begin(), tree[i][j].end());
		for (int k = 0; k < tree[i][j].size(); ++k) {
			if (tree[i][j][k] > food[i][j]) {
				while (tree[i][j].size() > k) {
					dead[i][j] += tree[i][j].back() / 2;
					tree[i][j].pop_back();
				}
				break;
			}
			food[i][j] -= tree[i][j][k];
			++tree[i][j][k];
		}
	}
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) food[i][j] += dead[i][j] + A[i][j];
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
		for (auto k: tree[i][j]) if (k % 5 == 0) {
			for (int l = 0; l < 8; ++l) {
				int ni = i + dy[l], nj = j + dx[l];
				if (0 <= ni && ni < N && 0 <= nj && nj < N) tree[ni][nj].push_back(1);
			}
		}
	}
}

void solve() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) food[i][j] = 5;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> A[i][j];
	for (int i = 0; i < M; ++i) {
		int x, y, z; cin >> x >> y >> z;
		--x; --y; tree[x][y].push_back(z);
	}
	for (int i = 0; i < K; ++i) query();
	int ans = 0;
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) ans += tree[i][j].size();
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}