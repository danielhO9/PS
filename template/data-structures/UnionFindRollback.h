/**
 * Description: Union-Find data structure with rollback capability.
 *  Supports merging sets and rolling back merge operations to a previous state.
 *  Crucial for algorithms like dynamic connectivity.
 *  The `find` operation does NOT use path compression, which is necessary for the rollback to function correctly.
 * Time: `merge` and `find` are $O(\log N)$. `rollback` is proportional to the number of merges to undo.
 */
struct UnionFindRollback {
	vector<int> par, rk;
    vector<tuple<int, int, int>> st;

    UnionFindRollback() = default;
	UnionFindRollback(int sz) {
		par.resize(sz);
		rk.resize(sz);
		for (int i = 0; i < sz; ++i) par[i] = i;
	}
    int time() { return st.size(); }
    void rollback(int t) {
        while (st.size() > t) {
            auto [v, p, r] = st.back(); st.pop_back();
            par[v] = p;
            rk[v] = r;
        }
    }
	int find(int x) {
		while (par[x] != x) x = par[x];
		return x;
	}
	void merge(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
        st.push_back({x, par[x], rk[x]});
        st.push_back({y, par[y], rk[y]});
		if (rk[x] > rk[y]) swap(x, y);
		par[x] = y;
		if (rk[x] == rk[y]) ++rk[y];
	}
};