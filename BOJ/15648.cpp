#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void update(vector<ll>& a, vector<ll>& tree, int node, int start, int end, int index, ll val) {
	if (index < start || index > end) return;
	if (start == end) {
		a[index] = val;
		tree[node] = val;
		return;
	}
	update(a, tree, node * 2, start, (start + end) / 2, index, val);
	update(a, tree, node * 2 + 1, (start + end) / 2 + 1, end, index, val);
	tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

ll query(vector<ll>& tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	ll lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	ll rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return max(lsum, rsum);
}

void solve() {
	int N, k, d; cin >> N >> k >> d;
	vector<int> S(N); for (int i = 0; i < N; ++i) cin >> S[i];
	vector<ll> mod(k);
	// 0 ~ MAX_N - 1
	int MAX_N = 5e5 + 1;
	vector<ll> arr(MAX_N);
	int h = (int)ceil(log2(MAX_N));
	int tree_size = (1 << (h + 1));
	vector<ll> tree(tree_size);
	ll ans = 0;
	for (int i = 0; i < N; ++i) {
		ll temp = mod[S[i] % k];
		temp = max(temp, query(tree, 1, 0, MAX_N - 1, max(0, S[i] - d), min(S[i] + d, 500000)));
		++temp;
		mod[S[i] % k] = max(mod[S[i] % k], temp);
		update(arr, tree, 1, 0, MAX_N - 1, S[i], temp);
		ans = max(ans, temp);
	}
	cout << ans;
	// init(arr, tree, 1, 0, MAX_N - 1);
	// update(arr, tree, 1, 0, MAX_N - 1, cur, 30);
	// query(tree, 1, 0, MAX_N - 1, 0, cur);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}