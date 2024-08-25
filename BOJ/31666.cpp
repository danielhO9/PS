#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct LazyPropagation {
	vector<ll> arr;
	vector<ll> tree;
	vector<ll> lazy;
	int sz;
    void init(vector<ll>& a, int sz_) {
		sz = sz_;
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		lazy = vector<ll>(tree_size);
		init_(1, 0, sz - 1);
	}
	void init_(int node, int start, int end) {
		if (start == end) tree[node] = arr[start];
		else {
			init_(node * 2, start, (start + end) / 2);
			init_(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = tree[node * 2] + tree[node * 2 + 1];
		}
	}

	void update_lazy(int node, int start, int end) {
		if (lazy[node] != 0) {
			tree[node] = lazy[node];
			if (start != end) {
				lazy[node * 2] = lazy[node];
				lazy[node * 2 + 1] = lazy[node];
			}
			lazy[node] = 0;
		}
	}
	void update_range(int node, int start, int end, int left, int right, ll diff) {
		update_lazy(node, start, end);
		if (left > end || right < start) {
			return;
		}
		if (left <= start && end <= right) {
			tree[node] = diff;
			if (start != end) {
				lazy[node * 2] = diff;
				lazy[node * 2 + 1] = diff;
			}
			return;
		}
		update_range(node * 2, start, (start + end) / 2, left, right, diff);
		update_range(node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
		tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
	}
	void update(int left, int right, ll val) {
		update_range(1, 0, sz - 1, left, right, val);
	}
	ll query(int node, int start, int end, int left, int right) {
		update_lazy(node, start, end);
		if (left > end || right < start) {
			return 0;
		}
		if (left <= start && end <= right) {
			return tree[node];
		}
		ll lsum = query(node * 2, start, (start+end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start+end) / 2 + 1, end, left, right);
		return max(lsum, rsum);
	}
	ll query(int left, int right) {
		return query(1, 0, sz - 1, left, right);
	}
} seg;

ll x[100000], s[100000];
unordered_map<ll, ll> m;

void solve() {
    int N; cin >> N;
    for (int i = 0; i < N; ++i) cin >> x[i] >> s[i];
    set<ll> S;
    for (int i = 0; i < N; ++i) {
        S.insert(x[i]);
        S.insert(x[i] + s[i] - 1);
    }
    int num = 0;
    for (auto i: S) {
        m[i] = num;
        ++num;
    }
	int MAX_N = num;
    vector<ll> a(MAX_N);
    seg.init(a, MAX_N);
    ll ans = 0;
    for (int i = 0; i < N; ++i) {
        ll h = seg.query(m[x[i]], m[x[i] + s[i] - 1]) + s[i];
        ans = max(ans, h);
        cout << ans << '\n';
        seg.update(m[x[i]], m[x[i] + s[i] - 1], h);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}