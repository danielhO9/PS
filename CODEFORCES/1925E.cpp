#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

void init(vector<LL> &a, vector<LL> & tree, int node, int start, int end) {
	if (start == end) tree[node] = a[start];
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
}

void update(vector<LL> &a, vector<LL>& tree, int node, int start, int end, int index, LL val) {
	if (index < start || index > end) return;
	if (start == end) {
		a[index] = val;
		tree[node] = val;
		return;
	}
	update(a, tree, node * 2, start, (start + end) / 2, index, val);
	update(a, tree, node * 2 + 1, (start + end) / 2 + 1, end, index, val);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

LL query(vector<LL> &tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	LL lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	LL rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return lsum + rsum;
}

void solve() {
	int n, m, q; cin >> n >> m >> q;
	vector<LL> X(m), V(m);
	vector<LL> dis(n, -1);

	vector<LL> value(n);
	for (int i = 0; i < m; ++i) {
		cin >> X[i];
		--X[i];
		dis[X[i]] = 0;
	}
	for (int i = 0; i < m; ++i) {
		cin >> V[i];
		value[X[i]] = V[i];
	}
	set<pair<LL, LL>> S;
	for (int i = 0; i < m; ++i) S.insert({X[i], V[i]});
	for (int i = n - 2; i >= 0; --i) if (dis[i] == -1) dis[i] = dis[i + 1] + 1;
	vector<LL> arr(n);
	for (int i = 0; i < n - 1; ++i) {
		if (dis[i] == 0 && value[i + 1] == 0) arr[i + 1] = value[i] * dis[i + 1] * (dis[i + 1] + 1) / 2;
	}
	int h = (int)ceil(log2(n));
	int tree_size = (1 << (h + 1));
	vector<LL> tree(tree_size);
	init(arr, tree, 1, 0, n - 1);
	for (int i = 0; i < q; ++i) {
		// for (auto i: arr) cout << i << ' ';
		int what; cin >> what;
		if (what == 1) {
			LL x, v; cin >> x >> v; --x;
			value[x] = v;
			auto ite = S.lower_bound({x, v});
			auto nite = ite; --ite;
			LL ind = ite->first;
			LL nv = value[ind] * (x - ind - 1) * (x - ind) / 2;
			update(arr, tree, 1, 0, n - 1, ind + 1, nv);
			if (value[x + 1] == 0) {
				LL nind = nite->first;
				LL nnv = value[x] * (nind - x - 1) * (nind - x) / 2;
				update(arr, tree, 1, 0, n - 1, x + 1, nnv);
			}
			S.insert({x, v});
		} else {
			LL l, r; cin >> l >> r; --l; --r;
			LL ans = query(tree, 1, 0, n - 1, l, r);
			auto ite = S.lower_bound({l, 0});
			auto ind = ite->first; --ite;
			auto v = ite->second;
			if (arr[l] == 0) ans += v * (ind - l) * (ind - l + 1) / 2;
			ite = S.lower_bound({r, 0});
			ind = ite->first; --ite;
			v = ite->second;
			ans -= v * (ind - r - 1) * (ind - r) / 2;
			cout << ans << '\n';
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}