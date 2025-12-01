#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Node {
    ll cnt, sm;
    Node() = default;
};

/**
 * Description: Segment Tree with Lazy Propagation for efficient range updates and queries.
 *  Supports range updates and range queries efficiently.
 * Time: Both update and query operations are $O(\log N)$.
 */
struct LazyPropagation {
	vector<Node> arr;
	vector<Node> tree;
	vector<ll> lazy;
	ll sz;

	inline Node merge(const Node& a, const Node& b) {
        Node ret {a.cnt + b.cnt, a.sm + b.sm};
        return ret;
    }
	LazyPropagation() = default;
	LazyPropagation(const vector<ll>& a) {
		sz = a.size();
		ll h = (ll)ceil(log2(sz));
		ll tree_size = (1 << (h + 1));
        arr = vector<Node>(sz);
		tree = vector<Node>(tree_size);
        lazy = vector<ll>(tree_size);
        for (ll i = 0; i < sz; ++i) if (a[i]) arr[i] = Node{1, 0};
		init(1, 0, sz - 1);
	}
	void init(ll node, ll start, ll end) {
		if (start == end) tree[node] = arr[start];
		else {
			ll mid = (start + end) / 2;
			init(node * 2, start, mid);
			init(node * 2 + 1, mid + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update_lazy(ll node, ll start, ll end) {
		if (lazy[node] != 0) {
			tree[node].sm += tree[node].cnt * lazy[node];
			if (start != end) {
				lazy[node * 2] += lazy[node];
				lazy[node * 2 + 1] += lazy[node];
			}
			lazy[node] = 0;
		}
	}
	void update_range(ll node, ll start, ll end, ll left, ll right, ll diff) {
		update_lazy(node, start, end);
		if (left > end || right < start) return;
		if (left <= start && end <= right) {
			tree[node].sm += tree[node].cnt * diff;
			if (start != end) {
				lazy[node * 2] += diff;
				lazy[node * 2 + 1] += diff;
			}
			return;
		}
		ll mid = (start + end) / 2;
		update_range(node * 2, start, mid, left, right, diff);
		update_range(node * 2 + 1, mid + 1, end, left, right, diff);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
    void update_poll(ll node, ll start, ll end, ll index) {
        update_lazy(node, start, end);
		if (index < start || index > end) return;
		if (start == end) {
			tree[node] = Node {0, 0};
			return;
		}
		ll mid = (start + end) / 2;
		update_poll(node * 2, start, mid, index);
		update_poll(node * 2 + 1, mid + 1, end, index);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	Node query(ll node, ll start, ll end, ll left, ll right) {
		update_lazy(node, start, end);
		if (left > end || right < start) return Node {0, 0}; // TODO
		if (left <= start && end <= right) return tree[node];
		ll mid = (start + end) / 2;
		Node lsum = query(node * 2, start, mid, left, right);
		Node rsum = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(lsum, rsum);
	}
	void update(ll left, ll right, ll val) { update_range(1, 0, sz - 1, left, right, val); }
    void updatep(ll idx) { update_poll(1, 0, sz - 1, idx); }
	Node query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
};

ll N;
ll x[300000], y[300000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    ll N; cin >> N;
    for (ll i = 0; i < N; ++i) cin >> x[i] >> y[i];
    
    vector<ll> v;
    for (ll i = 0; i < N; ++i) v.push_back(x[i]);
    sort(v.begin(), v.end());
    for (ll i = 0; i < N; ++i) x[i] = lower_bound(v.begin(), v.end(), x[i]) - v.begin();

    v.clear();
    for (ll i = 0; i < N; ++i) v.push_back(y[i]);
    sort(v.begin(), v.end());
    for (ll i = 0; i < N; ++i) y[i] = lower_bound(v.begin(), v.end(), y[i]) - v.begin();

    vector<pair<ll, ll>> pts;
    for (ll i = 0; i < N; ++i) pts.push_back(make_pair(x[i], y[i]));
    sort(pts.begin(), pts.end());

    vector<ll> a(N, 1);
    a[pts.front().second] = 0;
    LazyPropagation seg {a};

    ll ans = 0;
    for (ll i = 0; i < N; ++i) {
        ans += seg.query(0, pts[i].second).sm;

        if (i + 1 < N) seg.updatep(pts[i + 1].second);
        seg.update(pts[i].second, N - 1, 1);
    }
    cout << ans;
}