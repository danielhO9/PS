#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SegmentTree {
	vector<ll> arr;
	vector<ll> tree;
	int sz;

	inline ll merge(ll a, ll b) { return min(a, b); }

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
		if (left > end || right < start) return LLONG_MAX; // modify
		if (left <= start && end <= right) return tree[node];
		ll lsum = query(node * 2, start, (start + end) / 2, left, right);
		ll rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
		return merge(lsum, rsum);
	}

	ll query(int left, int right) { return query(1, 0, sz - 1, left, right); }
};

int N, P, L;
int a[3001], l[3001], r[3001];
const int MAX = 987654321;
ll val[3001];

void solve() {
    vector<ll> arr(N + 1, MAX);
    int sm = 0;
    for (int i = 1; i <= N; ++i) sm += a[i];
    int cur = 0;
    int last = sm % P;
    if (last == 0) last += P;
    for (int i = 1; i <= N; ++i) {
        int s = cur + 1, e = cur + a[i];
        l[i] = (s - 1) / P + 1;
        r[i] = (e - 1) / P + 1;
        cur += a[i];
    }
    int ans = 0;
    val[0] = MAX;
    for (int i = 1; i <= N; ++i) {
        arr[i] = (r[i] - l[i]) * P;
        if (r[i] == r[N]) arr[i] += last;
        else arr[i] += P;
        val[i] = arr[i];
        if (arr[i] <= L) ans = 1;
    }
    SegmentTree seg; seg.init(arr);
    vector<ll> narr(N + 1);
    
    for (int j = 2; j <= N; ++j) {
        for (int i = 0; i <= N; ++i) narr[i] = MAX;
        int prv = 0;
        ll mn = arr[prv];
        for (int i = j; i <= N; ++i) {
            while (prv + 1 < i && r[prv + 1] < l[i]) {
                ++prv;
                mn = min(mn, arr[prv]);
            }
            narr[i] = min(narr[i], mn + val[i]);
            ll tmp = val[i];
            if (l[i] == r[N]) tmp -= last;
            else tmp -= P;
            if (prv + 1 < i) narr[i] = min(narr[i], seg.query(prv + 1, i - 1) + tmp);
            if (narr[i] <= L) ans = j;
        }
        seg.init(narr);
        swap(arr, narr);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while (true) {
        cin >> N >> P >> L;
        if (N == 0) break;
        for (int i = 1; i <= N; ++i) cin >> a[i];
        solve();
    }
}