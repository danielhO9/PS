#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	int sz;

	inline ll merge(ll a, ll b) { return max(a, b); }

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

	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return 0; // modify
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}

	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

ll n, m;
ll a[200000], b[200000], x[200000];

void solve() {
	cin >> n;
	for (int i = 0; i < n; ++i) cin >> a[i];
	for (int i = 0; i < n; ++i) cin >> b[i];
	cin >> m;
	for (int i = 0; i < m; ++i) cin >> x[i];
	for (int i = 0; i < n; ++i) if (a[i] < b[i]) {
		cout << "NO\n";
		return;
	}
	SegmentTree seg;
	vector<ll> arr(n);
	for (int i = 0; i < n; ++i) arr[i] = b[i];
	seg.init(arr);

	unordered_map<int, int, custom_hash> m_razor;
	for (int i = 0; i < m; ++i) ++m_razor[x[i]];

	unordered_map<int, vector<int>, custom_hash> m_idx;
	for (int i = 0; i < n; ++i) if (a[i] != b[i]) m_idx[b[i]].push_back(i);

	for (auto& [num, v]: m_idx) {
		for (int i = 0; i < v.size(); ++i) {
			if (i + 1 == v.size() || seg.query(v[i], v[i + 1]) > num) {
				if (m_razor.find(num) == m_razor.end() || m_razor[num] == 0) {
					cout << "No\n";
					return;
				} else {
					--m_razor[num];
				}
			}
		}
	}
	cout << "Yes\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}