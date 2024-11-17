#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

ll N, K;

ll pow(ll a, ll b) {
	if (b == 0) return 1;
	ll half = pow(a, b / 2);
	half = (half * half) % MOD;
	if (b % 2 == 0) return half;
	else return (half * a) % MOD;
}

ll _inv(ll x) {
	return pow(x, MOD - 2);
}

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	vector<ll> tree_cnt;
	int sz;

	void init(vector<ll>& a, int sz_) {
		sz = sz_;
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		tree_cnt = vector<ll>(tree_size);
		init(1, 0, sz - 1);
	}
	void init(int node, int start, int end) {
		if (start == end) tree[node] = arr[start];
		else {
			init(node * 2, start, (start + end) / 2);
			init(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = tree[node * 2] + tree[node * 2 + 1];
			tree_cnt[node] = tree_cnt[node * 2] + tree_cnt[node * 2 + 1];
		}
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] += val;
			tree[node] += val;
			tree_cnt[node] += 1;
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
		tree_cnt[node] = tree_cnt[node * 2] + tree_cnt[node * 2 + 1];
	}
	void update(int index, ll val) {
		update(1, 0, sz - 1, index, val);
	}
	pair<ll, ll> query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return {0, 0};
		if (left <= start && end <= right) return {tree[node], tree_cnt[node]};
		auto lsum = query(node * 2, start, (start + end) / 2, left, right);
		auto rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return {lsum.first + rsum.first, lsum.second + rsum.second};
	}
	pair<ll, ll> query(int left, int right) {
		return query(1, 0, sz - 1, left, right);
	}
} seg;

int P[200001];
int inv[200001];

void solve() {
	cin >> N >> K;
	for (int i = 1; i <= N; ++i) cin >> P[i];
	for (int i = 1; i <= N; ++i) inv[P[i]] = i;
	int MAX_N = N + 1;
	vector<ll> arr(MAX_N);
	seg.init(arr, MAX_N);
	ll ccnt = 0;
	ll cnt = 0;
	for (int i = N; i >= 1; --i) {
		int idx = inv[i];
		auto q = seg.query(max(1ll, - K + idx + 1), idx);
		cnt += q.first; cnt %= MOD;
		cnt -= (q.second * (max(1ll, - K + idx + 1) - 1)) % MOD;
		cnt += MOD;
		cnt %= MOD;
		// cout << i << ' ' << cnt << '\n';
		ccnt += seg.query(1, idx).second;
		ccnt %= MOD;
		seg.update(idx, min((ll) idx, N - K + 1));
	}
	// cout << ccnt << ' ' << cnt << "\n";
	// assert(cnt >= ccnt);
	cnt *= _inv(N - K + 1); cnt %= MOD;
	ccnt -= cnt;
	ccnt += MOD;
	ccnt %= MOD;
	ll tmp = K * (K - 1); tmp %= MOD;
	tmp *= _inv(4); tmp %= MOD;
	ccnt += tmp; ccnt %= MOD;
	cout << ccnt;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}