#include <bits/stdc++.h>
using namespace std;

// 0-index
struct UF {
	vector<int> par, sz;

	void init(int _sz) {
		par.resize(_sz);
		sz.resize(_sz);
		for (int i = 0; i < _sz; ++i) par[i] = i;
		for (int i = 0; i < _sz; ++i) sz[i] = 1;
	}

	int find(int x) {
		if (par[x] == x) return x;
		par[x] = find(par[x]);
		return par[x];
	}

	void union_path(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
		if (sz[x] > sz[y]) swap(x, y);
		par[x] = y;
		sz[y] += sz[x];
	}
};