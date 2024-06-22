#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void init(vector<ll>& a, vector<ll>& tree, int node, int start, int end) {
	if (start == end) tree[node] = a[start];
	else {
		init(a, tree, node * 2, start, (start + end) / 2);
		init(a, tree, node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	}
}

ll query(vector<ll>& tree, int node, int start, int end, int left, int right, ll val) {
	if (left > end || right < start) return LLONG_MAX;
	if (tree[node] < val) return LLONG_MAX;
	if (start == end) return start;
	ll lsum = query(tree, node * 2, start, (start + end) / 2, left, right, val);
	if (lsum != LLONG_MAX) return lsum;
	ll rsum = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right, val);
	return rsum;
}

void solve() {
	ll T, N; cin >> T >> N;
	ll L, K; cin >> L >> K;
	vector<ll> t(N * 2); 
	for (int i = 0; i < N; ++i) {
		cin >> t[i];
		t[i + N] = t[i] + T;
	}
	vector<ll> l(K); for (int i = 0; i < K; ++i) cin >> l[i];
	vector<ll> ldis; for (int i = 1; i < K; ++i) ldis.push_back(l[i] - l[i - 1]);
	int MAX_N = 2 * N;
	vector<ll> arr(MAX_N);
	for (int i = 0; i < N; ++i) {
		arr[i] = (i + 1 == N ? T + t[0] : t[i + 1]) - t[i];
		arr[i + N] = arr[i];
	}
	int h = (int)ceil(log2(MAX_N));
	int tree_size = (1 << (h + 1));
	vector<ll> tree(tree_size);

	init(arr, tree, 1, 0, MAX_N - 1);
	ll ans = 0, s = 0, left = 0;
	for (int i = 0; i < K - 1; ++i) {
		if (i == 0 && t[0] >= ldis[0]) {
			ans += ldis[0];
			left = t[0] - ldis[0];
			continue;
		}
		if (left >= ldis[i]) {
			ans += ldis[i];
			left -= ldis[i];
			continue;
		}
		if (arr[s] >= ldis[i]) {
			ans += t[s] - (ans % T);
			ans += ldis[i];
			left = arr[s] - ldis[i];
			++s;
			s %= N;
			continue;
		}
		ll tmp = query(tree, 1, 0, MAX_N - 1, s, s + N, ldis[i]);
		if (tmp == LLONG_MAX) {
			cout << "What is that map newbie...\n";
			return;
		}
		s = tmp;
		ans += t[s] > (ans % T) ? t[s] - (ans % T) : t[s + N] - (ans % T);
		ans += ldis[i];
		left = arr[s] - ldis[i];
		++s;
		s %= N;
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}