#include <bits/stdc++.h>
using namespace std;

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
	void merge(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
		if (rk[x] > rk[y]) swap(x, y);
		par[x] = y;
		if (rk[x] == rk[y]) ++rk[y];
	}
};

int N, M;
string adj[50];
int deg[50];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; ++i) cin >> adj[i];
    UF uf {N};
    int rem = M - (N - 1);
    for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) if (adj[i][j] == 'Y') {
        if (uf.find(i) != uf.find(j)) {
            ++deg[i]; ++deg[j];
            uf.merge(i, j);
        } else if (rem) {
            --rem;
            ++deg[i]; ++deg[j];
        }
    }
    if (rem != 0) {
        cout << -1;
        return 0;
    }
    int rt = uf.find(0);
    for (int i = 0; i < N; ++i) if (uf.find(i) != rt) {
        cout << -1;
        return 0;
    }
    for (int i = 0; i < N; ++i) cout << deg[i] << ' ';
}