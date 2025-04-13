#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;

int N;
char opr[500000];
ll l[500000], r[500000];
ll u[500000];

ll pow(ll a, ll b) {
    if (b == 0) return 1ll;
    ll h = pow(a, b / 2);
    h = (h * h) % MOD;
    if (b % 2) return (a * h) % MOD;
    else return h;
}

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

	int query(int node, int start, int end, int k) {
		if (start == end) return start;
		int l = tree[node * 2];
        if (l < k) return query(node * 2 + 1, (start + end) / 2 + 1, end, k - l);
        else return query(node * 2, start, (start + end) / 2, k);
	}

	void update(int index, ll val) { update(1, 0, sz - 1, index, val); }

	int query(int k) { return query(1, 0, sz - 1, k); }
} seg;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N - 1; ++i) {
        cin >> l[i] >> opr[i];
    }
    vector<ll> arr(N - 1, 1);
    seg.init(arr);
    cin >> r[N - 2];
    for (int i = 0; i < N - 2; ++i) r[i] = l[i + 1];
    for (int i = 0; i < N - 1; ++i) cin >> u[i];
    ll v = 0;
    int cnt = N - 1;
    for (int i = 0; i < N - 1; ++i) {
        v ^= u[i];
        ll pv = v;
        int idx = seg.query(v);
        // cout << idx << ' ';
        if (opr[idx] == '+') v = (l[idx] + r[idx]) % MOD;
        else if (opr[idx] == '-') v = (l[idx] - r[idx] + MOD) % MOD;
        else if (opr[idx] == '*') v = (l[idx] * r[idx]) % MOD;
        else v = (l[idx] * pow(r[idx], MOD - 2)) % MOD;
        
        if (pv != 1) {
            int iidx = seg.query(pv - 1);
            r[iidx] = v;
        }
        if (pv != cnt) {
            int iidx = seg.query(pv + 1);
            l[iidx] = v;
        }
        seg.update(idx, -1);
        --cnt;
        cout << v << '\n';
    }
}