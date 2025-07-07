#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 1-index
struct Fenwick {
    vector<ll> tree;

    Fenwick(int sz) { tree.resize(sz); }
    void update(int i, ll dif) { while (i < tree.size()) { tree[i] += dif; i += (i & -i); } }
    ll query(int i) {
        ll ret = 0;
        while (i > 0) { ret += tree[i]; i -= (i & -i); }
        return ret;
    }
};

void solve() {
	int N, M, K; cin >> N >> M >> K;
	Fenwick tree {N+1};
	vector<ll> a(N); for (int i = 0; i < N; ++i) cin >> a[i];
	for (int i = 0; i < N; ++i) tree.update(i + 1, a[i]);
	M += K;
	while (M--) {
		ll t, b, c; cin >> t >> b >> c;
		if (t == 1) {
			tree.update(b, c - a[b-1]);
			a[b-1] = c;
		}
		else cout << tree.query(c) - tree.query(b - 1) << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}