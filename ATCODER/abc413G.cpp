#include <bits/stdc++.h>
using namespace std;

vector<int> grid[200000];
vector<pair<int, int>> seg;
vector<int> idx[200000];
int H, W, K, cnt;

// 0-index
struct UF {
	vector<int> par, rk;

	UF(int _sz) {
		par.resize(_sz);
		rk.resize(_sz);
		for (int i = 0; i < _sz; ++i) par[i] = i;
	}
	int find(int x) {
		if (par[x] == x) return x;
		par[x] = find(par[x]);
		return par[x];
	}
	void union_rank(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
		if (rk[x] > rk[y]) swap(x, y);
		par[x] = y;
		if (rk[x] == rk[y]) ++rk[y];
	}
};

void solve() {
    cin >> H >> W >> K;
    while (K--) {
        int R, C; cin >> R >> C; --R; --C;
        grid[R].push_back(C);
    }
    for (int i = 0; i < H; ++i) {
        grid[i].push_back(W);
        sort(grid[i].begin(), grid[i].end());
        int s = 0;
        for (int j = 0; j < grid[i].size(); ++j) {
            if (s < grid[i][j]) {
                seg.push_back(make_pair(s, grid[i][j]));
                idx[i].push_back(cnt++);
            }
            s = grid[i][j] + 1;
        }
    }
    // for (int i = 0; i < H; ++i) {
    //     for (auto j: idx[i]) cout << j << ' ';
    //     cout << '\n';
    // }
    // cout << "seg\n";
    // for (auto i: seg) {
    //     cout << i.first << ' ' << i.second << '\n';
    // }
    UF uf{cnt};
    for (int i = 1; i < H; ++i) {
        if (idx[i - 1].empty()) continue;
        int prv = idx[i - 1][0];
        for (int j = 0; j < idx[i].size(); ++j) {
            int cur = idx[i][j];
            while (seg[prv].second <= seg[cur].first) ++prv;
            while (prv <= idx[i-1].back()
            && !(seg[prv].second <= seg[cur].first) && !(seg[cur].second <= seg[prv].first)) {
                uf.union_rank(cur, prv++);
                // cout << prv - 1 << ' ' << cur << '\n';
            }
            if (prv != idx[i - 1][0]) --prv;
        }
    }
    if (uf.find(0) == uf.find(cnt - 1)) cout << "Yes";
    else cout << "No";

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}