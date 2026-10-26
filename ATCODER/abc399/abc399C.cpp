#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
		par[x] = y;
	}
};

int N, M;

void solve() {
    cin >> N >> M;
    UF uf; uf.init(N + 1);
    int ans = 0;
    while (M--) {
        int u, v; cin >> u >> v;
        if (uf.find(u) == uf.find(v)) ++ans;
        uf.union_path(u, v);
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}