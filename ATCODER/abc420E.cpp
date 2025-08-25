#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 0-index
struct UF {
	vector<int> par, rk, black, black_cnt;

	UF(int _sz) {
		par.resize(_sz);
		rk.resize(_sz);
        black.resize(_sz);
        black_cnt.resize(_sz);
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
        black_cnt[y] += black_cnt[x];
		if (rk[x] == rk[y]) ++rk[y];
	}
    void change(int x) {
        if (black[x]) --black_cnt[find(x)];
        else ++black_cnt[find(x)];
        black[x] ^= 1;
    }
};

int N, Q;

void solve() {
    cin >> N >> Q;
    UF uf {N + 1};
    while (Q--) {
        int t; cin >> t;
        if (t == 1) {
            int u, v; cin >> u >> v;
            uf.union_rank(u, v);
        }
        else if (t == 2) {
            int v; cin >> v;
            uf.change(v);
        }
        else {
            int v; cin >> v;
            int p = uf.find(v);
            if (uf.black_cnt[p]) cout << "Yes\n";
            else cout << "No\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}