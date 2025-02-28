#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct LazyPropagation {
	vector<ll> arr;
	vector<ll> tree;
	vector<ll> lazy;
	ll sz;

	inline ll merge(ll a, ll b) { return max(a, b); }

	void init(vector<ll>& a) {
		sz = a.size();
		arr = a;
		ll h = (ll)ceil(log2(sz));
		ll tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		lazy = vector<ll>(tree_size);
		init_(1, 0, sz - 1);
	}

	void init_(ll node, ll start, ll end) {
		if (start == end) tree[node] = arr[start];
		else {
			init_(node * 2, start, (start + end) / 2);
			init_(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	void update_lazy(ll node, ll start, ll end) {
		if (lazy[node] != 0) {
			tree[node] += lazy[node]; // modify
			if (start != end) {
				lazy[node * 2] += lazy[node];
				lazy[node * 2 + 1] += lazy[node];
			}
			lazy[node] = 0;
		}
	}

	void update_range(ll node, ll start, ll end, ll left, ll right, ll diff) {
		update_lazy(node, start, end);
		if (left > end || right < start) {
			return;
		}
		if (left <= start && end <= right) {
			tree[node] += diff; // modify
			if (start != end) {
				lazy[node * 2] += diff;
				lazy[node * 2 + 1] += diff;
			}
			return;
		}
		update_range(node * 2, start, (start + end) / 2, left, right, diff);
		update_range(node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}

	ll query(ll node, ll start, ll end, ll left, ll right) {
		update_lazy(node, start, end);
		if (left > end || right < start) return 0; // modify
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}

	void update(ll left, ll right, ll val) { update_range(1, 0, sz - 1, left, right, val); }

	ll query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
} seg;

int N;
ll X[500001], Y[500001];
vector<ll> itoX, itoY;
unordered_map<ll, int> xm, ym;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 1; i <= N; ++i) cin >> X[i] >> Y[i];
	for (int i = 0; i <= N; ++i) itoX.push_back(X[i]);
	for (int i = 0; i <= N; ++i) itoY.push_back(Y[i]);
	sort(itoX.begin(), itoX.end()); for (int i = 0; i <= N; ++i) xm[itoX[i]] = i;
	sort(itoY.begin(), itoY.end()); for (int i = 0; i <= N; ++i) ym[itoY[i]] = i;
	vector<pair<int, int>> v;
	for (int i = 0; i <= N; ++i) v.push_back(make_pair(xm[X[i]], ym[Y[i]]));
	sort(v.begin(), v.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
		return a.second < b.second;
	});

	vector<ll> arr(N + 1, 0); seg.init(arr);
	
	for (auto pt: v) {
		int xi = pt.first, yi = pt.second;
		ll cur = seg.query(xi, xi);
		ll mx = xi == 0 ? 0 : seg.query(0, xi - 1);
		seg.update(xi, xi, -cur + mx);

		seg.update(xi, N, itoX[xi]);
		if (xi != 0) seg.update(0, xi - 1, itoY[yi]);
	}
	cout << seg.query(0, N);
}