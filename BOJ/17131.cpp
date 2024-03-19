#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll MOD = 1e9 + 7;

void init(vector<ll> &a, vector<ll> & tree, int node, int start, int end) {
	if (start == end) tree[node] = a[start];
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
}

void update(vector<ll> &a, vector<ll>& tree, int node, int start, int end, int index, ll val) {
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

ll query(vector<ll> &tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	ll lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	ll rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return lsum + rsum;
}

void solve() {
	int N; cin >> N;
	vector<pair<int, int>> V(N);
	for (int i = 0; i < N; ++i) cin >> V[i].first >> V[i].second;
	sort(V.begin(), V.end(), [](auto& a, auto& b) { return a.second > b.second; });
	int n; n = 4e5 + 1;
	// 0 ~ n - 1
	vector<ll> arr(n);
	int h = (int)ceil(log2(n));
	int tree_size = (1 << (h + 1));
	vector<ll> tree(tree_size);
	// init(arr, tree, 1, 0, n - 1);
	// update(arr, tree, 1, 0, n - 1, cur, 30);
	// query(tree, 1, 0, n - 1, 0, cur);
	ll ans = 0;
	int now = 0;
	for (int i = 0; i < N; ++i) {
		if (V[now].second != V[i].second) {
			for (int j = now; j < i; ++j) {
				update(arr, tree, 1, 0, n - 1, V[j].first + 2e5, arr[V[j].first + 2e5] + 1);
			}
			now = i;
		}
		ll l = query(tree, 1, 0, n - 1, 0, V[i].first - 1 + 2e5);
		ll r = query(tree, 1, 0, n - 1, V[i].first + 1 + 2e5, n - 1);
		l *= r; l %= MOD;
		ans += l;
		ans %= MOD;
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}