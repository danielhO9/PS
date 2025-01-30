#include <bits/stdc++.h>
using namespace std;

int R, C;
int chess[500][500];

struct UF {
	int sz;
	vector<int> par;

	void init(int _sz) {
		sz = _sz;
		par.resize(sz);
		for (int i = 0; i < sz; ++i) par[i] = i;
	}

	int find(int x) {
		if (par[x] == x) return x;
		par[x] = find(par[x]);
		return par[x];
	}

	void union_path(int x, int y) {
		x = find(x); y = find(y);
		if (chess[x / C][x % C] < chess[y / C][y % C]) swap(x, y);
		par[x] = y;
	}
};

int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int ans[500][500];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> R >> C;
	for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) cin >> chess[i][j];
	UF uf; uf.init(R * C);
	for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) {
		int cur = i * C + j;
		int mn = chess[i][j];
		int nxt = i * C + j;
		for (int k = 0; k < 8; ++k) {
			int ni = i + dy[k], nj = j + dx[k];
			if (0 <= ni && ni < R && 0 <= nj && nj < C && mn > chess[ni][nj]) {
				mn = chess[ni][nj];
				nxt = ni * C + nj;
			}
		}
		uf.union_path(cur, nxt);
	}
	for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) {
		int top = uf.find(i * C + j);
		++ans[top / C][top % C];
	}
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) cout << ans[i][j] << ' ';
		cout << '\n';
	}
}