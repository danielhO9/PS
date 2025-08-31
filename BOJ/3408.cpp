#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INIT_VALUE = 0; // TODO

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	int sz;

	ll merge(ll a, ll b) { return min(a, b); }
	SegmentTree() = default;
	SegmentTree(int sz): SegmentTree(vector<ll>(sz, INIT_VALUE)) {}
	SegmentTree(const vector<ll>& a) {
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
			int mid = (start + end) / 2;
			init(node * 2, start, mid);
			init(node * 2 + 1, mid + 1, end);
			tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
		}
	}
	void update(int node, int start, int end, int index, ll val) {
		if (index < start || index > end) return;
		if (start == end) {
			arr[index] += val;
			tree[node] += val;
			return;
		}
		int mid = (start + end) / 2;
		update(node * 2, start, mid, index, val);
		update(node * 2 + 1, mid + 1, end, index, val);
		tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
	}
	ll query(int node, int start, int end, int left, int right) {
		if (left > end || right < start) return INIT_VALUE;
		if (left <= start && end <= right) return tree[node];
		int mid = (start + end) / 2;
		ll lsum = query(node * 2, start, mid, left, right);
		ll rsum = query(node * 2 + 1, mid + 1, end, left, right);
		return merge(lsum, rsum);
	}
	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }
	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

int n;
int a[200000];
int prv[200000], nxt[200000];
unordered_map<int, int> m;

bool isUnique(int i, int l, int r) {
    return prv[i] < l && r < nxt[i];
}

int isBoring(int l, int r) {
    if (l >= r) return 0;
    int ret = 0;
    int pivot = -1;
    for (int i = 0; i <= r - l; ++i) {
        if (isUnique(l + i, l, r)) {
            pivot = l + i;
            break;
        }
        if (isUnique(r - i, l, r)) {
            pivot = r - i;
            break;
        }
    }
    if (pivot == -1) return 1;
    ret |= isBoring(l, pivot - 1);
    ret |= isBoring(pivot + 1, r);
    return ret;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    m.clear();
    for (int i = 0; i < n; ++i) {
        prv[i] = -1, nxt[i] = n;
        if (m.find(a[i]) != m.end()) {
            prv[i] = m[a[i]];
            nxt[prv[i]] = i;
        }
        m[a[i]] = i;
    }
    if (isBoring(0, n - 1)) cout << "boring\n";
    else cout << "non-boring\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}