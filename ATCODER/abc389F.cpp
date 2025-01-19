#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N;
vector<pair<ll, ll>> contests;

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	int sz;

	inline ll merge(ll a, ll b) { return a + b; }

	void init(vector<ll>& a) {
		sz = a.size();
		arr = a;
		int h = (int)ceil(log2(sz));
		int tree_size = (1 << (h + 1));
		tree = vector<ll>(tree_size);
		init(1, 0, sz - 1);
	}

	void init(int node, int start, int end) {
		if (start == end) tree[node] = arr[start];
		else {
			init(node * 2, start, (start + end) / 2);
			init(node * 2 + 1, (start + end) / 2 + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}

	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] += val; // modify
			tree[node] += val; // modify
			return;
		}
		update(node * 2, start, (start + end) / 2, index, val);
		update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}

	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0; // modify
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}

	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }

	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
} seg;

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		ll l, r; cin >> l >> r;
		contests.push_back(make_pair(l, r));
	}
	vector<ll> arr(500001, 0);
	seg.init(arr);
	for (int i = 0; i < N; ++i) {
		
		ll l = 0, r = 500000, mid;
		ll tar = contests[i].first;
		ll opr1 = -1, opr2 = -1;
		if (seg.query(1, r) + r >= tar) {
			while (l + 1 < r) {
				mid = (l + r) / 2;
				ll val = seg.query(1, mid) + mid;
				if (val >= tar) r = mid;
				else l = mid;
			}
			// seg.update(r, 1);
			opr1 = r;
			// cout << opr1 << " +\n";
		}
		l = 0, r = 500000;
		tar = contests[i].second + 1;
		if (seg.query(1, r) + r >= tar) {
			while (l + 1 < r) {
				mid = (l + r) / 2;
				ll val = seg.query(1, mid) + mid;
				if (val >= tar) r = mid;
				else l = mid;
			}
			opr2 = r;
			// seg.update(r, -1);
			// cout << opr2 << " -\n";
		}
		if (opr1 != -1) seg.update(opr1, 1);
		if (opr2 != -1) seg.update(opr2, -1);
	}

	int Q; cin >> Q;
	while (Q--) {
		ll x; cin >> x;
		cout << x + seg.query(1, x) << '\n';
	}

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}