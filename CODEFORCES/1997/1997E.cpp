#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void update(vector<ll>& a, vector<ll>& tree, int node, int start, int end, int index, ll val) {
	if (index < start || index > end) return;
	if (start == end) {
		a[index] += val;
		tree[node] += val;
		return;
	}
	update(a, tree, node * 2, start, (start + end) / 2, index, val);
	update(a, tree, node * 2 + 1, (start + end) / 2 + 1, end, index, val);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(vector<ll>& tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	ll lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	ll rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return lsum + rsum;
}

int n, q;
int a[200000];
int k[200000];

void solve() {
	cin >> n >> q;
	for (int i = 0; i < n; ++i) cin >> a[i];
	int MAX_N = n + 1;
	vector<ll> arr(MAX_N);
	int h = (int)ceil(log2(MAX_N));
	int tree_size = (1 << (h + 1));
	vector<ll> tree(tree_size);
	for (int i = 0; i < n; ++i) {
		int l = 0, r = n;
		while (l + 1 < r) {
			int mid = (l + r) / 2;
			if (query(tree, 1, 0, n, 1, mid) / mid + 1 <= a[i]) r = mid;
			else l = mid;
		}
		update(arr, tree, 1, 0, n, r, 1ll);
		k[i] = r;
	}
	while (q--) {
		int i, x; cin >> i >> x; --i;
		if (k[i] <= x) {
			cout << "YES\n";
		} else cout << "NO\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}