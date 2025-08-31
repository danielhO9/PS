#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INIT_VALUE = 0; // TODO

struct LazyPropagation {
	vector<ll> arr;
	vector<ll> tree;
	vector<ll> lazy;
	int sz;

	inline ll merge(ll a, ll b) { return a + b; }
	LazyPropagation() = default;
	LazyPropagation(int sz): LazyPropagation(vector<ll>(sz, INIT_VALUE)) {}
	LazyPropagation(const vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
        lazy = vector<ll>(tree_size);
		init(1, 0, sz - 1);
	}
	void init(ll node, ll start, ll end) {
		if (start == end) tree[node] = arr[start];
		else {
			int mid = (start + end) / 2;
			init(node * 2, start, mid);
			init(node * 2 + 1, mid + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update_lazy(ll node, ll start, ll end) {
		if (lazy[node] != 0) {
			tree[node] = 0;
			if (start != end) {
				lazy[node * 2] = 1;
				lazy[node * 2 + 1] = 1;
			}
			lazy[node] = 0;
		}
	}
    void update_point(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			tree[node] += val;
			return;
		}
		int mid = (start + end) / 2;
		update_point(node * 2, start, mid, index, val);
		update_point(node * 2 + 1, mid + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	void update_range(ll node, ll start, ll end, ll left, ll right) {
		update_lazy(node, start, end);
		if (left > end || right < start) return;
		if (left <= start && end <= right) {
			tree[node] = 0;
			if (start != end) {
				lazy[node * 2] = 1; // modify
				lazy[node * 2 + 1] = 1; // modify
			}
			return;
		}
		int mid = (start + end) / 2;
		update_range(node * 2, start, mid, left, right);
		update_range(node * 2 + 1, mid + 1, end, left, right);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	ll query(ll node, ll start, ll end, ll left, ll right) {
		update_lazy(node, start, end);
		if (left > end || right < start) return INIT_VALUE;
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		ll lsum = query(node * 2, start, mid, left, right);
		ll rsum = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(lsum, rsum);
	}
    void update_set(ll idx, ll val) {
        query(idx, idx);
        update_point(1, 0, sz - 1, idx, val);
    }
	void update(ll left, ll right) { update_range(1, 0, sz - 1, left, right); }
	ll query(ll left, ll right) { return query(1, 0, sz - 1, left, right); }
};

struct Query {
    int t, x, y;
};

int Q;
int prv[500002], nxt[500002];
vector<Query> query;
vector<ll> v;
int inv[500001];

void solve() {
    cin >> Q;
    query.resize(Q + 1);
    prv[0] = -1;
    nxt[0] = Q + 1;
    for (int i = 1; i <= Q; ++i) {
        cin >> query[i].t >> query[i].x;
        if (query[i].t == 2) cin >> query[i].y;
        else {
            nxt[i] = nxt[query[i].x];
            prv[i] = query[i].x;
            nxt[query[i].x] = i;
        }
    }
    int cur = 0;
    while (cur != Q + 1) {
        v.push_back(cur);
        cur = nxt[cur];
    }
    // for (auto i: v) cout << i << ' ';
    for (int i = 0; i < v.size(); ++i) inv[v[i]] = i;
    LazyPropagation seg {(int) v.size()};
    for (int i = 1; i <= Q; ++i) {
        if (query[i].t == 1) {
            int ii = inv[i];
            seg.update_set(ii, i);
        } else {
            int xx = inv[query[i].x], yy = inv[query[i].y];
            if (xx > yy) swap(xx, yy);
            if (xx + 1 == yy) cout << 0 << '\n';
            else {
                cout << seg.query(xx + 1, yy - 1) << '\n';
                seg.update(xx + 1, yy - 1);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}