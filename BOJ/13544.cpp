#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void init(vector<ll>& a, vector<vector<ll>>& tree, int node, int start, int end) {
	if (start == end) tree[node].push_back(a[start]);
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node].resize(tree[node * 2].size() + tree[node * 2 + 1].size());
		merge(tree[node * 2].begin(), tree[node * 2].end(), tree[node * 2 + 1].begin(), tree[node * 2 + 1].end(), tree[node].begin());
	}
}

ll query(vector<vector<ll>>& tree, int node, int start, int end, int left, int right, ll k) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node].end() - upper_bound(tree[node].begin(), tree[node].end(), k);
	ll lcnt = query(tree, node * 2, start, (start + end) / 2, left, right, k);
	ll rcnt = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right, k);
	return lcnt + rcnt;
}

void solve() {
	// 0 ~ MAX_N - 1
	int MAX_N; cin >> MAX_N;
	vector<ll> arr(MAX_N); for (int i = 0; i < MAX_N; ++i) cin >> arr[i];
	int h = (int)ceil(log2(MAX_N));
	int tree_size = (1 << (h + 1));
	vector<vector<ll>> tree(tree_size);
	init(arr, tree, 1, 0, MAX_N - 1);
	int M; cin >> M;
	ll ans = 0;
	while (M--) {
		int i, j; ll k; cin >> i >> j >> k;
		i ^= ans; j ^= ans; k ^= ans; --i; --j;
		ans = query(tree, 1, 0, MAX_N - 1, i, j, k);
		cout << ans << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}