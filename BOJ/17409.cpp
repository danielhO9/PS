#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll MOD = 1e9 + 7;

void update(vector<ll>& tree, int node, int start, int end, int index, ll val) {
	if (index < start || index > end) return;
	if (start == end) {
		tree[node] = val;
		return;
	}
	update(tree, node * 2, start, (start + end) / 2, index, val);
	update(tree, node * 2 + 1, (start + end) / 2 + 1, end, index, val);
	tree[node] = tree[node * 2] + tree[node * 2 + 1]; tree[node] %= MOD;
}

ll query(vector<ll>& tree, int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	ll lsum = query(tree, node * 2, start, (start + end) / 2, left, right);
	ll rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return (lsum + rsum) % MOD;
}

void solve() {
	int N, K; cin >> N >> K;
	vector<ll> A(N); for (int i = 0; i < N; ++i) cin >> A[i];
	ll cache[N][K + 1];
	for (int i = 0; i < N; ++i) cache[i][1] = 1;

	// 0 ~ MAX_N - 1
	int MAX_N = 1e5 + 1;
	int h = (int)ceil(log2(MAX_N));
	int tree_size = (1 << (h + 1));
	vector<vector<ll>> tree(K + 1, vector<ll>(tree_size));
	for (int i = 2; i <= K; ++i) {
		for (int j = 0; j < N; ++j) {
			cache[j][i] = query(tree[i], 1, 0, MAX_N - 1, 0, A[j] - 1);
			update(tree[i], 1, 0, MAX_N - 1, A[j], cache[j][i - 1]);
		}
	}
	ll ans = 0;
	for (int i = 0; i < N; ++i) {
		ans += cache[i][K];
		ans %= MOD;
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